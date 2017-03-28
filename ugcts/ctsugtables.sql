drop table FIX_BSORDERS;

drop index KS.I_FIX_ENT;

--==============================================================
-- Index: I_ENT_FIX : Ϊ���ܹ����UGCTS�����ٶ�
--==============================================================
create  index KS.I_FIX_ENT on KS.ENTRUST (
CONTRACT_NO          ASC,
ENTRUST_METHOD        ASC
);


drop index KS.I_FIX_DONEID;

create index KS.I_FIX_DONEID on KS.REAL_DONE (
ENTRUST_METHOD    ASC,
DONE_ID			ASC,
RDONE_DATETIME 	ASC
);

--==============================================================
-- Table: FIX_BSORDERS
--==============================================================
create table FIX_BSORDERS
(
   CLORDID              CHAR(20)               not null with default '',
   ORIGCLORDID          CHAR(20)               not null with default '',
   BEGINSTRING          CHAR(10)               not null with default '',
   BSUGID               CHAR(10)               not null with default '',
   SELLSIDE             CHAR(10)               not null with default '',
   SSCLORDID            CHAR(20)               not null with default '',
   ONBEHALFCOMPID       CHAR(20)               not null with default '',
   DELIVERCOMPID        CHAR(20)               not null with default '',
   PCXLCLORDID          VARCHAR(20)            not null with default '',
   MSGSEQNUM            INT                    not null with default 0,
   MSGTYPE              CHAR(4)                not null with default '',
   LISTID               CHAR(20)               not null with default '',
   LISTSEQNO            INT                    not null with default 0,
   ORDERID              CHAR(10)               not null with default '',
   ORDTYPE              CHAR(1)                not null with default '',
   NONTRADINGORDTYPE    CHAR(3)                not null with default '',
   TIMEINFORCE          CHAR(1)                not null with default '',
   SIDE                 CHAR(1)                not null with default '',
   OPENCLOSE            CHAR(1)                not null with default '',
   HANDLINST            CHAR(1)                not null with default '',
   TRANSACTTIME         CHAR(30)               not null with default '',
   SYMBOL               CHAR(30)               not null with default '',
   ORDERQTY             DECIMAL(18,4)          not null with default 0,
   CASHORDERQTY         DECIMAL(18,4)          with default 0,
   CURRENCY             CHAR(6)                not null with default '',
   PRICE                DECIMAL(12,4)          not null with default 0,
   ACCOUNT              CHAR(15)               not null with default '',
   CLIENTID             CHAR(30)               not null with default '',
   SECURITYEXCHANGE     CHAR(6)                not null with default '',
   SSEXCHANGE           CHAR(6)                not null default '',
   ORDSTATUS            CHAR(1)                not null with default '',
   EXECTYPE             CHAR(1)                not null with default '',
   CANCELEDQTY          DECIMAL(18,4)          not null with default 0,
   LOCALDATE            CHAR(10)               not null with default '',
   LOCALTIME            CHAR(8)                not null with default '',
   AVGPX                DECIMAL(12,6)          not null with default 0,
   CUMQTY               DECIMAL(18,4)          not null with default 0,
   LEAVESQTY            DECIMAL(18,4)          not null with default 0,
   EXECNOCNT            INT                    not null with default 0,
   EXPIREDATE           CHAR(10)               not null with default '',
   EXPIRETIME           CHAR(30)               not null with default '',
   constraint "P_Key_1" primary key (CLORDID)
)
in TX_DATA_TBS  index in TX_INDEX_TBS;

comment on table FIX_BSORDERS is
'������KSCTS���ݿ��У�UGCTSר�õģ������Լ����������õĶ�������';

comment on column FIX_BSORDERS.CLORDID is
'���󷽶������';

comment on column FIX_BSORDERS.ORIGCLORDID is
'����ԭʼ�������-BuySide������ԭʼ������';

comment on column FIX_BSORDERS.BEGINSTRING is
'BuySide����������Ϣ��TAG8��ֵ��Ϊ�˼�����Ϣ�����úͰ汾��ͬ?Ĵ��?;

comment on column FIX_BSORDERS.SELLSIDE is
'��ӦENTRUST���еı���ϯλKS.ENTRUST.REPORT_SEAT';

comment on column FIX_BSORDERS.SSCLORDID is
'�����̵ĺ�ͬ��KS.ENTRUST.RPT_CONTRACT';

comment on column FIX_BSORDERS.ONBEHALFCOMPID is
'���BuySide�Ķ�����Ϣ�е�OnBehalfCompID(�Ը�BS��ִ�з���)';

comment on column FIX_BSORDERS.DELIVERCOMPID is
'���BuySide�Ķ�����Ϣ�е�DeliverCompID';

comment on column FIX_BSORDERS.PCXLCLORDID is
'��¼��ǰ������������ĵ���ClOrdID���յ�ʱ���ʾ��û�б�������ĵ�';

comment on column FIX_BSORDERS.MSGSEQNUM is
'�յ�BuySide���¶�����ʱ�����Ϣ���';

comment on column FIX_BSORDERS.MSGTYPE is
'Message Type';

comment on column FIX_BSORDERS.LISTID is
'��Ϊ���Ӷ���(MsgType=E)��ʱ����ΪTAG66��ֵ��NewOrderSingle��Ϊ��';

comment on column FIX_BSORDERS.LISTSEQNO is
'TAG67:	Order number within the list';

comment on column FIX_BSORDERS.ORDERID is
'Unique identifier for Order as assigned by sell-side (broker, exchange, ECN). Uniqueness must be guaranteed within a single trading day. ';

comment on column FIX_BSORDERS.TIMEINFORCE is
'TAG59, Specifies how long the order remains in effect. Absence of this field is interpreted as DAY.';

comment on column FIX_BSORDERS.CANCELEDQTY is
'�ѳ����ɹ��򣨳ɹ��ĵ�����������';

comment on column FIX_BSORDERS.LOCALDATE is
'���һ���޸ĵı�������';

comment on column FIX_BSORDERS.LOCALTIME is
'���һ���޸ĵı���ʱ��';

comment on column FIX_BSORDERS.EXECNOCNT is
'����������BuySideִ�б����е�ExecID����ţ�0 - PendingNew; 1 - NewConfirmation; 2...999998 Ϊ����ִ�����; 999999Ϊ�����ɹ���ĵ��ɹ���ִ�����';

comment on column FIX_BSORDERS.EXPIREDATE is
'��������Ч����-�Ա���ʱ��ǣ�Ŀǰ�������EXPIRETIME';

comment on column FIX_BSORDERS.EXPIRETIME is
'������ָ������ʱ���ʱ�򣬱�ʾ����ʱ��㣬��UTC��ʾ';

/*
drop table FIX_EXEC;

--==============================================================
-- Table: FIX_EXEC
--==============================================================
create table FIX_EXEC
(
   DONE_ID              integer        not null,
   CONTRACT_NO          CHAR(10)               not null with default '',
   CUST_NO              CHAR(10)               not null with default '',
   MARKET_CODE          CHAR(1)                not null with default '',
   HOLDER_ACC_NO        CHAR(15)               not null with default '',
   SEC_ACC              CHAR(15)               not null with default '',
   DONE_NO              NUMERIC(12)            not null with default 0,
   SEC_TYPE             CHAR(2)                not null with default '',
   SEC_CODE             CHAR(8)                not null with default '',
   DONE_AMT             DECIMAL(19,4)          not null with default 0,
   DONE_VOL             INT                    not null with default 0,
   DONE_TIME            CHAR(8)                not null with default '',
   DONE_DATE            CHAR(8)                not null with default '',
   RPT_CONTRACT_NO      CHAR(10)               not null with default '',
   BS                   CHAR(2)                not null with default '',
   DONE_PRICE           DECIMAL(9,3)           not null with default 0,
   NET_AMT              DECIMAL(19,4)          not null with default 0,
   OCCUR_TIME           CHAR(8)                not null default '',
   REFF                 CHAR(10)               not null with default '',
   
   constraint "P_Key_1" primary key (DONE_ID)
)
in TX_DATA_TBS
index in TX_INDEX_TBS;

comment on table FIX_EXEC is
'FIXUGר�õ�ʵʱ�ɽ���';

comment on column FIX_EXEC.DONE_ID is
'�ɽ�ID���';

comment on column FIX_EXEC.CONTRACT_NO is
'��ͬ���-��ClOrdID';

comment on column FIX_EXEC.CUST_NO is
'�ͻ���';

comment on column FIX_EXEC.MARKET_CODE is
'�г�����';

comment on column FIX_EXEC.HOLDER_ACC_NO is
'�ɶ�����';

comment on column FIX_EXEC.SEC_ACC is
'���̴���';

comment on column FIX_EXEC.DONE_NO is
'�ɽ����';

comment on column FIX_EXEC.SEC_TYPE is
'֤ȯ���';

comment on column FIX_EXEC.SEC_CODE is
'֤ȯ����';

comment on column FIX_EXEC.ENTRUST_METHOD is
'ί�з�ʽ';

comment on column FIX_EXEC.DONE_AMT is
'�ɽ����';

comment on column FIX_EXEC.DONE_VOL is
'�ɽ�����';

comment on column FIX_EXEC.DONE_TIME is
'�ɽ�ʱ��';

comment on column FIX_EXEC.DONE_DATE is
'�ɽ�����';

comment on column FIX_EXEC.RPT_CONTRACT_NO is
'���̺�ͬ��';

comment on column FIX_EXEC.BS is
'ҵ�����';

comment on column FIX_EXEC.DONE_PRICE is
'�ɽ��۸�';

comment on column FIX_EXEC.NET_AMT is
'�ɽ�����';

comment on column FIX_EXEC.CURRENCY_TYPE is
'��������';

comment on column FIX_EXEC.OCCUR_TIME is
'����ʱ��';
*/