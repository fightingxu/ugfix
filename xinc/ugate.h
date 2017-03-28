/********************************************************************
	created:	2011/08/17
	created:	17:8:2011   10:44
	filename: 	C:\DD\PROJECTS\FIXIII\UGATE\xinc\ugate.h
	file path:	C:\DD\PROJECTS\FIXIII\UGATE\xinc
	file base:	ugate
	file ext:	h
	author:		CHENYH
	
	purpose:	供UDL等调用的 C 调用接口函数
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
      char	sExecID[31];		//133.TAG17 执行编号
      char	sSenderCompID[21];		//6.TAG49 发送方ID
      char	sTargetCompID[21];		//7.TAG56 接收方ID
      
      long	lSvrTime;		//93.TAG10101:Server时间
      
      char  sPossResend;   // TAG97: Indicates that message may contain information that has been sent under another sequence number. Y / N
      char  sSecondaryExecID[31];  // TAG527 记录SS给出的ExecID
      
      double dCashOrderQty;  // TAG 152: 在订单中，可以用这个来替代OrderQty, 但是在NewConfirmation确认单中，必须填写被SellSide推算出来的OrderQty.
      // Added @ 2011-9-25 15:44:33
      char sOnBehalfOfSubID[21];  // TAG116 
      char sDeliverToSubID[21];   // TAG129
      
      // Added @ 2012/4/1 17:34:42 记录P_EXECNO: 即订单经过的交易日个数，此后，ExecID将改为nnnD<lDays>-<OrderID>
      long lDays;
      
      // 2012/4/18 14:24:13 BBG 利用这个字段，作为UUID
      char	sSenderSubID[21];		//TAG50 发送方SubID  提取BBG's UUID
      char	sTargetSubID[21];		//TAG57 接收方SubID  记录BBG's UUID
      
      // 2012/4/25 14:32:55 为兼容TAG22-SecurityIDSource；TAG48-SecurityID
      char  sSecurityID[31];     // TAG48 SecurityID
      char  sIDSource[8];        // TAG22 IDSource
   } T_UGDATA; // 这是一个专用于与KSUDL模式下的表交换数据的数据集合

   // 函数名: UG_NewOrderSingle2FIXMsg
   // 编程  : 陈永华 2011-9-17 15:14:13
   // 描述  : 将pUGData转换为NewOrderSingle的FIX消息串
   // 返回  : int :返回生成的串的长度
   // 参数  : T_UGDATA *pUGData[IN]: 基本数据
   // 参数  : char *fixmsg [OUT]: 生成的FIX消息串的缓存
   // 参数  : unsigned int fmsize[IN]: fixmsg的缓存长度
   int UG_NewOrderSingle2FIXMsg(T_UGDATA *pUGData, const char *addfixmsg, char *fixmsg, int fmsize);


   // 函数名: UG_ExecutionFIXMsg
   // 编程  : 陈永华 2011-9-17 15:02:55
   // 描述  : 将pUGData转换为Execution Report的FIX消息串
   // 返回  : int :返回生成的串的长度
   // 参数  : T_UGDATA *pUGData[IN]: 基本数据
   // 参数  : char *fixmsg [OUT]: 生成的FIX消息串的缓存
   // 参数  : unsigned int fmsize[IN]: fixmsg的缓存长度
   int UG_ExecutionFIXMsg(T_UGDATA *pUGData,char *fixmsg, unsigned int fmsize);


   // 函数名: UG_CancelRejectFIXMsg
   // 编程  : 陈永华 2011-9-17 14:58:17
   // 描述  : 将pUGData转换为CancelReject的FIX消息串
   // 返回  : int :返回生成的串的长度
   // 参数  : T_UGDATA *pUGData[IN]: 基本数据
   // 参数  : char *fixmsg [OUT]: 生成的FIX消息串的缓存
   // 参数  : unsigned int fmsize[IN]: fixmsg的缓存长度
   int UG_CancelRejectFIXMsg(T_UGDATA *pUGData,char *fixmsg, unsigned int fmsize);   

   // 函数名: UG_UGDataReturn
   // 编程  : 陈永华 2011-9-17 14:54:09
   // 描述  : 交换pUGData中的sSenderCompID、sTargetCompID和sOnBehalfOfCompID、sDeliverToCompID
   // 返回  : void 
   // 参数  : T_UGDATA *pUGData [IN/OUT]
   void UG_UGDataReturn(T_UGDATA *pUGData);

   // 函数名: FIXDataGetUGData
   // 编程  : 陈永华 2011-9-17 11:08:59
   // 描述  : 提取h中的数据到pUGData中，以便程序快速处理
   // 返回  : int 
   // 参数  : FIXDATAHANDLE h [IN]: 已经设置好FIX消息的FIXDataHandle
   // 参数  : T_UGDATA *pUGData [OUT]: 要被填写的关键字段值
   // 参数  : const char *addfixmsg [IN]: 没有能够被填写到pUGData中的非关键域的FIX附加串；NULL-不填 
   // 参数  : unsigned int afmsize [IN]:  addfixmsg的缓存字节数
   int FIXDataGetUGData(FIXDATAHANDLE h, T_UGDATA *pUGData, char *addfixmsg, unsigned int afmsize);


   // 函数名: UG_FIXMsg2UGData
   // 编程  : 陈永华 2011-8-25 16:41:02
   // 描述  : 提取fixmsg中的关键数据到pUGData中，不能提取的，则存放到addfixmsg中
   // 返回  : int <0: 失败,fixmsg不是合规的消息串或系统异常；>0: 成功，返回共有多少个字段域
   // 参数  : const char *fixmsg [IN]: 被提取的FIX消息串
   // 参数  : int fmlen [IN]: fixmsg的串长
   // 参数  : T_UGDATA *pUGData [OUT]: 要被填写的关键字段值
   // 参数  : const char *addfixmsg [IN]: 没有能够被填写到pUGData中的非关键域的FIX附加串；NULL-不填 
   // 参数  : unsigned int afmsize [IN]:  addfixmsg的缓存字节数
   int UG_FIXMsg2UGData(const char *fixmsg, int fmlen, T_UGDATA *pUGData, char *addfixmsg, unsigned int afmsize);



   // 函数名: UG_PickupTagValue
   // 编程  : 陈永华 2011-8-22 17:07:51
   // 描述  : 从fixmsg中快速获得tag的值，但只能取第一个
   // 用于临时获取个别特殊tag，如: MsgType; BeginString; SenderCompID; TargetCompID等
   // 返回  : const char * : 返回NULL表示没有找到指定的tag，或tvsize不足; 否则，取到了
   // 参数  : const char *fixmsg [IN]: 被提取的FIX格式的消息串
   // 参数  : int tag [IN]: 要找的指定TAG
   // 参数  : char *tvalue [OUT]: 填写获取的tag的值
   // 参数  : unsigned int tvsize [IN]: tvalue的缓存长度，不可以<=0的
   const char *UG_PickupTagValue(const char *fixmsg, int tag, char *tvalue, unsigned int tvsize);


   // UDL主动导出通道状态变更信息，以更新平台监控
   // statusinfo格式为: <LocalID>|<PartnerID1>:<status>:<load>:<errmsg>|...|<PartnerIDx>:<status>:<load>:<errmsg>
   int UDLHaveChannelStatusInfo(const char *statusinfo);


   // 函数名: UDLHaveMessageIn
   // 编程  : 陈永华 2011-8-19 23:42:29
   // 描述  : UDL从对方收到FIX消息，需要通过UG提交给FS平台
   // 返回  : int <0: 失败；否则，成功
   // 参数  : const char *sPartnerID [IN]: 为该消息来自于那个Partner，也可以为NULL
   // 参数  : const char *fixmsg [IN]: UDL提交给UG进行处理的FIX消息内容
   int UDLHaveMessageIn(const char *PartnerID,const char *fixmsg);

#ifdef _MSC_VER
   typedef void THREADENTRY(void *pArv);
#else
   typedef void *THREADENTRY(void *pArv);
#endif

   // 函数名: StartThread
   // 编程  : 陈永华 2011-8-17 21:15:38
   // 描述  : 用ThreadRun函数作为线程的入口，启动一个线程
   // 返回  : int <0: 启动失败；否则成功
   // 参数  : THREADENTRY ThreadRun [IN]: 线程入口函数
   // 参数  : void *pArv [IN]: 启动的时候的带入的参数
   int StartThread(THREADENTRY ThreadRun,void *pArv);

   // 函数名: UG_INIReadTString
   // 编程  : 陈永华 2011-8-17 14:16:47
   // 描述  : 读取配置文件中的指定配置项 
   // 返回  : char * : 
   // 参数  : const char *section [IN]: 配置段
   // 参数  : const char *entry [IN]: 配置项
   // 参数  : const char *defvalue [IN]: 缺省值
   // 参数  : char *buffer [OUT]: 存放读取的配置值
   // 参数  : int bufLen [IN]: buffer缓存的字节长度
   char *UG_INIReadTString(const char *section, const char *entry, const char *defvalue,char *buffer,int bufLen);

   // 函数名: UG_INIReadInt
   // 编程  : 陈永华 2011-8-17 21:13:26
   // 描述  : 以整形方式读取配置文件中的指定的配置项
   // 返回  : int :返回读取的整数值
   // 参数  : const char *section [IN]: 配置段
   // 参数  : const char *entry [IN]: 配置项
   // 参数  : int defvalue [IN]: 缺省值
   int UG_INIReadInt(const char *section, const char *entry,int defvalue);

   // 函数名: UG_LoadIni
   // 编程  : 陈永华 2011-8-17 14:33:40
   // 描述  : 打开并装载UGate的主体配置参数
   // 返回  : int >0: 成功，否则程序将会退出
   // 参数  : const char *inifile [IN]: 配置文件
   int UG_LoadIni(const char *inifile);

   // 函数名: UG_Init
   // 编程  : 陈永华 2011-8-17 14:49:22
   // 描述  : 初始化UGate的主体模块
   // 返回  : int <0: 失败；否则成功
   int UG_Init();

   // 函数名: UG_BCCLinkOK
   // 编程  : 陈永华 2011-8-17 15:13:47
   // 描述  : UGate与BCC连接是否正常，若不正常，则说明要求强制退出
   // 返回  : int >0: 连接正常
   int UG_BCCLinkOK();

   // 函数名: UG_ToExit
   // 编程  : 陈永华 2011-8-18 21:23:43
   // 描述  : 和UG_Init相对，准备退出UGate
   // 返回  : void 
   void UG_ToExit();

   // 函数名: UG_GetPartners
   // 编程  : 陈永华 2011-8-29 23:58:55
   // 描述  : 取系统定义的属于本UG的各个Partner
   // 返回  : const char * : 返回有效PartnerID序列: <PartnerID1>;<PartnerID2>;...;<PartnerIDn>
   const char *UG_GetPartners();


   // 函数名: UG_GetLocalID
   // 编程  : 陈永华 2011-8-20 15:56:58
   // 描述  : 取本UGate的LocalID
   // 返回  : const char *
   const char *UG_GetLocalID();
   
   // 函数名: SQLDebugLog
   // 编程  : 陈永华 2004-3-4 17:45:16
   // 描述  : 供UDL等记录信息到本地LOG日志中
   // 返回  : void 
   // 参数  : int errorcode [IN]: 日志中记录的错误代码
   // 参数  : char *pFormat [IN]: 日志记录中的信息格式
   // 参数  : ... [IN]: 日志信息的参数清单
   void SQLDebugLog(int errorcode,char *pFormat,...);
#define UG_WriteLog SQLDebugLog

   // 函数名: UG_SendMessageIn
   // 编程  : 陈永华 2011-8-20 17:32:43
   // 描述  : 向FS平台以推送方式提交消息 (多线程保护)
   // 返回  : int <0: 失败；否则成功
   // 参数  : int reqtype [IN]: 消息的功能号
   // 参数  : int pmode [IN]: 0 - 不可靠的方式提交(有可能没有能够交给平台)；1 - 可靠提交(若一切正常，则一定会提交给平台的)
   // 参数  : const char *inmsg [IN]: 需要提交的消息字符串
   int UG_SendMessageIn(int reqtype, int pmode, const char *inmsg);


   // 函数名: UG_Processing
   // 编程  : 陈永华 2011-8-20 23:36:25
   // 描述  : UG主线程中不断从平台处获取消息
   // 返回  : int 
   int UG_Processing();


   // 函数名: UG_FIXMsgKeyTagCmp
   // 编程  : 陈永华 2011-8-26 17:35:24
   // 描述  : 比较两个FIX消息中的最关键域，确认是否基本为相同的消息
   // 返回  : int =0: 表示相同；
   //       否则为不同的-- 1:MsgType; 2: NewOrderSingle; 3:OrderCancel/OrderModification; 
   //                      4:Execution Report; 5:Order Cancel Reject; 6:New Order List
   // 参数  : const char *fixmsg1 [IN]: 被比较的FIX消息1
   // 参数  : const char *fixmsg2 [IN]: 被比较的FIX消息2
   int UG_FIXMsgKeyTagCmp(const char *fixmsg1, const char *fixmsg2);


   // 函数名: UG_RestoreFIXInMsg
   // 编程  : 陈永华 2011-8-28 16:17:02
   // 描述  : 以恢复的方式将FIX IN的消息提交给FS
   // 返回  : int <0: 失败；否则，成功
   // 参数  : const char *partnerid [IN]: 该消息发起的PartnerID,若fixmsg中在SendCompID中设置了，可以为NULL
   // 参数  : const char *fixmsg [IN]: IN FIX Message
   int UG_RestoreFIXInMsg(const char *partnerid, const char *fixmsg);

   
   // 函数名: UG_LoadMarkets
   // 编程  : 陈永华 2011-9-15 23:13:06
   // 描述  : 装载交易市场的内部代码匹配文件
   // 返回  : int >0: 成功装载匹配项个数；
   //             <=0: 装载失败  -1:文件打开异常; 0:没有准确定义清单;
   //             -2: 申请内存失败；
   // 参数  : const char *imarketfile
   int UG_LoadMarkets(const char *imarketfile);

   // 函数名: UG_GetIMarket
   // 编程  : 陈永华 2011-9-15 23:18:45
   // 描述  : 根据输入的各代码，找出内部市场代码；必须之前成功调用UG_LoadMarkets
   // 返回  : const char *: NULL - 没有找到; 否则返回交易市场内部代码
   // 参数  : const char *exchcode[IN]: KSFIX平台提供的交易所代码，如 "XSHE"
   // 参数  : const char *account[IN]: 股东代码或投资者帐号，可以为空(则不一定准确)
   // 参数  : const char *symbol[IN]: 证券代码或合约代码，可以为空(则不一定准确)
   const char *UG_GetIMarket(const char *exchcode, const char *account, const char *symbol);

   // 函数名: UG_GetExchange
   // 编程  : 陈永华 2011-9-15 23:23:38
   // 描述  : 根据输入的各代码，找出交易所代码；必须之前成功调用UG_LoadMarkets
   // 返回  : const char *: NULL - 没有找到; 否则返回平台的交易所代码
   // 参数  : const char *imarket[IN]: 交易系统内部的市场代码，如 "1"
   // 参数  : const char *account[IN]: 股东代码或投资者帐号，可以为空(则不一定准确)
   // 参数  : const char *symbol[IN]: 证券代码或合约代码，可以为空(则不一定准确)
   const char *UG_GetExchange(const char *imarket, const char *account, const char *symbol);

   //////////////////////////////////////////////////////////////////////////
   // !! 如下两个函数，专门在OUTMODE!=0的配置下，被UDL调用的，内部不用
   // 函数名: UG_GetOutMsg
   // 编程  : 陈永华 2011-9-16 22:30:51
   // 描述  : UDL获取需要处理的OUT消息
   // 返回  : int >0: 获取成功，并返回msgbuf中的消息长度；
   //             0: 在等待outwaitms*100 (ms)时间内，没有需要OUT处理的消息；
   //             -2: 非法的partnerid，本UGATE没有定义这个对手
   // 参数  : const char *partnerid [IN]: 对手方的ID，即OUT消息中的 TargetCompID
   // 参数  : int outwaitms [IN]: 等待消息的时间控制，实际等待的最长时间为 outwaitms*100 (ms)
   // 参数  : char *msgbuf [OUT]: 存放得到的需要OUT处理的消息，缓存长度即为系统实际处理的最长，建议为MAXFIXMSGLEN
   int UG_GetOutMsg(const char *partnerid, int outwaitms, char *msgbuf);
   
   
   // 函数名: UG_HaveOutMsg
   // 编程  : 陈永华 2011-9-16 22:30:54
   // 描述  : 供UDL暂时将OUT消息，缓存到UGATE框架管理下的OUT消息队列中
   // 返回  : int : 0/1 - 实际的plevel，即实际被存放的OUT消息队列优先级，0比1高
   //             -2: 非法的partnerid，本UGATE没有定义这个对手
   // 参数  : const char *parterid [IN]: 对手方的ID，即OUT消息中的 TargetCompID
   // 参数  : const char *msg [IN]: 要缓存的fixmsg，以'\0'结束
   // 参数  : int plevel [IN]: 即缓存队列优先级: 0或1, 0比1高, 即在UG_GetOutMsg的时候，先取0队列中的消息，然后取1队列中的消息
   int UG_HaveOutMsg(const char *parterid, const char *msg, int plevel);
   //////////////////////////////////////////////////////////////////////////


   // 函数名: UG_SetOutMode
   // 编程  : 陈永华 2011-9-16 23:11:49
   // 描述  : 供UDL调用，以设置 OUT消息的处理模式
   // 返回  : void 
   // 参数  : int outmode[IN]: 0 - UDL将提供实际的UDLOnMessageOut函数，并进行处理；
   //                          1 - 让UGATE框架来维护OUT消息的队列，UDL通过调用UG_GetOutMsg来获取OUT消息
   void UG_SetOutMode(int outmode);


   // 函数名: UG_GetOutMsgSize
   // 编程  : 陈永华 2011-9-16 23:36:16
   // 描述  : 当OUTMODE=1的时候，取UGATE管理下的指定PartnerID的OutMsg缓存消息个数
   // 返回  : int >=0: 目前被管理的Out队列中的Msg消息个数
   //             -2: 非法的partnerid，本UGATE没有定义这个对手
   // 参数  : const char *partnerid [IN]: 对手方的ID，即OUT消息中的 TargetCompID
   int UG_GetOutMsgSize(const char *partnerid);

   // Function name: UGGetChannelInfo
   // Author       : CHENYH 2012/5/18 23:39:30
   // Description  : 取UG内部的各个Channel的状态  -- UG主程序用
   // Return type  : int >=0: 获取成功；<0: 失败，错误的iChannel号
   // Argument : int iChannel [IN]:从0开始的Channel编号
   // Argument : char *info256 [OUT]: 以"<PartnerID>:<状态>:<负载>" 格式返回的信息
   int UGGetChannelInfo(int iChannel, char *info256);

   void UGReloadKFXFile(int iChannel);

#ifdef __cplusplus
}
#endif

#endif // ugate_h__
