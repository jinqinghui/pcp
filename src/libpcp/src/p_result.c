/*
 * Copyright (c) 2012-2014,2021 Red Hat.
 * Copyright (c) 1995-2000 Silicon Graphics, Inc.  All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * Thread-safe note
 *
 * Because __pmFindPDUBuf() returns with a pinned pdu buffer, the
 * buffer passed back from __pmEncodeResult() must also remain pinned
 * (otherwise another thread could clobber the buffer after returning
 * from __pmEncodeResult()) ... it is the caller of __pmEncodeResult()
 * who is responsible for (a) not pinning the buffer again, and (b)
 * ensuring _someone_ will unpin the buffer when it is safe to do so.
 *
 * Similarly, __pmDecodeResult() accepts a pinned buffer and returns
 * a pmResult that (on 64-bit pointer platforms) may contain pointers
 * into a second underlying pinned buffer.  The input buffer remains
 * pinned, the second buffer will be pinned if it is used.  The caller
 * will typically call pmFreeResult(), but also needs to call
 * __pmUnpinPDUBuf() for the input PDU buffer.  When the result contains
 * pointers back into the input PDU buffer, this will be pinned _twice_
 * so the pmFreeResult() and __pmUnpinPDUBuf() calls will still be
 * required.
 */

#include <ctype.h>
#include "pmapi.h"
#include "libpcp.h"
#include "internal.h"

/*
 * PDUs for pmResult (PDU_RESULT) and pmHighResResult (PDU_HIGHRES_RESULT)
 */

typedef struct {
    pmID		pmid;
    int			numval;		/* no. of vlist elements or error */
    int			valfmt;		/* insitu or pointer */
    __pmValue_PDU	vlist[1];	/* zero or more */
} vlist_t;

typedef struct {
    __pmPDUHdr		hdr;
    pmTimeval		timestamp;	/* when returned */
    int			numpmid;	/* no. of PMIDs to follow */
    __pmPDU		data[1];	/* zero or more */
} result_t;

typedef struct {
    __pmPDUHdr		hdr;		/* three word (3x int) PDU header */
    int			numpmid;	/* count of PMIDs to follow */
    pmTimespec		timestamp;	/* 64bit-aligned time */
    __pmPDU		data[2];	/* zero or more (2 for alignment) */
} highres_result_t;

static void
__pmGetResultSize(int pdutype, int numpmid, pmValueSet * const *vset,
		size_t *needp, size_t *vneedp)
{
    size_t	need;	/* bytes for the PDU */
    size_t	vneed;	/* additional bytes for the pmValueBlocks on the end */
    int		i, j;
   
    vneed = 0;
    if (pdutype == PDU_HIGHRES_RESULT)
	need = sizeof(highres_result_t) - (sizeof(__pmPDU) * 2);
    else
	need = sizeof(result_t) - sizeof(__pmPDU);

    /* now add space for each vlist_t (data field in result structures) */
    for (i = 0; i < numpmid; i++) {
	const pmValueSet *vsp = vset[i];

	/* need space for PMID and count of values (defer valfmt until
	 * we know numval > 0, which means there should be a valfmt)
	 */
	need += sizeof(pmID) + sizeof(int);
	for (j = 0; j < vsp->numval; j++) {
	    /* plus value, instance pair */
	    need += sizeof(__pmValue_PDU);
	    if (vsp->valfmt == PM_VAL_DPTR || vsp->valfmt == PM_VAL_SPTR) {
		/* plus pmValueBlock */
		vneed += PM_PDU_SIZE_BYTES(vsp->vlist[j].value.pval->vlen);
	    }
	}
	if (j)
	    /* optional value format, if any values present */
	    need += sizeof(int);
    }

    *vneedp = vneed;
    *needp = need;
}

static void
__pmEncodeValueSet(__pmPDU *pdubuf, int numpmid, pmValueSet * const *vset,
		vlist_t *vlp, __pmPDU *vbp)
{
    int		i, j, nb, pad, extra;

    /*
     * Note: vbp, and hence offset in sent PDU is in units of __pmPDU
     */
    for (i = 0; i < numpmid; i++) {
	pmValueSet	*vsp = vset[i];

	vlp->pmid = __htonpmID(vsp->pmid);
	if (vsp->numval > 0)
	    vlp->valfmt = htonl(vsp->valfmt);
	for (j = 0; j < vsp->numval; j++) {
	    vlp->vlist[j].inst = htonl(vsp->vlist[j].inst);
	    if (vsp->valfmt == PM_VAL_DPTR || vsp->valfmt == PM_VAL_SPTR) {
		/*
		 * pmValueBlocks are harder!
		 * -- need to copy the len field (len) + len bytes (vbuf)
		 */
		nb = vsp->vlist[j].value.pval->vlen;
		memcpy((void *)vbp, (void *)vsp->vlist[j].value.pval, nb);
		if ((extra = (nb % sizeof(__pmPDU))) != 0) {
		    /* clear the padding bytes, lest they contain garbage */
		    char	*padp = (char *)vbp + nb;
		    for (pad = sizeof(__pmPDU) - 1; pad >= extra; pad--)
			*padp++ = '~';	/* buffer end */
		}
		__htonpmValueBlock((pmValueBlock *)vbp);
		/* point to the value block at the end of the PDU */
		vlp->vlist[j].value.lval = htonl((int)(vbp - pdubuf));
		vbp += PM_PDU_SIZE(nb);
	    }
	    else {
		/* punt on vsp->valfmt == PM_VAL_INSITU */
		vlp->vlist[j].value.lval = htonl(vsp->vlist[j].value.lval);
	    }
	}
	vlp->numval = htonl(vsp->numval);

	if (j > 0)
	    vlp = (vlist_t *)((__psint_t)vlp +
				sizeof(*vlp) + (j - 1) * sizeof(vlp->vlist[0]));
	else
	    vlp = (vlist_t *)((__psint_t)vlp +
				sizeof(vlp->pmid) + sizeof(vlp->numval));
    }
}

int
__pmEncodeResult(int targetfd, const pmResult *result, __pmPDU **pdu)
{
    size_t	need, vneed;
    __pmPDU	*pdubuf;
    result_t	*pp;
    int		type = PDU_RESULT;

    (void)targetfd;
    __pmGetResultSize(type, result->numpmid, result->vset, &need, &vneed);

    /*
     * Need to reserve additional space for trailer (an int) in case the
     * PDU buffer is used by __pmLogPutResult2()
     */
    if ((pdubuf = __pmFindPDUBuf((int)(need + vneed + sizeof(int)))) == NULL)
	return -oserror();
    pp = (result_t *)pdubuf;
    pp->hdr.len = (int)(need + vneed);
    pp->hdr.type = type;
    pp->timestamp.tv_sec = htonl((__int32_t)(result->timestamp.tv_sec));
    pp->timestamp.tv_usec = htonl((__int32_t)(result->timestamp.tv_usec));
    pp->numpmid = htonl(result->numpmid);

    __pmEncodeValueSet(pdubuf, result->numpmid, result->vset,
			(vlist_t *)pp->data, pdubuf + need/sizeof(__pmPDU));

    /* Note PDU remains pinned ... see thread-safe comments above */
    *pdu = pdubuf;
    return 0;
}

int
__pmEncodeHighResResult(const pmHighResResult *result, __pmPDU **pdu)
{
    size_t		need, vneed;
    __pmPDU		*pdubuf;
    highres_result_t	*pp;
    int			type = PDU_HIGHRES_RESULT;

    __pmGetResultSize(type, result->numpmid, result->vset, &need, &vneed);

    /*
     * Need to reserve additional space for trailer (an int) in case the
     * PDU buffer is used by __pmLogPutHighResResult2()
     */
    if ((pdubuf = __pmFindPDUBuf((int)(need + vneed + sizeof(int)))) == NULL)
	return -oserror();
    pp = (highres_result_t *)pdubuf;
    pp->hdr.len = (int)(need + vneed);
    pp->hdr.type = type;
    pp->numpmid = htonl(result->numpmid);
    pp->timestamp.tv_sec = (__int64_t)(result->timestamp.tv_sec);
    pp->timestamp.tv_nsec = (__int64_t)(result->timestamp.tv_nsec);
    __htonll((char *)&pp->timestamp.tv_sec);
    __htonll((char *)&pp->timestamp.tv_nsec);

    __pmEncodeValueSet(pdubuf, result->numpmid, result->vset,
			(vlist_t *)pp->data, pdubuf + need/sizeof(__pmPDU));

    /* Note PDU remains pinned ... see thread-safe comments above */
    *pdu = pdubuf;
    return 0;
}

/*
 * Internal variant of __pmSendResult() with current context.
 */
int
__pmSendResult_ctx(__pmContext *ctxp, int fd, int from, const pmResult *result)
{
    int		sts;
    __pmPDU	*pdubuf = NULL;
    result_t	*pp;

    if (ctxp != NULL)
	PM_ASSERT_IS_LOCKED(ctxp->c_lock);

    if (pmDebugOptions.pdu)
	__pmDumpResult_ctx(ctxp, stderr, result);
    if ((sts = __pmEncodeResult(fd, result, &pdubuf)) < 0)
	return sts;
    pp = (result_t *)pdubuf;
    pp->hdr.from = from;
    sts = __pmXmitPDU(fd, pdubuf);
    __pmUnpinPDUBuf(pdubuf);
    return sts;
}

int
__pmSendResult(int fd, int from, const pmResult *result)
{
    return __pmSendResult_ctx(NULL, fd, from, result);
}

/*
 * Internal variant of __pmSendHighResResult() with current context.
 */
int
__pmSendHighResResult_ctx(__pmContext *ctxp, int fd, int from, const pmHighResResult *result)
{
    __pmPDU		*pdubuf = NULL;
    highres_result_t	*pp;
    int			sts;

    if (ctxp != NULL)
	PM_ASSERT_IS_LOCKED(ctxp->c_lock);

    if (pmDebugOptions.pdu)
	__pmDumpHighResResult_ctx(ctxp, stderr, result);
    if ((sts = __pmEncodeHighResResult(result, &pdubuf)) < 0)
	return sts;
    pp = (highres_result_t *)pdubuf;
    pp->hdr.from = from;
    sts = __pmXmitPDU(fd, pdubuf);
    __pmUnpinPDUBuf(pdubuf);
    return sts;
}

int
__pmSendHighResResult(int fd, int from, const pmHighResResult *result)
{
    return __pmSendHighResResult_ctx(NULL, fd, from, result);
}

#if defined(HAVE_64BIT_PTR)
static int
__pmDecodeValueSet(__pmPDU *pdubuf, int pdulen, __pmPDU *data, char *pduend,
		int numpmid, int preamble, int unaligned, pmValueSet *vset[])
{
    char	*newbuf;
    int		valfmt;
    int		vindex;
    int		numval;
    int		need;
    int		i, j;
/*
 * Note: all sizes are in units of bytes ... beware that 'data' is in
 *	 units of __pmPDU
 */
    int		vsize;		/* size of vlist_t's in PDU buffer */
    int		nvsize;		/* size of pmValue's after decode */
    int		offset;		/* differences in sizes */
    int		vbsize;		/* size of pmValueBlocks */
    char	*vsplit;	/* vlist/valueblock division point */
    size_t	check;
    pmValueSet	*nvsp;
    vlist_t	*vlp;

    vsplit = pduend;	/* smallest observed value block pointer */
    nvsize = vsize = vbsize = 0;
    for (i = 0; i < numpmid; i++) {
	vlp = (vlist_t *)&data[vsize/sizeof(__pmPDU)];

	check = sizeof(*vlp) - sizeof(vlp->vlist) - sizeof(int);
	if (check > (pduend - (char *)vlp)) {
	    if (pmDebugOptions.pdu && pmDebugOptions.desperate)
		fprintf(stderr, "%s: Bad: pmid[%d] outer vlp past end of "
				"PDU buffer\n", "__pmDecodeValueSet", i);
	    return PM_ERR_IPC;
	}

	vsize += sizeof(vlp->pmid) + sizeof(vlp->numval);
	nvsize += sizeof(pmValueSet);
	numval = ntohl(vlp->numval);
	valfmt = ntohl(vlp->valfmt);
	if (pmDebugOptions.pdu && pmDebugOptions.desperate) {
	    pmID	pmid = __ntohpmID(vlp->pmid);
	    char	strbuf[20];
	    fprintf(stderr, "vlist[%d] pmid: %s numval: %d",
			i, pmIDStr_r(pmid, strbuf, sizeof(strbuf)), numval);
	}
	/* numval may be negative - it holds an error code in that case */
	if (numval > pdulen) {
	    if (pmDebugOptions.pdu && pmDebugOptions.desperate)
		fprintf(stderr, "%s: Bad: pmid[%d] numval=%d > len=%d\n",
				"__pmDecodeValueSet", i, numval, pdulen);
	    return PM_ERR_IPC;
	}
	if (numval > 0) {
	    if (sizeof(*vlp) - sizeof(vlp->vlist) > (pduend - (char *)vlp)) {
		if (pmDebugOptions.pdu && pmDebugOptions.desperate)
		    fprintf(stderr, "%s: Bad: pmid[%d] inner vlp past end of "
				    "PDU buffer\n", "__pmDecodeValueSet", i);
		return PM_ERR_IPC;
	    }
	    check = (INT_MAX - sizeof(*vlp)) / sizeof(__pmValue_PDU);
	    if (numval >= check) {
		if (pmDebugOptions.pdu && pmDebugOptions.desperate)
		    fprintf(stderr, "%s: Bad: pmid[%d] numval=%d > max=%ld\n",
				    "", i, numval, (long)check);
		return PM_ERR_IPC;
	    }
	    vsize += sizeof(vlp->valfmt) + numval * sizeof(__pmValue_PDU);
	    nvsize += (numval - 1) * sizeof(pmValue);

	    if (pmDebugOptions.pdu && pmDebugOptions.desperate)
		fprintf(stderr, " valfmt: %s",
			valfmt == PM_VAL_INSITU ? "insitu" : "ptr");

	    if (valfmt != PM_VAL_INSITU) {
		for (j = 0; j < numval; j++) {
		    __pmValue_PDU *pduvp;
		    pmValueBlock *pduvbp;

		    pduvp = &vlp->vlist[j];
		    check = (size_t)(pduend - (char *)pduvp);
		    if (sizeof(__pmValue_PDU) > check) {
			if (pmDebugOptions.pdu && pmDebugOptions.desperate)
			    fprintf(stderr, "%s: Bad: pmid[%d] value[%d] "
					    "initial pduvp past end of "
					    "PDU buffer\n",
					    "__pmDecodeValueSet", i, j);
			return PM_ERR_IPC;
		    }
		    vindex = ntohl(pduvp->value.lval);
		    if (vindex < 0 || vindex > pdulen) {
			if (pmDebugOptions.pdu && pmDebugOptions.desperate)
			    fprintf(stderr, "%s: Bad: pmid[%d] value[%d] "
					    "vindex=%d\n",
					    "__pmDecodeValueSet", i, j, vindex);
			return PM_ERR_IPC;
		    }
		    pduvbp = (pmValueBlock *)&pdubuf[vindex];
		    if (vsplit > (char *)pduvbp)
			vsplit = (char *)pduvbp;
		    check = (size_t)(pduend - (char *)pduvbp);
		    if (sizeof(unsigned int) > check) {
			if (pmDebugOptions.pdu && pmDebugOptions.desperate)
			    fprintf(stderr, "%s: Bad: pmid[%d] value[%d] "
					    "second pduvp past end of "
					    "PDU buffer\n",
					    "__pmDecodeValueSet", i, j);
			return PM_ERR_IPC;
		    }
		    __ntohpmValueBlock(pduvbp);
		    if (pduvbp->vlen < PM_VAL_HDR_SIZE ||
			pduvbp->vlen > pdulen) {
			if (pmDebugOptions.pdu && pmDebugOptions.desperate)
			    fprintf(stderr, "%s: Bad: pmid[%d] value[%d] "
					    "vlen=%d\n", "__pmDecodeValueSet",
					    i, j, pduvbp->vlen);
			return PM_ERR_IPC;
		    }
		    if (pduvbp->vlen > (size_t)(pduend - (char *)pduvbp)) {
			if (pmDebugOptions.pdu && pmDebugOptions.desperate)
			    fprintf(stderr, "%s: Bad: pmid[%d] value[%d] "
					    "pduvp past end of PDU buffer\n",
					    "__pmDecodeValueSet", i, j);
			return PM_ERR_IPC;
		    }
		    vbsize += PM_PDU_SIZE_BYTES(pduvbp->vlen);
		    if (pmDebugOptions.pdu && pmDebugOptions.desperate) {
			fprintf(stderr, " len: %d type: %d",
			    pduvbp->vlen - PM_VAL_HDR_SIZE, pduvbp->vtype);
		    }
		}
	    }
	}
	if (pmDebugOptions.pdu && pmDebugOptions.desperate) {
	    fputc('\n', stderr);
	}
    }

    need = nvsize + vbsize;
    offset = preamble + vsize;

    if (pmDebugOptions.pdu && pmDebugOptions.desperate) {
	fprintf(stderr, "need: %d vsize: %d nvsize: %d vbsize: %d "
			"offset: %d pdulen: %d pduend: %p vsplit: %p "
			"(diff %d) pdubuf: %p (diff %d)\n",
			need, vsize, nvsize, vbsize, offset, pdulen, pduend,
			vsplit, (int)(pduend-vsplit),
			pdubuf, (int)(pduend-(char *)pdubuf));
    }

    if (need < 0 ||
	vsize > INT_MAX / sizeof(__pmPDU) ||
	vbsize > INT_MAX / sizeof(pmValueBlock) ||
	offset != pdulen - (pduend - vsplit) ||
	offset + vbsize != pduend - (char *)pdubuf) {
	if (pmDebugOptions.pdu && pmDebugOptions.desperate) {
	    if (need < 0)
		fprintf(stderr, "%s: Bad: need (%d) < 0\n",
				"__pmDecodeValueSet", need);
	    if (vsize > INT_MAX / sizeof(__pmPDU))
		fprintf(stderr, "%s: Bad: vsize (%d) > %d\n",
				"__pmDecodeValueSet", vsize,
				(int)(INT_MAX / sizeof(__pmPDU)));
	    if (vbsize > INT_MAX / sizeof(pmValueBlock))
		fprintf(stderr, "%s: Bad: vbsize (%d) > %d\n",
				"__pmDecodeValueSet", vbsize,
				(int)(INT_MAX / sizeof(pmValueBlock)));
	    if (offset != pdulen - (pduend - vsplit))
		fprintf(stderr, "%s: Bad: offset (%d) != %d\n",
				"__pmDecodeValueSet", offset,
				(int)(pdulen - (pduend - vsplit)));
	    if (offset + vbsize != pduend - (char *)pdubuf)
		fprintf(stderr, "%s: Bad: offset+vbsize (%d) "
				"!= pduend-pdubuf (%d)\n",
				"__pmDecodeValueSet", (int)(offset + vbsize),
				(int)(pduend - (char *)pdubuf));
	}
	return PM_ERR_IPC;
    }

    /* the original pdubuf is already pinned so we won't allocate that again */
    if ((newbuf = (char *)__pmFindPDUBuf(need)) == NULL)
	return -oserror();

    /*
     * At this point, we have verified the contents of the incoming PDU and
     * the following is set up ...
     *
     * From the original PDU buffer ...
     * :-----:---------------------:----------------:---------------------:
     * : Hdr : timestamp + numpmid : ... vlists ... : .. pmValueBlocks .. :
     * :-----:---------------------:----------------:---------------------:
     *                              <---  vsize ---> <----   vbsize  ---->
     *                                    bytes              bytes
     *
     * and in the new PDU buffer we are going to build ...
     * :---------------------:---------------------:
     * : ... pmValueSets ... : .. pmValueBlocks .. :
     * :---------------------:---------------------:
     *  <---   nvsize    ---> <----   vbsize  ---->
     *         bytes                  bytes
     */

    if (vbsize) {
	/* pmValueBlocks (if any) are copied across "as is" */
	vindex = vsize / sizeof(__pmPDU);
	memcpy((void *)&newbuf[nvsize], (void *)&data[vindex], vbsize);
    }

    /*
     * offset is a bit tricky ... _add_ the expansion due to the
     * different sizes of the vlist_t and pmValueSet, and _subtract_
     * the PDU header and result timestamp/numpmid fields ...
     */
    offset = nvsize - vsize - unaligned;
    nvsize = vsize = 0;
    for (i = 0; i < numpmid; i++) {
	vlp = (vlist_t *)&data[vsize/sizeof(__pmPDU)];
	nvsp = (pmValueSet *)&newbuf[nvsize];
	vset[i] = nvsp;
	nvsp->pmid = __ntohpmID(vlp->pmid);
	nvsp->numval = ntohl(vlp->numval);
	if (pmDebugOptions.pdu && pmDebugOptions.desperate) {
	    char	strbuf[20];
	    fprintf(stderr, "new vlist[%d] pmid: %s numval: %d",
			i, pmIDStr_r(nvsp->pmid, strbuf, sizeof(strbuf)),
			nvsp->numval);
	}

	vsize += sizeof(nvsp->pmid) + sizeof(nvsp->numval);
	nvsize += sizeof(pmValueSet);
	if (nvsp->numval > 0) {
	    nvsp->valfmt = ntohl(vlp->valfmt);
	    if (pmDebugOptions.pdu && pmDebugOptions.desperate)
		fprintf(stderr, " valfmt: %s",
			    nvsp->valfmt == PM_VAL_INSITU ? "insitu" : "ptr");
	    vsize += sizeof(nvsp->valfmt) + nvsp->numval * sizeof(__pmValue_PDU);
	    nvsize += (nvsp->numval - 1) * sizeof(pmValue);
	    for (j = 0; j < nvsp->numval; j++) {
		__pmValue_PDU	*vp = &vlp->vlist[j];
		pmValue		*nvp = &nvsp->vlist[j];

		nvp->inst = ntohl(vp->inst);
		if (nvsp->valfmt == PM_VAL_INSITU) {
		    nvp->value.lval = ntohl(vp->value.lval);
		    if (pmDebugOptions.pdu && pmDebugOptions.desperate)
			fprintf(stderr, " value: %d", nvp->value.lval);
		}
		else if (nvsp->valfmt == PM_VAL_DPTR ||
			 nvsp->valfmt == PM_VAL_SPTR) {
		    /*
		     * in the input PDU buffer, lval is an index to the
		     * start of the pmValueBlock, in units of __pmPDU
		     */
		    vindex = sizeof(__pmPDU) * ntohl(vp->value.lval) + offset;
		    nvp->value.pval = (pmValueBlock *)&newbuf[vindex];
		    if (pmDebugOptions.pdu && pmDebugOptions.desperate) {
			int		k, len;
			len = nvp->value.pval->vlen - PM_VAL_HDR_SIZE;
			fprintf(stderr, " len: %d type: %d value: 0x", len,
				nvp->value.pval->vtype);
			for (k = 0; k < len; k++)
			    fprintf(stderr, "%02x", nvp->value.pval->vbuf[k]);
		    }
		}
		else {
		    if (pmDebugOptions.pdu && pmDebugOptions.desperate)
			fprintf(stderr, " botch: valfmt=%d\n", nvsp->valfmt);
		    return PM_ERR_IPC;
		}
	    }
	}
	if (pmDebugOptions.pdu && pmDebugOptions.desperate) {
	    fputc('\n', stderr);
	}
    }
    if (numpmid == 0)
	__pmUnpinPDUBuf(newbuf);
    return 0;
}

#elif defined(HAVE_32BIT_PTR)

static int
__pmDecodeValueSet(__pmPDU *pdubuf, int pdulen, __pmPDU *data, char *pduend,
		int numpmid, int preamble, int unaligned, pmValueSet *vset[])
{
    pmValueSet	*vsp;		/* vlist_t == pmValueSet */
    char	*vsplit;	/* vlist/valueblock division point */
    vlist_t	*vlp = (vlist_t *)data;
    size_t	check;
    int		i, j;
    int		vindex;
    int		vsize = 0;	/* size of vlist_t's in PDU buffer */

    /*
     * Fix up any pointers in pmValueBlocks (currently offsets into
     * the PDU buffer) by adding the base address of the PDU buffer.
     */
    vsplit = pduend;
    for (i = 0; i < numpmid; i++) {
	check = sizeof(*vlp) - sizeof(vlp->vlist) - sizeof(int);
	if (check > (pduend - (char *)vlp)) {
	    if (pmDebugOptions.pdu && pmDebugOptions.desperate)
		fprintf(stderr, "%s: Bad: pmid[%d] outer vlp past end of "
				"__pmDecodeValueSet", "PDU buffer\n", i);
	    return PM_ERR_IPC;
	}

	vsp = vset[i] = (pmValueSet *)vlp;
	vsp->pmid = __ntohpmID(vsp->pmid);
	vsp->numval = ntohl(vsp->numval);
	/* numval may be negative - it holds an error code in that case */
	if (vsp->numval > pdulen) {
	    if (pmDebugOptions.pdu && pmDebugOptions.desperate)
		fprintf(stderr, "%s: Bad: pmid[%d] numval=%d > len=%d\n",
				"__pmDecodeValueSet", i, vsp->numval, pdulen);
	    return PM_ERR_IPC;
	}

	vsize += sizeof(vsp->pmid) + sizeof(vsp->numval);
	if (vsp->numval > 0) {
	    if (sizeof(*vlp) - sizeof(vlp->vlist) > (pduend - (char *)vlp)) {
		if (pmDebugOptions.pdu && pmDebugOptions.desperate)
		    fprintf(stderr, "%s: Bad: pmid[%d] inner vlp past end of "
				    "PDU buffer\n", "__pmDecodeValueSet", i);
		return PM_ERR_IPC;
	    }
	    check = (INT_MAX - sizeof(*vlp)) / sizeof(__pmValue_PDU);
	    if (vsp->numval >= check) {
		if (pmDebugOptions.pdu && pmDebugOptions.desperate)
		    fprintf(stderr, "%s: Bad: pmid[%d] numval=%d > max=%ld\n",
				    "__pmDecodeValueSet",
				    i, vsp->numval, (long)check);
		return PM_ERR_IPC;
	    }
	    vsp->valfmt = ntohl(vsp->valfmt);
	    vsize += sizeof(vsp->valfmt) + vsp->numval * sizeof(__pmValue_PDU);
	    for (j = 0; j < vsp->numval; j++) {
		__pmValue_PDU *pduvp;
		pmValueBlock *pduvbp;

		pduvp = &vsp->vlist[j];
		if (sizeof(__pmValue_PDU) > (size_t)(pduend - (char *)pduvp)) {
		    if (pmDebugOptions.pdu && pmDebugOptions.desperate)
			fprintf(stderr, "%s: Bad: pmid[%d] value[%d] initial "
					"pduvp past end of PDU buffer\n",
					"__pmDecodeValueSet", i, j);
		    return PM_ERR_IPC;
		}

		pduvp->inst = ntohl(pduvp->inst);
		if (vsp->valfmt == PM_VAL_INSITU) {
		    pduvp->value.lval = ntohl(pduvp->value.lval);
		} else {
		    /* salvage pmValueBlocks from end of PDU */
		    vindex = ntohl(pduvp->value.lval);
		    if (vindex < 0 || vindex > pdulen) {
			if (pmDebugOptions.pdu && pmDebugOptions.desperate)
			    fprintf(stderr, "%s: Bad: pmid[%d] value[%d] "
					    "vindex=%d\n",
					    "__pmDecodeValueSet", i, j, vindex);
			return PM_ERR_IPC;
		    }
		    pduvbp = (pmValueBlock *)&pdubuf[vindex];
		    if (vsplit > (char *)pduvbp)
			vsplit = (char *)pduvbp;
		    check = (size_t)(pduend - (char *)pduvbp);
		    if (sizeof(unsigned int) > check) {
			if (pmDebugOptions.pdu && pmDebugOptions.desperate)
			    fprintf(stderr, "%s: Bad: pmid[%d] value[%d] "
					    "second pduvp past end of "
					    "PDU buffer\n",
					    "__pmDecodeValueSet", i, j);
			return PM_ERR_IPC;
		    }
		    __ntohpmValueBlock(pduvbp);
		    if (pduvbp->vlen < PM_VAL_HDR_SIZE ||
			pduvbp->vlen > pdulen) {
			if (pmDebugOptions.pdu && pmDebugOptions.desperate)
			    fprintf(stderr, "%s: Bad: pmid[%d] value[%d] "
					    "vlen=%d\n", "__pmDecodeValueSet",
					    i, j, pduvbp->vlen);
			return PM_ERR_IPC;
		    }
		    if (pduvbp->vlen > (size_t)(pduend - (char *)pduvbp)) {
			if (pmDebugOptions.pdu && pmDebugOptions.desperate)
			    fprintf(stderr, "%s: Bad: pmid[%d] value[%d] "
					    "pduvp past end of PDU buffer\n",
					    "__pmDecodeValueSet", i, j);
			return PM_ERR_IPC;
		    }
		    pduvp->value.pval = pduvbp;
		}
	    }
	    vlp = (vlist_t *)((__psint_t)vlp +
			sizeof(*vlp) + (vsp->numval-1)*sizeof(vlp->vlist[0]));
	}
	else {
	    vlp = (vlist_t *)((__psint_t)vlp +
			sizeof(vlp->pmid) + sizeof(vlp->numval));
	}
    }
    if (numpmid > 0) {
	check = preamble + vsize;
	if (check != pdulen - (pduend - vsplit)) {
	    if (pmDebugOptions.pdu && pmDebugOptions.desperate)
		fprintf(stderr, "%s: Bad: vsplit past end of PDU buffer\n",
				"__pmDecodeValueSet");
	    return PM_ERR_IPC;
	}
	/*
	 * PDU buffer already pinned on entry, pin again so that
	 * the caller can safely call _both_ pmFree*Result() and
	 * __pmUnpinPDUBuf() ... refer to thread-safe notes above.
	 */
	__pmPinPDUBuf(pdubuf);
    }

    return 0;
}

#else
#error Bozo - unexpected sizeof pointer!! - commented for static checking
#endif

/*
 * Internal variant of __pmDecodeResult() with current context.
 *
 * Enter here with pdubuf already pinned ... result may point into
 * _another_ pdu buffer that is pinned on exit
 */
int
__pmDecodeResult_ctx(__pmContext *ctxp, __pmPDU *pdubuf, pmResult **result)
{
    int		sts;
    int		numpmid;	/* number of metrics */
    char	*pduend;	/* end pointer for incoming buffer */
    size_t	bytes, nopad;
    result_t	*pp;
#if 0	// TODO when pr,*result -> __pmResult
    __pmResult	*pr;
#else
    __pmResult	*__pr;
    pmResult	*pr;
#endif

    if (ctxp != NULL)
	PM_ASSERT_IS_LOCKED(ctxp->c_lock);

    pp = (result_t *)pdubuf;
    pduend = (char *)pdubuf + pp->hdr.len;
    bytes = sizeof(result_t) - sizeof(__pmPDU);
    if (pduend - (char *)pdubuf < bytes) {
	if (pmDebugOptions.pdu && pmDebugOptions.desperate)
	    fprintf(stderr, "%s: Bad: len=%d smaller than min %d\n",
			    "__pmDecodeResult", pp->hdr.len, (int)bytes);
	return PM_ERR_IPC;
    }

    numpmid = ntohl(pp->numpmid);
    if (numpmid < 0 || numpmid > pp->hdr.len) {
	if (pmDebugOptions.pdu && pmDebugOptions.desperate)
	    fprintf(stderr, "%s: Bad: numpmid=%d negative or not smaller "
			    "than PDU len %d\n", "__pmDecodeResult",
			    numpmid, pp->hdr.len);
	return PM_ERR_IPC;
    }
    bytes = (INT_MAX - sizeof(pmResult)) / sizeof(pmValueSet *);
    if (numpmid >= bytes) {
	if (pmDebugOptions.pdu && pmDebugOptions.desperate)
	    fprintf(stderr, "%s: Bad: numpmid=%d larger than max %ld\n",
			    "__pmDecodeResult", numpmid, (long)bytes);
	return PM_ERR_IPC;
    }

    if ((__pr = (__pmResult *)__pmAllocResult(numpmid)) == NULL)
	return -oserror();

    pr = __pmOffsetResult(__pr);
    pr->numpmid = numpmid;
    pr->timestamp.tv_sec = ntohl(pp->timestamp.tv_sec);
    pr->timestamp.tv_usec = ntohl(pp->timestamp.tv_usec);

    bytes = sizeof(result_t) - sizeof(__pmPDU);
    nopad = sizeof(pp->hdr) + sizeof(pp->timestamp) + sizeof(pp->numpmid);

    if ((sts = __pmDecodeValueSet(pdubuf, pp->hdr.len, pp->data, pduend,
				  numpmid, bytes, nopad, pr->vset)) < 0) {
	pr->numpmid = 0;	/* force no pmValueSet's to free */
	pmFreeResult(pr);
	return sts;
    }

    if (pmDebugOptions.pdu)
	__pmDumpResult_ctx(ctxp, stderr, pr);

    /*
     * Note we return with the input buffer (pdubuf) still pinned and
     * for the 64-bit pointer case the new buffer (newbuf) also pinned -
     * if numpmid != 0 see the thread-safe comments above
     */
    *result = pr;
    return 0;
}

int
__pmDecodeResult(__pmPDU *pdubuf, pmResult **result)
{
    return __pmDecodeResult_ctx(NULL, pdubuf, result);
}

/*
 * Internal variant of __pmDecodeHighResResult() with current context.
 *
 * Enter here with pdubuf already pinned ... result may point into
 * _another_ pdu buffer that is pinned on exit
 */
int
__pmDecodeHighResResult_ctx(__pmContext *ctxp, __pmPDU *pdubuf, pmHighResResult **result)
{
    int			sts;
    int			numpmid;	/* number of metrics */
    char		*pduend;	/* end pointer for incoming buffer */
    size_t		bytes, nopad;
    pmHighResResult	*pr;
    highres_result_t	*pp;

    if (ctxp != NULL)
	PM_ASSERT_IS_LOCKED(ctxp->c_lock);

    pp = (highres_result_t *)pdubuf;
    pduend = (char *)pdubuf + pp->hdr.len;
    bytes = sizeof(highres_result_t) - (sizeof(__pmPDU) * 2);
    if (pduend - (char *)pdubuf < bytes) {
	if (pmDebugOptions.pdu && pmDebugOptions.desperate)
	    fprintf(stderr, "%s: Bad: len=%d smaller than min %d\n",
			    "__pmDecodeHighResResult", pp->hdr.len, (int)bytes);
	return PM_ERR_IPC;
    }

    numpmid = ntohl(pp->numpmid);
    if (numpmid < 0 || numpmid > pp->hdr.len) {
	if (pmDebugOptions.pdu && pmDebugOptions.desperate)
	    fprintf(stderr, "%s: Bad: numpmid=%d negative or not smaller "
			    "than PDU len %d\n", "__pmDecodeHighResResult",
			    numpmid, pp->hdr.len);
	return PM_ERR_IPC;
    }
    bytes = (INT_MAX - sizeof(pmHighResResult)) / sizeof(pmValueSet *);
    if (numpmid >= bytes) {
	if (pmDebugOptions.pdu && pmDebugOptions.desperate)
	    fprintf(stderr, "%s: Bad: numpmid=%d larger than max %ld\n",
			    "__pmDecodeHighResResult", numpmid, (long)bytes);
	return PM_ERR_IPC;
    }

    if ((pr = (pmHighResResult *)malloc(sizeof(pmHighResResult) +
			 	(numpmid - 1) * sizeof(pmValueSet *))) == NULL)
	return -oserror();

    pr->numpmid = numpmid;
    __ntohll((char *)&pp->timestamp.tv_sec);
    pr->timestamp.tv_sec = pp->timestamp.tv_sec;
    __ntohll((char *)&pp->timestamp.tv_nsec);
    pr->timestamp.tv_nsec = pp->timestamp.tv_nsec;

    bytes = sizeof(highres_result_t) - (sizeof(__pmPDU) * 2);
    nopad = sizeof(pp->hdr) + sizeof(pp->numpmid) + sizeof(pp->timestamp);

    if ((sts = __pmDecodeValueSet(pdubuf, pp->hdr.len, pp->data, pduend,
				  numpmid, bytes, nopad, pr->vset)) < 0) {
	free(pr);
	return sts;
    }

    if (pmDebugOptions.pdu)
	__pmDumpHighResResult_ctx(ctxp, stderr, pr);

    /*
     * Note we return with the input buffer (pdubuf) still pinned and
     * for the 64-bit pointer case the new buffer (newbuf) also pinned -
     * if numpmid != 0 see the thread-safe comments above
     */
    *result = pr;
    return 0;
}

int
__pmDecodeHighResResult(__pmPDU *pdubuf, pmHighResResult **result)
{
    return __pmDecodeHighResResult_ctx(NULL, pdubuf, result);
}
