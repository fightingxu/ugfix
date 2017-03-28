#ifndef _UGCTS2DI_HXX
#define _UGCTS2DI_HXX
extern struct _DB_UGDATA  // !!!!���ṹ�����T_UGDATA��ͬ!!!
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
   char sOrderID[21];      //       ORDERID              CHAR(10) �����ڲ����ò�����10�ַ���������ϵͳ�õ���OrderID��ſ�20���ڳ�����ʱ����
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
   char sBeginString[13];		/*118.TAG8 ��Ϣͷ��Э��汾��*/
   char sPassword[21];     // TAG 554 Password 
   
   // ����������Ϣ���ɵ�ʱ���õ��ֶ�:
   char	vsmess[256];		/*176.TAG58 TEXT*/
   long  lCxlRejReason;		/*27.TAG102 �����ܾ�ԭ��*/
   long  lOrdRejReason;		/*28.TAG103�����ܾ�ԭ��*/
   double	dCommission;		/*35.TAG12 ������*/
   char	sCxlRejResponseTo[4];		/*73.TAG434 �����ܾ���Ӧ(1or2)*/
   
   double	dLastPx;		//33.TAG31 ���γɽ��۸�
   double	dLastQty;		//38.TAG32 ���γɽ�����
   char	sExecTransType[3];		//70.TAG20 �������ͱ�ʶ��
   char	sExecID[21];		//133.TAG17 ִ�б��
   char	sSenderCompID[21];		//6.TAG49 ���ͷ�ID
   char	sTargetCompID[21];		//7.TAG56 ���շ�ID
   
   long	lSvrTime;		//93.TAG10101:Serverʱ��
   
   char  sPossResend;   // TAG97: Indicates that message may contain information that has been sent under another sequence number. Y / N
   char  sSecondaryExecID[21];  // TAG527 ��¼SS������ExecID
   
   double dCashOrderQty;  // TAG 152: �ڶ����У���������������OrderQty, ������NewConfirmationȷ�ϵ��У�������д��SellSide���������OrderQty.      
   // Added @ 2011-9-25 15:44:33 ����B���е�OnBehalfOfCompID��Ҫ
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
   char sBS[3];   // 0x - �����ɽ���¼��1x - �����ɹ���¼
   double dDONE_PRICE;
   char sOCCUR_TIME[9];
} tRealDone;

#endif

