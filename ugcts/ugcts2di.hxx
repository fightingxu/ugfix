#ifndef _UGCTS2DI_HXX
#define _UGCTS2DI_HXX
extern struct _DB_UGDATA  // !!!!本结构必须和T_UGDATA相同!!!
{
   char sOrigClOrdID[21];  //       ORIGCLORDID          CHAR(20)               not null with default '',
   char sClOrdID[21];      //       CLORDID              CHAR(20)               not null with default '',
   char sSellSide[11];     //       SELLSIDE             CHAR(10)               not null with default '',
   char sOnBehalfOfCompID[21];  //       ONBEHALFCOMPID       CHAR(20)               not null with default '',
   char sDeliverToCompID[21];   //       DELIVERCOMPID        CHAR(20)               not null with default '',
   long lMsgSeqNum;        //       MSGSEQNUM            INT                    not null with default 0,
   char sMsgType[6];       //       MSGTYPE              CHAR(4)                not null with default '',
   char sListID[21];       //       LISTID               CHAR(20)               not null with default '',
   long lListSeqNo;        //       LISTSEQNO            INT                    not null with default 0,
   char sOrderID[21];      //       ORDERID              CHAR(10) 尽管内部采用不超过10字符，但从外系统得到的OrderID则放宽到20，在撤单的时候用
   char sOrdType[4];       //       ORDTYPE              CHAR(1)                not null with default '',
   char sNonTradingOrdType[4];   //       NONTRADINGORDTYPE    CHAR(3)                not null with default '',
   char sTimeInForce[4];   //       
   char sSide[4];          //       SIDE                 CHAR(1)                not null with default '',
   char sOpenClose[4];     //       OPENCLOSE            CHAR(1)                not null with default '',
   char sHandlInst[4];     //       HANDLINST            CHAR(1)                not null with default '',
   char sExecInst[51];     // TAG 18 Instructions for order handling on exchange trading floor. If more than one instruction is applicable to an order, this field can contain multiple instructions separated by space.
   char sTransactTime[31];   //       TRANSACTTIME         CHAR(30)               not null with default '',
   char sSymbol[31];       //       SYMBOL               CHAR(30)               not null with default '',
   double dOrderQty;       //       ORDERQTY             DECIMAL(18,4)          not null with default 0,
   char sCurrency[8];      //       CURRENCY             CHAR(6)                not null with default '',
   double dPrice;          //       PRICE                DECIMAL(9,3)           not null with default 0,
   char sAccount[16];      //       ACCOUNT              CHAR(15)               not null with default '',
   char sClientID[31];     //       CLIENTID             CHAR(30)               not null with default '',
   char sSecurityExchange[8];   //       SECURITYEXCHANGE     CHAR(6)                not null with default '',
   char sOrdStatus[4];     //       ORDSTATUS            CHAR(1)                not null with default '',
   char sExecType[4];      //       EXECTYPE             CHAR(1)                not null with default '',
   double dCanceledQty;    //       CANCELEDQTY          DECIMAL(18,4)          not null with default 0,
   char sLocalDate[11];    //       LOCALDATE            CHAR(10)               not null with default '',
   char sLocalTime[9];     //       LOCALTIME            CHAR(8)                not null with default '',
   double dAvgPx;          //       AVGPX                DECIMAL(12,6)          not null with default 0,
   double dCumQty;         //       CUMQTY               DECIMAL(18,4)          not null with default 0,
   double dLeavesQty;      //       LEAVESQTY            DECIMAL(18,4)          not null with default 0,
   long lExecNoCnt;        //       EXECNOCNT            INT                    not null with default 0,
   char sExpireDate[11];   //       EXPIREDATE           CHAR(10)               not null with default '',
   char sExpireTime[31];    //       EXPIRETIME           CHAR(8)                not null with default '',
   char sBeginString[13];		/*118.TAG8 消息头和协议版本号*/
   char sPassword[21];     // TAG 554 Password 
   
   // 其他用于消息生成的时候用的字段:
   char	vsmess[256];		/*176.TAG58 TEXT*/
   long  lCxlRejReason;		/*27.TAG102 撤单拒绝原因*/
   long  lOrdRejReason;		/*28.TAG103订单拒绝原因*/
   double	dCommission;		/*35.TAG12 手续费*/
   char	sCxlRejResponseTo[4];		/*73.TAG434 撤单拒绝相应(1or2)*/
   
   double	dLastPx;		//33.TAG31 本次成交价格
   double	dLastQty;		//38.TAG32 本次成交数量
   char	sExecTransType[3];		//70.TAG20 交易类型标识符
   char	sExecID[21];		//133.TAG17 执行编号
   char	sSenderCompID[21];		//6.TAG49 发送方ID
   char	sTargetCompID[21];		//7.TAG56 接收方ID
   
   long	lSvrTime;		//93.TAG10101:Server时间
   
   char  sPossResend;   // TAG97: Indicates that message may contain information that has been sent under another sequence number. Y / N
   char  sSecondaryExecID[21];  // TAG527 记录SS给出的ExecID
   
   double dCashOrderQty;  // TAG 152: 在订单中，可以用这个来替代OrderQty, 但是在NewConfirmation确认单中，必须填写被SellSide推算出来的OrderQty.      
   // Added @ 2011-9-25 15:44:33 申万B股中的OnBehalfOfCompID需要
   char sOnBehalfOfSubID[21];  // TAG116 
   char sDeliverToSubID[21];   // TAG129
} DB_UGData;

extern struct _T_REAL_DONE
{
   long lDONE_ID;
   char sCONTRACT_NO[11];
   char cMARKET_CODE;
   double dDONE_NO;
   char sSEC_TYPE[3];
   char sSEC_CODE[9];
   long lDONE_VOL;
   char sDONE_TIME[9];
   char sRPT_CONTRACT_NO[11];
   char sBS[3];   // 0x - 正常成交记录；1x - 撤单成功记录
   double dDONE_PRICE;
   char sOCCUR_TIME[9];
} tRealDone;

#endif

