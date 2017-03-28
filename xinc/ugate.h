/********************************************************************
	created:	2011/08/17
	created:	17:8:2011   10:44
	filename: 	C:\DD\PROJECTS\FIXIII\UGATE\xinc\ugate.h
	file path:	C:\DD\PROJECTS\FIXIII\UGATE\xinc
	file base:	ugate
	file ext:	h
	author:		CHENYH
	
	purpose:	��UDL�ȵ��õ� C ���ýӿں���
*********************************************************************/
#ifndef ugate_h__
#define ugate_h__
#include "fixbase.h"

#define MAXFIXMSGLEN 8000

enum FS_STATUS
{
   FS_EOD      = -10,
   FS_ERROR    = -2,
   FS_DISABLE  = -1,
   FS_CLOSE    = 0,
   FS_CONNECTING = 1,
   FS_OPEN     = 2
};


#ifdef __cplusplus
extern "C" {
#endif

   typedef struct _T_UGDATA
   {
      char sOrigClOrdID[61];  //       ORIGCLORDID          CHAR(20)               not null with default '',
      char sClOrdID[61];      //       CLORDID              CHAR(20)               not null with default '',
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
      char	sExecID[31];		//133.TAG17 ִ�б��
      char	sSenderCompID[21];		//6.TAG49 ���ͷ�ID
      char	sTargetCompID[21];		//7.TAG56 ���շ�ID
      
      long	lSvrTime;		//93.TAG10101:Serverʱ��
      
      char  sPossResend;   // TAG97: Indicates that message may contain information that has been sent under another sequence number. Y / N
      char  sSecondaryExecID[31];  // TAG527 ��¼SS������ExecID
      
      double dCashOrderQty;  // TAG 152: �ڶ����У���������������OrderQty, ������NewConfirmationȷ�ϵ��У�������д��SellSide���������OrderQty.
      // Added @ 2011-9-25 15:44:33
      char sOnBehalfOfSubID[21];  // TAG116 
      char sDeliverToSubID[21];   // TAG129
      
      // Added @ 2012/4/1 17:34:42 ��¼P_EXECNO: �����������Ľ����ո������˺�ExecID����ΪnnnD<lDays>-<OrderID>
      long lDays;
      
      // 2012/4/18 14:24:13 BBG ��������ֶΣ���ΪUUID
      char	sSenderSubID[21];		//TAG50 ���ͷ�SubID  ��ȡBBG's UUID
      char	sTargetSubID[21];		//TAG57 ���շ�SubID  ��¼BBG's UUID
      
      // 2012/4/25 14:32:55 Ϊ����TAG22-SecurityIDSource��TAG48-SecurityID
      char  sSecurityID[31];     // TAG48 SecurityID
      char  sIDSource[8];        // TAG22 IDSource
   } T_UGDATA; // ����һ��ר������KSUDLģʽ�µı������ݵ����ݼ���

   // ������: UG_NewOrderSingle2FIXMsg
   // ���  : ������ 2011-9-17 15:14:13
   // ����  : ��pUGDataת��ΪNewOrderSingle��FIX��Ϣ��
   // ����  : int :�������ɵĴ��ĳ���
   // ����  : T_UGDATA *pUGData[IN]: ��������
   // ����  : char *fixmsg [OUT]: ���ɵ�FIX��Ϣ���Ļ���
   // ����  : unsigned int fmsize[IN]: fixmsg�Ļ��泤��
   int UG_NewOrderSingle2FIXMsg(T_UGDATA *pUGData, const char *addfixmsg, char *fixmsg, int fmsize);


   // ������: UG_ExecutionFIXMsg
   // ���  : ������ 2011-9-17 15:02:55
   // ����  : ��pUGDataת��ΪExecution Report��FIX��Ϣ��
   // ����  : int :�������ɵĴ��ĳ���
   // ����  : T_UGDATA *pUGData[IN]: ��������
   // ����  : char *fixmsg [OUT]: ���ɵ�FIX��Ϣ���Ļ���
   // ����  : unsigned int fmsize[IN]: fixmsg�Ļ��泤��
   int UG_ExecutionFIXMsg(T_UGDATA *pUGData,char *fixmsg, unsigned int fmsize);


   // ������: UG_CancelRejectFIXMsg
   // ���  : ������ 2011-9-17 14:58:17
   // ����  : ��pUGDataת��ΪCancelReject��FIX��Ϣ��
   // ����  : int :�������ɵĴ��ĳ���
   // ����  : T_UGDATA *pUGData[IN]: ��������
   // ����  : char *fixmsg [OUT]: ���ɵ�FIX��Ϣ���Ļ���
   // ����  : unsigned int fmsize[IN]: fixmsg�Ļ��泤��
   int UG_CancelRejectFIXMsg(T_UGDATA *pUGData,char *fixmsg, unsigned int fmsize);   

   // ������: UG_UGDataReturn
   // ���  : ������ 2011-9-17 14:54:09
   // ����  : ����pUGData�е�sSenderCompID��sTargetCompID��sOnBehalfOfCompID��sDeliverToCompID
   // ����  : void 
   // ����  : T_UGDATA *pUGData [IN/OUT]
   void UG_UGDataReturn(T_UGDATA *pUGData);

   // ������: FIXDataGetUGData
   // ���  : ������ 2011-9-17 11:08:59
   // ����  : ��ȡh�е����ݵ�pUGData�У��Ա������ٴ���
   // ����  : int 
   // ����  : FIXDATAHANDLE h [IN]: �Ѿ����ú�FIX��Ϣ��FIXDataHandle
   // ����  : T_UGDATA *pUGData [OUT]: Ҫ����д�Ĺؼ��ֶ�ֵ
   // ����  : const char *addfixmsg [IN]: û���ܹ�����д��pUGData�еķǹؼ����FIX���Ӵ���NULL-���� 
   // ����  : unsigned int afmsize [IN]:  addfixmsg�Ļ����ֽ���
   int FIXDataGetUGData(FIXDATAHANDLE h, T_UGDATA *pUGData, char *addfixmsg, unsigned int afmsize);


   // ������: UG_FIXMsg2UGData
   // ���  : ������ 2011-8-25 16:41:02
   // ����  : ��ȡfixmsg�еĹؼ����ݵ�pUGData�У�������ȡ�ģ����ŵ�addfixmsg��
   // ����  : int <0: ʧ��,fixmsg���ǺϹ����Ϣ����ϵͳ�쳣��>0: �ɹ������ع��ж��ٸ��ֶ���
   // ����  : const char *fixmsg [IN]: ����ȡ��FIX��Ϣ��
   // ����  : int fmlen [IN]: fixmsg�Ĵ���
   // ����  : T_UGDATA *pUGData [OUT]: Ҫ����д�Ĺؼ��ֶ�ֵ
   // ����  : const char *addfixmsg [IN]: û���ܹ�����д��pUGData�еķǹؼ����FIX���Ӵ���NULL-���� 
   // ����  : unsigned int afmsize [IN]:  addfixmsg�Ļ����ֽ���
   int UG_FIXMsg2UGData(const char *fixmsg, int fmlen, T_UGDATA *pUGData, char *addfixmsg, unsigned int afmsize);



   // ������: UG_PickupTagValue
   // ���  : ������ 2011-8-22 17:07:51
   // ����  : ��fixmsg�п��ٻ��tag��ֵ����ֻ��ȡ��һ��
   // ������ʱ��ȡ��������tag����: MsgType; BeginString; SenderCompID; TargetCompID��
   // ����  : const char * : ����NULL��ʾû���ҵ�ָ����tag����tvsize����; ����ȡ����
   // ����  : const char *fixmsg [IN]: ����ȡ��FIX��ʽ����Ϣ��
   // ����  : int tag [IN]: Ҫ�ҵ�ָ��TAG
   // ����  : char *tvalue [OUT]: ��д��ȡ��tag��ֵ
   // ����  : unsigned int tvsize [IN]: tvalue�Ļ��泤�ȣ�������<=0��
   const char *UG_PickupTagValue(const char *fixmsg, int tag, char *tvalue, unsigned int tvsize);


   // UDL��������ͨ��״̬�����Ϣ���Ը���ƽ̨���
   // statusinfo��ʽΪ: <LocalID>|<PartnerID1>:<status>:<load>:<errmsg>|...|<PartnerIDx>:<status>:<load>:<errmsg>
   int UDLHaveChannelStatusInfo(const char *statusinfo);


   // ������: UDLHaveMessageIn
   // ���  : ������ 2011-8-19 23:42:29
   // ����  : UDL�ӶԷ��յ�FIX��Ϣ����Ҫͨ��UG�ύ��FSƽ̨
   // ����  : int <0: ʧ�ܣ����򣬳ɹ�
   // ����  : const char *sPartnerID [IN]: Ϊ����Ϣ�������Ǹ�Partner��Ҳ����ΪNULL
   // ����  : const char *fixmsg [IN]: UDL�ύ��UG���д����FIX��Ϣ����
   int UDLHaveMessageIn(const char *PartnerID,const char *fixmsg);

#ifdef _MSC_VER
   typedef void THREADENTRY(void *pArv);
#else
   typedef void *THREADENTRY(void *pArv);
#endif

   // ������: StartThread
   // ���  : ������ 2011-8-17 21:15:38
   // ����  : ��ThreadRun������Ϊ�̵߳���ڣ�����һ���߳�
   // ����  : int <0: ����ʧ�ܣ�����ɹ�
   // ����  : THREADENTRY ThreadRun [IN]: �߳���ں���
   // ����  : void *pArv [IN]: ������ʱ��Ĵ���Ĳ���
   int StartThread(THREADENTRY ThreadRun,void *pArv);

   // ������: UG_INIReadTString
   // ���  : ������ 2011-8-17 14:16:47
   // ����  : ��ȡ�����ļ��е�ָ�������� 
   // ����  : char * : 
   // ����  : const char *section [IN]: ���ö�
   // ����  : const char *entry [IN]: ������
   // ����  : const char *defvalue [IN]: ȱʡֵ
   // ����  : char *buffer [OUT]: ��Ŷ�ȡ������ֵ
   // ����  : int bufLen [IN]: buffer������ֽڳ���
   char *UG_INIReadTString(const char *section, const char *entry, const char *defvalue,char *buffer,int bufLen);

   // ������: UG_INIReadInt
   // ���  : ������ 2011-8-17 21:13:26
   // ����  : �����η�ʽ��ȡ�����ļ��е�ָ����������
   // ����  : int :���ض�ȡ������ֵ
   // ����  : const char *section [IN]: ���ö�
   // ����  : const char *entry [IN]: ������
   // ����  : int defvalue [IN]: ȱʡֵ
   int UG_INIReadInt(const char *section, const char *entry,int defvalue);

   // ������: UG_LoadIni
   // ���  : ������ 2011-8-17 14:33:40
   // ����  : �򿪲�װ��UGate���������ò���
   // ����  : int >0: �ɹ���������򽫻��˳�
   // ����  : const char *inifile [IN]: �����ļ�
   int UG_LoadIni(const char *inifile);

   // ������: UG_Init
   // ���  : ������ 2011-8-17 14:49:22
   // ����  : ��ʼ��UGate������ģ��
   // ����  : int <0: ʧ�ܣ�����ɹ�
   int UG_Init();

   // ������: UG_BCCLinkOK
   // ���  : ������ 2011-8-17 15:13:47
   // ����  : UGate��BCC�����Ƿ�������������������˵��Ҫ��ǿ���˳�
   // ����  : int >0: ��������
   int UG_BCCLinkOK();

   // ������: UG_ToExit
   // ���  : ������ 2011-8-18 21:23:43
   // ����  : ��UG_Init��ԣ�׼���˳�UGate
   // ����  : void 
   void UG_ToExit();

   // ������: UG_GetPartners
   // ���  : ������ 2011-8-29 23:58:55
   // ����  : ȡϵͳ��������ڱ�UG�ĸ���Partner
   // ����  : const char * : ������ЧPartnerID����: <PartnerID1>;<PartnerID2>;...;<PartnerIDn>
   const char *UG_GetPartners();


   // ������: UG_GetLocalID
   // ���  : ������ 2011-8-20 15:56:58
   // ����  : ȡ��UGate��LocalID
   // ����  : const char *
   const char *UG_GetLocalID();
   
   // ������: SQLDebugLog
   // ���  : ������ 2004-3-4 17:45:16
   // ����  : ��UDL�ȼ�¼��Ϣ������LOG��־��
   // ����  : void 
   // ����  : int errorcode [IN]: ��־�м�¼�Ĵ������
   // ����  : char *pFormat [IN]: ��־��¼�е���Ϣ��ʽ
   // ����  : ... [IN]: ��־��Ϣ�Ĳ����嵥
   void SQLDebugLog(int errorcode,char *pFormat,...);
#define UG_WriteLog SQLDebugLog

   // ������: UG_SendMessageIn
   // ���  : ������ 2011-8-20 17:32:43
   // ����  : ��FSƽ̨�����ͷ�ʽ�ύ��Ϣ (���̱߳���)
   // ����  : int <0: ʧ�ܣ�����ɹ�
   // ����  : int reqtype [IN]: ��Ϣ�Ĺ��ܺ�
   // ����  : int pmode [IN]: 0 - ���ɿ��ķ�ʽ�ύ(�п���û���ܹ�����ƽ̨)��1 - �ɿ��ύ(��һ����������һ�����ύ��ƽ̨��)
   // ����  : const char *inmsg [IN]: ��Ҫ�ύ����Ϣ�ַ���
   int UG_SendMessageIn(int reqtype, int pmode, const char *inmsg);


   // ������: UG_Processing
   // ���  : ������ 2011-8-20 23:36:25
   // ����  : UG���߳��в��ϴ�ƽ̨����ȡ��Ϣ
   // ����  : int 
   int UG_Processing();


   // ������: UG_FIXMsgKeyTagCmp
   // ���  : ������ 2011-8-26 17:35:24
   // ����  : �Ƚ�����FIX��Ϣ�е���ؼ���ȷ���Ƿ����Ϊ��ͬ����Ϣ
   // ����  : int =0: ��ʾ��ͬ��
   //       ����Ϊ��ͬ��-- 1:MsgType; 2: NewOrderSingle; 3:OrderCancel/OrderModification; 
   //                      4:Execution Report; 5:Order Cancel Reject; 6:New Order List
   // ����  : const char *fixmsg1 [IN]: ���Ƚϵ�FIX��Ϣ1
   // ����  : const char *fixmsg2 [IN]: ���Ƚϵ�FIX��Ϣ2
   int UG_FIXMsgKeyTagCmp(const char *fixmsg1, const char *fixmsg2);


   // ������: UG_RestoreFIXInMsg
   // ���  : ������ 2011-8-28 16:17:02
   // ����  : �Իָ��ķ�ʽ��FIX IN����Ϣ�ύ��FS
   // ����  : int <0: ʧ�ܣ����򣬳ɹ�
   // ����  : const char *partnerid [IN]: ����Ϣ�����PartnerID,��fixmsg����SendCompID�������ˣ�����ΪNULL
   // ����  : const char *fixmsg [IN]: IN FIX Message
   int UG_RestoreFIXInMsg(const char *partnerid, const char *fixmsg);

   
   // ������: UG_LoadMarkets
   // ���  : ������ 2011-9-15 23:13:06
   // ����  : װ�ؽ����г����ڲ�����ƥ���ļ�
   // ����  : int >0: �ɹ�װ��ƥ���������
   //             <=0: װ��ʧ��  -1:�ļ����쳣; 0:û��׼ȷ�����嵥;
   //             -2: �����ڴ�ʧ�ܣ�
   // ����  : const char *imarketfile
   int UG_LoadMarkets(const char *imarketfile);

   // ������: UG_GetIMarket
   // ���  : ������ 2011-9-15 23:18:45
   // ����  : ��������ĸ����룬�ҳ��ڲ��г����룻����֮ǰ�ɹ�����UG_LoadMarkets
   // ����  : const char *: NULL - û���ҵ�; ���򷵻ؽ����г��ڲ�����
   // ����  : const char *exchcode[IN]: KSFIXƽ̨�ṩ�Ľ��������룬�� "XSHE"
   // ����  : const char *account[IN]: �ɶ������Ͷ�����ʺţ�����Ϊ��(��һ��׼ȷ)
   // ����  : const char *symbol[IN]: ֤ȯ������Լ���룬����Ϊ��(��һ��׼ȷ)
   const char *UG_GetIMarket(const char *exchcode, const char *account, const char *symbol);

   // ������: UG_GetExchange
   // ���  : ������ 2011-9-15 23:23:38
   // ����  : ��������ĸ����룬�ҳ����������룻����֮ǰ�ɹ�����UG_LoadMarkets
   // ����  : const char *: NULL - û���ҵ�; ���򷵻�ƽ̨�Ľ���������
   // ����  : const char *imarket[IN]: ����ϵͳ�ڲ����г����룬�� "1"
   // ����  : const char *account[IN]: �ɶ������Ͷ�����ʺţ�����Ϊ��(��һ��׼ȷ)
   // ����  : const char *symbol[IN]: ֤ȯ������Լ���룬����Ϊ��(��һ��׼ȷ)
   const char *UG_GetExchange(const char *imarket, const char *account, const char *symbol);

   //////////////////////////////////////////////////////////////////////////
   // !! ��������������ר����OUTMODE!=0�������£���UDL���õģ��ڲ�����
   // ������: UG_GetOutMsg
   // ���  : ������ 2011-9-16 22:30:51
   // ����  : UDL��ȡ��Ҫ�����OUT��Ϣ
   // ����  : int >0: ��ȡ�ɹ���������msgbuf�е���Ϣ���ȣ�
   //             0: �ڵȴ�outwaitms*100 (ms)ʱ���ڣ�û����ҪOUT�������Ϣ��
   //             -2: �Ƿ���partnerid����UGATEû�ж����������
   // ����  : const char *partnerid [IN]: ���ַ���ID����OUT��Ϣ�е� TargetCompID
   // ����  : int outwaitms [IN]: �ȴ���Ϣ��ʱ����ƣ�ʵ�ʵȴ����ʱ��Ϊ outwaitms*100 (ms)
   // ����  : char *msgbuf [OUT]: ��ŵõ�����ҪOUT�������Ϣ�����泤�ȼ�Ϊϵͳʵ�ʴ�����������ΪMAXFIXMSGLEN
   int UG_GetOutMsg(const char *partnerid, int outwaitms, char *msgbuf);
   
   
   // ������: UG_HaveOutMsg
   // ���  : ������ 2011-9-16 22:30:54
   // ����  : ��UDL��ʱ��OUT��Ϣ�����浽UGATE��ܹ����µ�OUT��Ϣ������
   // ����  : int : 0/1 - ʵ�ʵ�plevel����ʵ�ʱ���ŵ�OUT��Ϣ�������ȼ���0��1��
   //             -2: �Ƿ���partnerid����UGATEû�ж����������
   // ����  : const char *parterid [IN]: ���ַ���ID����OUT��Ϣ�е� TargetCompID
   // ����  : const char *msg [IN]: Ҫ�����fixmsg����'\0'����
   // ����  : int plevel [IN]: ������������ȼ�: 0��1, 0��1��, ����UG_GetOutMsg��ʱ����ȡ0�����е���Ϣ��Ȼ��ȡ1�����е���Ϣ
   int UG_HaveOutMsg(const char *parterid, const char *msg, int plevel);
   //////////////////////////////////////////////////////////////////////////


   // ������: UG_SetOutMode
   // ���  : ������ 2011-9-16 23:11:49
   // ����  : ��UDL���ã������� OUT��Ϣ�Ĵ���ģʽ
   // ����  : void 
   // ����  : int outmode[IN]: 0 - UDL���ṩʵ�ʵ�UDLOnMessageOut�����������д���
   //                          1 - ��UGATE�����ά��OUT��Ϣ�Ķ��У�UDLͨ������UG_GetOutMsg����ȡOUT��Ϣ
   void UG_SetOutMode(int outmode);


   // ������: UG_GetOutMsgSize
   // ���  : ������ 2011-9-16 23:36:16
   // ����  : ��OUTMODE=1��ʱ��ȡUGATE�����µ�ָ��PartnerID��OutMsg������Ϣ����
   // ����  : int >=0: Ŀǰ�������Out�����е�Msg��Ϣ����
   //             -2: �Ƿ���partnerid����UGATEû�ж����������
   // ����  : const char *partnerid [IN]: ���ַ���ID����OUT��Ϣ�е� TargetCompID
   int UG_GetOutMsgSize(const char *partnerid);

   // Function name: UGGetChannelInfo
   // Author       : CHENYH 2012/5/18 23:39:30
   // Description  : ȡUG�ڲ��ĸ���Channel��״̬  -- UG��������
   // Return type  : int >=0: ��ȡ�ɹ���<0: ʧ�ܣ������iChannel��
   // Argument : int iChannel [IN]:��0��ʼ��Channel���
   // Argument : char *info256 [OUT]: ��"<PartnerID>:<״̬>:<����>" ��ʽ���ص���Ϣ
   int UGGetChannelInfo(int iChannel, char *info256);

   void UGReloadKFXFile(int iChannel);

#ifdef __cplusplus
}
#endif

#endif // ugate_h__
