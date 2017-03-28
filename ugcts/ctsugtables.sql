drop table FIX_BSORDERS;

drop index KS.I_FIX_ENT;

--==============================================================
-- Index: I_ENT_FIX : 为了能够提高UGCTS运行速度
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
'建立在KSCTS数据库中，UGCTS专用的，保存以及后续处理用的订单数据';

comment on column FIX_BSORDERS.CLORDID is
'请求方订单编号';

comment on column FIX_BSORDERS.ORIGCLORDID is
'请求方原始订单编号-BuySide产生的原始订单号';

comment on column FIX_BSORDERS.BEGINSTRING is
'BuySide发过来的消息的TAG8的值，为了加速消息整理用和版本不同?拇?;

comment on column FIX_BSORDERS.SELLSIDE is
'对应ENTRUST表中的报盘席位KS.ENTRUST.REPORT_SEAT';

comment on column FIX_BSORDERS.SSCLORDID is
'即报盘的合同号KS.ENTRUST.RPT_CONTRACT';

comment on column FIX_BSORDERS.ONBEHALFCOMPID is
'存放BuySide的订单消息中的OnBehalfCompID(以给BS的执行方向)';

comment on column FIX_BSORDERS.DELIVERCOMPID is
'存放BuySide的订单消息中的DeliverCompID';

comment on column FIX_BSORDERS.PCXLCLORDID is
'记录当前订单被撤单或改单的ClOrdID，空的时候表示还没有被撤单或改单';

comment on column FIX_BSORDERS.MSGSEQNUM is
'收到BuySide的新订单的时候的消息序号';

comment on column FIX_BSORDERS.MSGTYPE is
'Message Type';

comment on column FIX_BSORDERS.LISTID is
'当为篮子订单(MsgType=E)的时候，则为TAG66的值，NewOrderSingle则为空';

comment on column FIX_BSORDERS.LISTSEQNO is
'TAG67:	Order number within the list';

comment on column FIX_BSORDERS.ORDERID is
'Unique identifier for Order as assigned by sell-side (broker, exchange, ECN). Uniqueness must be guaranteed within a single trading day. ';

comment on column FIX_BSORDERS.TIMEINFORCE is
'TAG59, Specifies how long the order remains in effect. Absence of this field is interpreted as DAY.';

comment on column FIX_BSORDERS.CANCELEDQTY is
'已撤单成功或（成功改单）的数据量';

comment on column FIX_BSORDERS.LOCALDATE is
'最后一次修改的本地日期';

comment on column FIX_BSORDERS.LOCALTIME is
'最后一次修改的本地时间';

comment on column FIX_BSORDERS.EXECNOCNT is
'用来产生给BuySide执行报告中的ExecID的序号：0 - PendingNew; 1 - NewConfirmation; 2...999998 为常规执行序号; 999999为撤单成功或改单成功的执行序号';

comment on column FIX_BSORDERS.EXPIREDATE is
'本订单有效日期-以本地时间记，目前建议采用EXPIRETIME';

comment on column FIX_BSORDERS.EXPIRETIME is
'即在有指定过期时间的时候，表示到期时间点，用UTC表示';

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
'FIXUG专用的实时成交表';

comment on column FIX_EXEC.DONE_ID is
'成交ID序号';

comment on column FIX_EXEC.CONTRACT_NO is
'合同序号-即ClOrdID';

comment on column FIX_EXEC.CUST_NO is
'客户号';

comment on column FIX_EXEC.MARKET_CODE is
'市场代码';

comment on column FIX_EXEC.HOLDER_ACC_NO is
'股东代码';

comment on column FIX_EXEC.SEC_ACC is
'报盘代码';

comment on column FIX_EXEC.DONE_NO is
'成交编号';

comment on column FIX_EXEC.SEC_TYPE is
'证券类别';

comment on column FIX_EXEC.SEC_CODE is
'证券代码';

comment on column FIX_EXEC.ENTRUST_METHOD is
'委托方式';

comment on column FIX_EXEC.DONE_AMT is
'成交金额';

comment on column FIX_EXEC.DONE_VOL is
'成交数量';

comment on column FIX_EXEC.DONE_TIME is
'成交时间';

comment on column FIX_EXEC.DONE_DATE is
'成交日期';

comment on column FIX_EXEC.RPT_CONTRACT_NO is
'报盘合同号';

comment on column FIX_EXEC.BS is
'业务类别';

comment on column FIX_EXEC.DONE_PRICE is
'成交价格';

comment on column FIX_EXEC.NET_AMT is
'成交净额';

comment on column FIX_EXEC.CURRENCY_TYPE is
'货币类型';

comment on column FIX_EXEC.OCCUR_TIME is
'发生时间';
*/