QA output created by 367
+++++++++++++++++++++++++++
+ Mode: PDU_BINARY Pass 0 +
+++++++++++++++++++++++++++
[SERVER]pmGetPDU: ERROR fd=<n> len=16 from=CLIENT
000:       10     7000   CLIENT     3039 
+ PDU_ERROR: code=12345
[SERVER]pmXmitPDU: ERROR fd=<n> len=16
000:       10     7000   SERVER     3039 
[SERVER]pmGetPDU: ERROR fd=<n> len=16 from=CLIENT
000:       10     7000   CLIENT ffffcfc7 
+ PDU_ERROR: code=-12345
[SERVER]pmXmitPDU: ERROR fd=<n> len=16
000:       10     7000   SERVER ffffcfc7 
[SERVER]pmGetPDU: RESULT fd=<n> len=208 from=CLIENT
000:       d0     7001   CLIENT    1a5e0    1e240        7     dead        1 
008:        0 ffffffff      4d2     beef        3        0        2      929 
016:        4      d80        8     11d7        0        1        1 ffffffff 
024:       2a 1ec72315        1        1 ffffffff       2c 3fc00000        1 
032:        1 ffffffff       2f   3ffc00        1        1 ffffffff       31 
040: deadcafe ffffcfc7  6000006 30007e7e  300000c 87654321 12345678  4000008 
048: 63691a7d  500000c 599b979b 8f205a13 
pmResult dump from ADDR timestamp: 108000.123456 06:00:00.123 numpmid: 7
  0.55.685 (<noname>): numval: 1 valfmt: 0 vlist[]:
   value 1234 0 0x4d2
  0.47.751 (<noname>): numval: 3 valfmt: 0 vlist[]:
    inst [2 or ???] value 2345 0 0x929
    inst [4 or ???] value 3456 0 0xd80
    inst [8 or ???] value 4567 0 0x11d7
  0.0.0 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value "0"
  123.456.789 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value 9756277977086449272
  255.0.0 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value 4.3000001e+21
  0.4095.0 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value 4.56e+123
  378.2930.766 (<noname>): Generic error, already reported above
+ PDU_RESULT:
pmResult dump from ADDR timestamp: 108000.123456 06:00:00.123 numpmid: 7
  0.55.685 (<noname>): numval: 1 valfmt: 0 vlist[]:
   value 1234 0 0x4d2
  0.47.751 (<noname>): numval: 3 valfmt: 0 vlist[]:
    inst [2 or ???] value 2345 0 0x929
    inst [4 or ???] value 3456 0 0xd80
    inst [8 or ???] value 4567 0 0x11d7
  0.0.0 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value "0"
  123.456.789 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value 9756277977086449272
  255.0.0 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value 4.3000001e+21
  0.4095.0 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value 4.56e+123
  378.2930.766 (<noname>): Generic error, already reported above
pmResult dump from ADDR timestamp: 108000.123456 06:00:00.123 numpmid: 7
  0.55.685 (<noname>): numval: 1 valfmt: 0 vlist[]:
   value 1234 0 0x4d2
  0.47.751 (<noname>): numval: 3 valfmt: 0 vlist[]:
    inst [2 or ???] value 2345 0 0x929
    inst [4 or ???] value 3456 0 0xd80
    inst [8 or ???] value 4567 0 0x11d7
  0.0.0 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value "0"
  123.456.789 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value 9756277977086449272
  255.0.0 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value 4.3000001e+21
  0.4095.0 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value 4.56e+123
  378.2930.766 (<noname>): Generic error, already reported above
[SERVER]pmXmitPDU: RESULT fd=<n> len=208
000:       d0     7001   SERVER    1a5e0    1e240        7     dead        1 
008:        0 ffffffff      4d2     beef        3        0        2      929 
016:        4      d80        8     11d7        0        1        1 ffffffff 
024:       2a 1ec72315        1        1 ffffffff       2c 3fc00000        1 
032:        1 ffffffff       2f   3ffc00        1        1 ffffffff       31 
040: deadcafe ffffcfc7  6000006 30007e7e  300000c 87654321 12345678  4000008 
048: 63691a7d  500000c 599b979b 8f205a13 
[SERVER]pmGetPDU: HIGHRES_RESULT fd=<n> len=216 from=CLIENT
000:       d8     7015   CLIENT  7000000        0 e0a50100        0 15cd5b07 
008: adde0000  1000000        0 ffffffff d2040000 efbe0000  3000000        0 
016:  2000000 29090000  4000000      d80        8     11d7        0  1000000 
024:  1000000 ffffffff 2c000000 1523c71e  1000000  1000000 ffffffff 2e000000 
032:     c03f  1000000  1000000 ffffffff 31000000   fc3f00  1000000  1000000 
040: ffffffff 33000000 fecaadde c7cfffff  6000006 7e7e0030  c000003 21436587 
048: 78563412  8000004 63691a7d  500000c 599b979b 8f205a13 
pmHighResResult dump from ADDR timestamp: 108000.123456789 06:00:00.123456789 numpmid: 7
  0.55.685 (<noname>): numval: 1 valfmt: 0 vlist[]:
   value 1234 0 0x4d2
  0.47.751 (<noname>): numval: 3 valfmt: 0 vlist[]:
    inst [2 or ???] value 2345 0 0x929
    inst [4 or ???] value 3456 0 0xd80
    inst [8 or ???] value 4567 0 0x11d7
  0.0.0 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value "0"
  123.456.789 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value 9756277977086449272
  255.0.0 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value 4.3000001e+21
  0.4095.0 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value 4.56e+123
  378.2930.766 (<noname>): Generic error, already reported above
+ PDU_HIGHRES_RESULT:
pmHighResResult dump from ADDR timestamp: 108000.123456789 06:00:00.123456789 numpmid: 7
  0.55.685 (<noname>): numval: 1 valfmt: 0 vlist[]:
   value 1234 0 0x4d2
  0.47.751 (<noname>): numval: 3 valfmt: 0 vlist[]:
    inst [2 or ???] value 2345 0 0x929
    inst [4 or ???] value 3456 0 0xd80
    inst [8 or ???] value 4567 0 0x11d7
  0.0.0 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value "0"
  123.456.789 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value 9756277977086449272
  255.0.0 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value 4.3000001e+21
  0.4095.0 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value 4.56e+123
  378.2930.766 (<noname>): Generic error, already reported above
pmHighResResult dump from ADDR timestamp: 108000.123456789 06:00:00.123456789 numpmid: 7
  0.55.685 (<noname>): numval: 1 valfmt: 0 vlist[]:
   value 1234 0 0x4d2
  0.47.751 (<noname>): numval: 3 valfmt: 0 vlist[]:
    inst [2 or ???] value 2345 0 0x929
    inst [4 or ???] value 3456 0 0xd80
    inst [8 or ???] value 4567 0 0x11d7
  0.0.0 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value "0"
  123.456.789 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value 9756277977086449272
  255.0.0 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value 4.3000001e+21
  0.4095.0 (<noname>): numval: 1 valfmt: 1 vlist[]:
   value 4.56e+123
  378.2930.766 (<noname>): Generic error, already reported above
[SERVER]pmXmitPDU: HIGHRES_RESULT fd=<n> len=216
000:       d8     7015   SERVER  7000000        0 e0a50100        0 15cd5b07 
008: adde0000  1000000        0 ffffffff d2040000 efbe0000  3000000        0 
016:  2000000 29090000  4000000      d80        8     11d7        0  1000000 
024:  1000000 ffffffff 2c000000 1523c71e  1000000  1000000 ffffffff 2e000000 
032:     c03f  1000000  1000000 ffffffff 31000000   fc3f00  1000000  1000000 
040: ffffffff 33000000 fecaadde c7cfffff  6000006 7e7e0030  c000003 21436587 
048: 78563412  8000004 63691a7d  500000c 599b979b 8f205a13 
[SERVER]pmGetPDU: PROFILE fd=<n> len=72 from=CLIENT
000:       48     7002   CLIENT       2a        1        2        0 deadcafe 
008:        0        2        0     face        1        1        0        1 
016:        2      400 
+ PDU_PROFILE: ctxnum=42
Dump Instance Profile state=EXCLUDE, 2 profiles
	Profile [0] indom=-559035650 [378.3001086] state=INCLUDE 2 instances
		Instances: [1] [2]
	Profile [1] indom=64206 [0.64206] state=EXCLUDE 1 instances
		Instances: [1024]
[SERVER]pmXmitPDU: PROFILE fd=<n> len=72
000:       48     7002   SERVER       2a        1        2        0 deadcafe 
008:        0        2        0     face        1        1        0        1 
016:        2      400 
[SERVER]pmGetPDU: FETCH fd=<n> len=52 from=CLIENT
000:       34     7003   CLIENT       2b        0        0        6        0 
008: 1ec72315 3fc00000   3ffc00      3ff ffffffff 
+ PDU_FETCH: ctxnum=43 now=0.000000 00:00:00.000 numpmid=6
+ PMIDs: 0.0.0 123.456.789 255.0.0 0.4095.0 0.0.1023 PM_ID_NULL
[SERVER]pmXmitPDU: FETCH fd=<n> len=52
000:       34     7003   SERVER       2b        0        0        6        0 
008: 1ec72315 3fc00000   3ffc00      3ff ffffffff 
[SERVER]pmGetPDU: HIGHRES_FETCH fd=<n> len=52 from=CLIENT
000:       34     7014   CLIENT       2b        0        0        6        0 
008: 1ec72315 3fc00000   3ffc00      3ff ffffffff 
+ PDU_HIGHRES_FETCH: ctxnum=43 numpmid=6
+ PMIDs: 0.0.0 123.456.789 255.0.0 0.4095.0 0.0.1023 PM_ID_NULL
[SERVER]pmXmitPDU: HIGHRES_FETCH fd=<n> len=52
000:       34     7014   SERVER       2b        0        0        6        0 
008: 1ec72315 3fc00000   3ffc00      3ff ffffffff 
[SERVER]pmGetPDU: DESC_REQ fd=<n> len=16 from=CLIENT
000:       10     7004   CLIENT deadbeef 
+ PDU_DESC_REQ: pmid=378.2927.751
[SERVER]pmXmitPDU: DESC_REQ fd=<n> len=16
000:       10     7004   SERVER deadbeef 
[SERVER]pmGetPDU: DESC fd=<n> len=32 from=CLIENT
000:       20     7005   CLIENT deadbeef        2     face        1 1f025000 
+ PDU_DESC:     Data Type: 64-bit int  InDom: 0.64206 0xface
    Semantics: counter  Units: Mbyte / hour
[SERVER]pmXmitPDU: DESC fd=<n> len=32
000:       20     7005   SERVER deadbeef        2     face        1 1f025000 
[SERVER]pmGetPDU: DESC_IDS fd=<n> len=44 from=CLIENT
000:       2c     7016   CLIENT ffffffff  6000000        0 1523c71e     c03f 
008:   3ffc00      3ff ffffffff 
+ PDU_DESC_IDS: sts arg=-1
IDlist dump: numids = 6
  PMID[0]: 0x00000000 0.0.0
  PMID[1]: 0x1ec72315 123.456.789
  PMID[2]: 0x3fc00000 255.0.0
  PMID[3]: 0x003ffc00 0.4095.0
  PMID[4]: 0x000003ff 0.0.1023
  PMID[5]: 0xffffffff PM_ID_NULL
[SERVER]pmXmitPDU: DESC_IDS fd=<n> len=44
000:       2c     7016   SERVER ffffffff  6000000        0 1523c71e     c03f 
008:   3ffc00      3ff ffffffff 
[SERVER]pmGetPDU: DESCS fd=<n> len=56 from=CLIENT
000:       38     7017   CLIENT  2000000 deadbeef  2000000     face  1000000 
008:  10f5200 feedbabe        0     face  3000000  10f2100 
+ PDU_DESCS:     Data Type: 64-bit int  InDom: 0.64206 0xface
    Semantics: counter  Units: Mbyte / hour
    Data Type: 32-bit int  InDom: 0.51966 0xcafe
    Semantics: instant  Units: count x 10^-1^2
[SERVER]pmXmitPDU: DESCS fd=<n> len=56
000:       38     7017   SERVER  2000000 deadbeef  2000000     face  1000000 
008:  10f5200 feedbabe        0     face  3000000  10f2100 
[SERVER]pmGetPDU: INSTANCE_REQ fd=<n> len=32 from=CLIENT
000:       20     7006   CLIENT     face    34bc0    9fbf1     dead        0 
+ PDU_INSTANCE_REQ: indom=0.64206 inst=57005 name=NULL
[SERVER]pmXmitPDU: INSTANCE_REQ fd=<n> len=32
000:       20     7006   SERVER     face    34bc0    9fbf1     dead        0 
[SERVER]pmGetPDU: INSTANCE_REQ fd=<n> len=40 from=CLIENT
000:       28     7006   CLIENT     face    34bc0    9fbf1        0        5 
008: 66697368 6f7e7e7e 
+ PDU_INSTANCE_REQ: indom=0.64206 inst=0 name="fisho"
[SERVER]pmXmitPDU: INSTANCE_REQ fd=<n> len=40
000:       28     7006   SERVER     face    34bc0    9fbf1        0        5 
008: 66697368 6f7e7e7e 
[SERVER]pmGetPDU: INSTANCE_REQ fd=<n> len=32 from=CLIENT
000:       20     7006   CLIENT     face    34bc0    9fbf1        0        0 
+ PDU_INSTANCE_REQ: indom=0.64206 inst=0 name=NULL
[SERVER]pmXmitPDU: INSTANCE_REQ fd=<n> len=32
000:       20     7006   SERVER     face    34bc0    9fbf1        0        0 
[SERVER]pmGetPDU: INSTANCE fd=<n> len=216 from=CLIENT
000:       d8     7007   CLIENT     1234        b        1        5 616c7068 
008: 617e7e7e        2        4 62657461        4        5 67616d6d 617e7e7e 
016:        8       28 6c6f6e67 2d6e6f6e 2d677265 656b2d6c 65747465 722d6e61 
024: 6d652d69 6e2d7468 652d6d69 64646c65       10        5 64656c74 617e7e7e 
032:       20        7 65707369 6c6f6e7e       40        3 7068697e       80 
040:        2 6d757e7e      100        6 6c616d62 64617e7e      200        5 
048: 6f6d6567 617e7e7e      400        5 74686574 617e7e7e 
+ PDU_INSTANCE: pmInResult dump from ADDR for InDom 0.4660 (0x1234), numinst=11
  [0] inst=1 name="alpha"
  [1] inst=2 name="beta"
  [2] inst=4 name="gamma"
  [3] inst=8 name="long-non-greek-letter-name-in-the-middle"
  [4] inst=16 name="delta"
  [5] inst=32 name="epsilon"
  [6] inst=64 name="phi"
  [7] inst=128 name="mu"
  [8] inst=256 name="lambda"
  [9] inst=512 name="omega"
  [10] inst=1024 name="theta"
[SERVER]pmXmitPDU: INSTANCE fd=<n> len=216
000:       d8     7007   SERVER     1234        b        1        5 616c7068 
008: 617e7e7e        2        4 62657461        4        5 67616d6d 617e7e7e 
016:        8       28 6c6f6e67 2d6e6f6e 2d677265 656b2d6c 65747465 722d6e61 
024: 6d652d69 6e2d7468 652d6d69 64646c65       10        5 64656c74 617e7e7e 
032:       20        7 65707369 6c6f6e7e       40        3 7068697e       80 
040:        2 6d757e7e      100        6 6c616d62 64617e7e      200        5 
048: 6f6d6567 617e7e7e      400        5 74686574 617e7e7e 
[SERVER]pmGetPDU: INSTANCE fd=<n> len=216 from=CLIENT
000:       d8     7007   CLIENT     1234        b ffffffff        5 616c7068 
008: 617e7e7e ffffffff        4 62657461 ffffffff        5 67616d6d 617e7e7e 
016: ffffffff       28 6c6f6e67 2d6e6f6e 2d677265 656b2d6c 65747465 722d6e61 
024: 6d652d69 6e2d7468 652d6d69 64646c65 ffffffff        5 64656c74 617e7e7e 
032: ffffffff        7 65707369 6c6f6e7e ffffffff        3 7068697e ffffffff 
040:        2 6d757e7e ffffffff        6 6c616d62 64617e7e ffffffff        5 
048: 6f6d6567 617e7e7e ffffffff        5 74686574 617e7e7e 
+ PDU_INSTANCE: pmInResult dump from ADDR for InDom 0.4660 (0x1234), numinst=11
  [0] inst=-1 name="alpha"
  [1] inst=-1 name="beta"
  [2] inst=-1 name="gamma"
  [3] inst=-1 name="long-non-greek-letter-name-in-the-middle"
  [4] inst=-1 name="delta"
  [5] inst=-1 name="epsilon"
  [6] inst=-1 name="phi"
  [7] inst=-1 name="mu"
  [8] inst=-1 name="lambda"
  [9] inst=-1 name="omega"
  [10] inst=-1 name="theta"
[SERVER]pmXmitPDU: INSTANCE fd=<n> len=216
000:       d8     7007   SERVER     1234        b ffffffff        5 616c7068 
008: 617e7e7e ffffffff        4 62657461 ffffffff        5 67616d6d 617e7e7e 
016: ffffffff       28 6c6f6e67 2d6e6f6e 2d677265 656b2d6c 65747465 722d6e61 
024: 6d652d69 6e2d7468 652d6d69 64646c65 ffffffff        5 64656c74 617e7e7e 
032: ffffffff        7 65707369 6c6f6e7e ffffffff        3 7068697e ffffffff 
040:        2 6d757e7e ffffffff        6 6c616d62 64617e7e ffffffff        5 
048: 6f6d6567 617e7e7e ffffffff        5 74686574 617e7e7e 
[SERVER]pmGetPDU: INSTANCE fd=<n> len=108 from=CLIENT
000:       6c     7007   CLIENT     1234        b        1        0        2 
008:        0        4        0        8        0       10        0       20 
016:        0       40        0       80        0      100        0      200 
024:        0      400        0 
+ PDU_INSTANCE: pmInResult dump from ADDR for InDom 0.4660 (0x1234), numinst=11
  [0] inst=1 name=""
  [1] inst=2 name=""
  [2] inst=4 name=""
  [3] inst=8 name=""
  [4] inst=16 name=""
  [5] inst=32 name=""
  [6] inst=64 name=""
  [7] inst=128 name=""
  [8] inst=256 name=""
  [9] inst=512 name=""
  [10] inst=1024 name=""
[SERVER]pmXmitPDU: INSTANCE fd=<n> len=108
000:       6c     7007   SERVER     1234        b        1        0        2 
008:        0        4        0        8        0       10        0       20 
016:        0       40        0       80        0      100        0      200 
024:        0      400        0 
[SERVER]pmGetPDU: LABEL_REQ fd=<n> len=20 from=CLIENT
000:       14     7012   CLIENT cdab3412  4000000 
+ PDU_LABEL_REQ: ident=305441741 type=0x4: INDOM 72.3451853
[SERVER]pmXmitPDU: LABEL_REQ fd=<n> len=20
000:       14     7012   SERVER cdab3412  4000000 
[SERVER]pmGetPDU: LABEL fd=<n> len=77 from=CLIENT
000:       4d     7013   CLIENT 3412cd7b 10000000        0  1000000 ffffffff 
008:  1000000 34000000 19000000    b0200    90f00 6574227b 7265706d 72757461 
016: 223a2265 636c6563 22737569 7e7e7e7d 
+ PDU_LABEL: ident=2077037108 type=0x10[0] pmLabelSet dump from ADDR inst=-1 nlabels=1
pmLabelSet ADDR json:
    {"temperature":"celcius"}
pmLabelSet ADDR index:
    [0] name(2,11) : value(15,9) [pmid]
[SERVER]pmXmitPDU: LABEL fd=<n> len=77
000:       4d     7013   SERVER 3412cd7b 10000000        0  1000000 ffffffff 
008:  1000000 34000000 19000000    b0200    90f00 6574227b 7265706d 72757461 
016: 223a2265 636c6563 22737569 7e7e7e7d 
[SERVER]pmGetPDU: TEXT_REQ fd=<n> len=20 from=CLIENT
000:       14     7008   CLIENT 12341234        5 
+ PDU_TEXT_REQ: ident=305402420 PMID 72.3332.564 txtype=5
[SERVER]pmXmitPDU: TEXT_REQ fd=<n> len=20
000:       14     7008   SERVER 12341234        5 
[SERVER]pmGetPDU: TEXT fd=<n> len=76 from=CLIENT
000:       4c     7009   CLIENT 43214321 35000000 7972616d 64616820 6c206120 
008: 6974746c 65206c61 6d620a69 74732066 6c656563 65207761 73207768 69746520 
016: 73207361 2e776f6e 7e7e7e0a 
+ PDU_TEXT: ident=1126253345 text="mary had a l ... as white as snow."
[SERVER]pmXmitPDU: TEXT fd=<n> len=76
000:       4c     7009   SERVER 43214321 35000000 7972616d 64616820 6c206120 
008: 6974746c 65206c61 6d620a69 74732066 6c656563 65207761 73207768 69746520 
016: 73207361 2e776f6e 7e7e7e0a 
[SERVER]pmGetPDU: ATTR fd=<n> len=22 from=CLIENT
000:       16     7011   CLIENT        5 70637071 61007e7e 
+ PDU_AUTH: attr=5 length=6 value="pcpqa"
[SERVER]pmXmitPDU: ATTR fd=<n> len=22
000:       16     7011   SERVER        5 70637071 61007e7e 
[SERVER]pmGetPDU: CREDS fd=<n> len=20 from=CLIENT
000:       14     700c   CLIENT        1  1020a0b 
+ PDU_CREDS: sender=CLIENT count=1
+ [0] type=1 a=2 b=10 c=11
[SERVER]pmXmitPDU: CREDS fd=<n> len=20
000:       14     700c   SERVER        1  1020a0b 
[SERVER]pmGetPDU: PMNS_IDS fd=<n> len=44 from=CLIENT
000:       2c     700d   CLIENT       2b        6        0 1ec72315 3fc00000 
008:   3ffc00      3ff ffffffff 
+ PDU_PMNS_IDS: sts arg=43
IDlist dump: numids = 6
  PMID[0]: 0x00000000 0.0.0
  PMID[1]: 0x1ec72315 123.456.789
  PMID[2]: 0x3fc00000 255.0.0
  PMID[3]: 0x003ffc00 0.4095.0
  PMID[4]: 0x000003ff 0.0.1023
  PMID[5]: 0xffffffff PM_ID_NULL
[SERVER]pmXmitPDU: PMNS_IDS fd=<n> len=44
000:       2c     700d   SERVER       2b        6        0 1ec72315 3fc00000 
008:   3ffc00      3ff ffffffff 
[SERVER]pmGetPDU: PMNS_NAMES fd=<n> len=220 from=CLIENT
000:       dc     700e   CLIENT       62        b        b fffffffb        5 
008: 616c7068 617e7e7e fffffffc        4 62657461 fffffffd        5 67616d6d 
016: 617e7e7e fffffffe       28 6c6f6e67 2d6e6f6e 2d677265 656b2d6c 65747465 
024: 722d6e61 6d652d69 6e2d7468 652d6d69 64646c65 ffffffff        5 64656c74 
032: 617e7e7e        0        7 65707369 6c6f6e7e        1        3 7068697e 
040:        2        2 6d757e7e        3        6 6c616d62 64617e7e        4 
048:        5 6f6d6567 617e7e7e        5        5 74686574 617e7e7e 
+ PDU_PMNS_NAMES:
namelist dump: numnames = 11
  name[0]: "alpha"
  name[1]: "beta"
  name[2]: "gamma"
  name[3]: "long-non-greek-letter-name-in-the-middle"
  name[4]: "delta"
  name[5]: "epsilon"
  name[6]: "phi"
  name[7]: "mu"
  name[8]: "lambda"
  name[9]: "omega"
  name[10]: "theta"
statuslist dump: numstatus = 11
  status[0]: -5
  status[1]: -4
  status[2]: -3
  status[3]: -2
  status[4]: -1
  status[5]: 0
  status[6]: 1
  status[7]: 2
  status[8]: 3
  status[9]: 4
  status[10]: 5
[SERVER]pmXmitPDU: PMNS_NAMES fd=<n> len=220
000:       dc     700e   SERVER       62        b        b fffffffb        5 
008: 616c7068 617e7e7e fffffffc        4 62657461 fffffffd        5 67616d6d 
016: 617e7e7e fffffffe       28 6c6f6e67 2d6e6f6e 2d677265 656b2d6c 65747465 
024: 722d6e61 6d652d69 6e2d7468 652d6d69 64646c65 ffffffff        5 64656c74 
032: 617e7e7e        0        7 65707369 6c6f6e7e        1        3 7068697e 
040:        2        2 6d757e7e        3        6 6c616d62 64617e7e        4 
048:        5 6f6d6567 617e7e7e        5        5 74686574 617e7e7e 
[SERVER]pmGetPDU: PMNS_NAMES fd=<n> len=176 from=CLIENT
000:       b0     700e   CLIENT       62        0        b        5 616c7068 
008: 617e7e7e        4 62657461        5 67616d6d 617e7e7e       28 6c6f6e67 
016: 2d6e6f6e 2d677265 656b2d6c 65747465 722d6e61 6d652d69 6e2d7468 652d6d69 
024: 64646c65        5 64656c74 617e7e7e        7 65707369 6c6f6e7e        3 
032: 7068697e        2 6d757e7e        6 6c616d62 64617e7e        5 6f6d6567 
040: 617e7e7e        5 74686574 617e7e7e 
+ PDU_PMNS_NAMES:
namelist dump: numnames = 11
  name[0]: "alpha"
  name[1]: "beta"
  name[2]: "gamma"
  name[3]: "long-non-greek-letter-name-in-the-middle"
  name[4]: "delta"
  name[5]: "epsilon"
  name[6]: "phi"
  name[7]: "mu"
  name[8]: "lambda"
  name[9]: "omega"
  name[10]: "theta"
[SERVER]pmXmitPDU: PMNS_NAMES fd=<n> len=176
000:       b0     700e   SERVER       62        0        b        5 616c7068 
008: 617e7e7e        4 62657461        5 67616d6d 617e7e7e       28 6c6f6e67 
016: 2d6e6f6e 2d677265 656b2d6c 65747465 722d6e61 6d652d69 6e2d7468 652d6d69 
024: 64646c65        5 64656c74 617e7e7e        7 65707369 6c6f6e7e        3 
032: 7068697e        2 6d757e7e        6 6c616d62 64617e7e        5 6f6d6567 
040: 617e7e7e        5 74686574 617e7e7e 
[SERVER]pmGetPDU: PMNS_CHILD fd=<n> len=36 from=CLIENT
000:       24     700f   CLIENT        1        d 6d756d62 6c652e66 756d626c 
008: 657e7e7e 
+ PDU_PMNS_CHILD: name="mumble.fumble" code=1
[SERVER]pmXmitPDU: PMNS_CHILD fd=<n> len=36
000:       24     700f   SERVER        1        d 6d756d62 6c652e66 756d626c 
008: 657e7e7e 
[SERVER]pmGetPDU: PMNS_TRAVERSE fd=<n> len=36 from=CLIENT
000:       24     7010   CLIENT        0        d 666f6f2e 6261722e 736e6f72 
008: 747e7e7e 
+ PDU_PMNS_TRAVERSE: name="foo.bar.snort"
[SERVER]pmXmitPDU: PMNS_TRAVERSE fd=<n> len=36
000:       24     7010   SERVER        0        d 666f6f2e 6261722e 736e6f72 
008: 747e7e7e 
[SERVER]pmGetPDU: LOG_CONTROL fd=<n> len=68 from=0
000:       44     8000        0        b        1      3e8        2     dead 
008: ffffffff     beef        3        2      929        4      d80        8 
016:     11d7 
+ PDU_LOG_CONTROL: control=11 state=1 rate=1000
pmResult dump from ADDR timestamp: NOW TODAY numpmid: 2
  0.55.685 (<noname>): Operation not permitted
  0.47.751 (<noname>): numval: 3 valfmt: 0 vlist[]:
    inst [2 or ???] value 2345 0 0x929
    inst [4 or ???] value 3456 0 0xd80
    inst [8 or ???] value 4567 0 0x11d7
pmResult dump from ADDR timestamp: NOW TODAY numpmid: 2
  0.55.685 (<noname>): Operation not permitted
  0.47.751 (<noname>): numval: 3 valfmt: 0 vlist[]:
    inst [2 or ???] value 2345 0 0x929
    inst [4 or ???] value 3456 0 0xd80
    inst [8 or ???] value 4567 0 0x11d7
[SERVER]pmXmitPDU: LOG_CONTROL fd=<n> len=68
000:       44     8000        0        b        1      3e8        2     dead 
008: ffffffff     beef        3        2      929        4      d80        8 
016:     11d7 
[SERVER]pmGetPDU: LOG_CONTROL fd=<n> len=68 from=0
000:       44     8000        0        b        1      3e8        2     dead 
008:        0     beef        3        2      929        4      d80        8 
016:     11d7 
+ PDU_LOG_CONTROL: control=11 state=1 rate=1000
pmResult dump from ADDR timestamp: NOW TODAY numpmid: 2
  0.55.685 (<noname>): No values returned!
  0.47.751 (<noname>): numval: 3 valfmt: 0 vlist[]:
    inst [2 or ???] value 2345 0 0x929
    inst [4 or ???] value 3456 0 0xd80
    inst [8 or ???] value 4567 0 0x11d7
pmResult dump from ADDR timestamp: NOW TODAY numpmid: 2
  0.55.685 (<noname>): No values returned!
  0.47.751 (<noname>): numval: 3 valfmt: 0 vlist[]:
    inst [2 or ???] value 2345 0 0x929
    inst [4 or ???] value 3456 0 0xd80
    inst [8 or ???] value 4567 0 0x11d7
[SERVER]pmXmitPDU: LOG_CONTROL fd=<n> len=68
000:       44     8000        0        b        1      3e8        2     dead 
008:        0     beef        3        2      929        4      d80        8 
016:     11d7 
[SERVER]pmGetPDU: LOG_CONTROL fd=<n> len=76 from=0
000:       4c     8000        0        b        1      3e8        2     dead 
008:        1 ffffffff      4d2     beef        3        2      929        4 
016:      d80        8     11d7 
+ PDU_LOG_CONTROL: control=11 state=1 rate=1000
pmResult dump from ADDR timestamp: NOW TODAY numpmid: 2
  0.55.685 (<noname>): numval: 1 valfmt: 0 vlist[]:
   value 1234 0 0x4d2
  0.47.751 (<noname>): numval: 3 valfmt: 0 vlist[]:
    inst [2 or ???] value 2345 0 0x929
    inst [4 or ???] value 3456 0 0xd80
    inst [8 or ???] value 4567 0 0x11d7
pmResult dump from ADDR timestamp: NOW TODAY numpmid: 2
  0.55.685 (<noname>): numval: 1 valfmt: 0 vlist[]:
   value 1234 0 0x4d2
  0.47.751 (<noname>): numval: 3 valfmt: 0 vlist[]:
    inst [2 or ???] value 2345 0 0x929
    inst [4 or ???] value 3456 0 0xd80
    inst [8 or ???] value 4567 0 0x11d7
[SERVER]pmXmitPDU: LOG_CONTROL fd=<n> len=76
000:       4c     8000        0        b        1      3e8        2     dead 
008:        1 ffffffff      4d2     beef        3        2      929        4 
016:      d80        8     11d7 
[SERVER]pmGetPDU: LOG_STATUS fd=<n> len=264 from=0
000:      108     8001        0 ?? pad ?     b6d0     3039     b6da     5ba0 
008:     b6e4     8707        1        1        0      800 666f6f00        0 
016:        0        0        0        0        0        0        0        0 
024:        0        0        0        0        0        0 666f6f2e 6261722e 
032: 636f6d00        0        0        0        0        0        0        0 
040:        0        0        0        0        0        0 545a2d54 48455245 
048:        0        0        0        0        0        0        0        0 
056: 545a2d48 45524500        0        0        0        0        0        0 
064:        0        0 
__pmDecodeLogStatus: got PDU (fromversion=2)
+ PDU_LOG_STATUS: start=46800.012345 13:00:00.012
last=46810.023456 13:00:10.023 now=46820.034567 13:00:20.034
state=1 vol=1 size=2048 host=foo tz="TZ-THERE" tzlogger="TZ-HERE"
__pmSendLogStatus: sending PDU (toversion=2)
[SERVER]pmXmitPDU: LOG_STATUS fd=<n> len=264
000:      108     8001        0 ?? pad ?     b6d0     3039     b6da     5ba0 
008:     b6e4     8707        1        1        0      800 666f6f00        0 
016:        0        0        0        0        0        0        0        0 
024:        0        0        0        0        0        0 666f6f2e 6261722e 
032: 636f6d00        0        0        0        0        0        0        0 
040:        0        0        0        0        0        0 545a2d54 48455245 
048:        0        0        0        0        0        0        0        0 
056: 545a2d48 45524500        0        0        0        0        0        0 
064:        0        0 
[SERVER]pmGetPDU: LOG_REQUEST fd=<n> len=16 from=0
000:       10     8002        0        3 
__pmDecodeLogRequest: got PDU (type=3, version=2)
+ PDU_LOG_REQUEST: request=sync
_pmSendRequest: sending PDU (type=3, version=2)
[SERVER]pmXmitPDU: LOG_REQUEST fd=<n> len=16
000:       10     8002        0        3 
[SERVER]pmGetPDU: TYPE-28752? fd=<n> len=16 from=CLIENT
000:       10     7050   CLIENT       41 
+ TRACE_PDU_ACK: ack=65
[SERVER]pmGetPDU: TYPE-28753? fd=<n> len=32 from=CLIENT
000:       20     7051   CLIENT  1060380 402f6a7a 2955385e 62312b62 32007e7e 
+ TRACE_PDU_DATA: tag="b1+b2" taglen=6 type=observe value=15.708
[SERVER]pmGetPDU: TYPE-28753? fd=<n> len=32 from=CLIENT
000:       20     7051   CLIENT  1050380 402921fb 54442d18 62312b62   7e7e7e 
+ TRACE_PDU_DATA: tag="b1+b" taglen=5 type=observe value=12.5664
[SERVER]pmGetPDU: TYPE-28753? fd=<n> len=28 from=CLIENT
000:       1c     7051   CLIENT  1040380 4022d97c 7f3321d2 62312b00 
+ TRACE_PDU_DATA: tag="b1+" taglen=4 type=observe value=9.42478
[SERVER]pmGetPDU: TYPE-28753? fd=<n> len=28 from=CLIENT
000:       1c     7051   CLIENT  1030380 401921fb 54442d18 6231007e 
+ TRACE_PDU_DATA: tag="b1" taglen=3 type=observe value=6.28319
[SERVER]pmGetPDU: TYPE-28753? fd=<n> len=28 from=CLIENT
000:       1c     7051   CLIENT  1020380 400921fb 54442d18 62007e7e 
+ TRACE_PDU_DATA: tag="b" taglen=2 type=observe value=3.14159
