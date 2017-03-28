/********************************************************************
	created:	2005/06/27
	created:	27:6:2005   19:25
	filename: 	D:\proj\ksbass\ksbu\bupub.cpp
	file path:	D:\proj\ksbass\ksbu
	file base:	bupub
	file ext:	cpp
	author:		CHENYH
	
	purpose:	 这里列出了可以供业务模块（C/C++都可以）调用的用于与BCC交换
   的控制函数（如SetCol、PutRow等函数）
*********************************************************************/

#include "stdafx.h"
#include "mypub.h"
#include "cxpack.h"
#include "svrlink.h"
#include "logfile.h"
#include "bdefine.h"

struct T_TICKLOG
{
   TICKUS tickus;
   char file[256];
   int  line;
};

class CBUTL
{
public:
   FILE *fp;
   int m_maxtls;
   int m_itl;
   T_TICKLOG *pLog;
public:
	int Dump();
	int Push(const char *file, int lineno,const char *desc);
	int Begin();
	int Set(int tlnum=0);
   CBUTL() { fp=NULL; m_maxtls=0; m_itl=0; pLog=NULL; }
   virtual ~CBUTL() { Close(); }
private:
	void Close();
};

CSvrLink g_SvrLink;  // 与业务调度中心的连接
extern CLogFile *g_pLogFile;

CBUTL g_BUTL;


// 设置BUTL的最大记录数，<=0: 关闭；>0: 启动记录
int BUTLSet(int tlnum)
{
   return(g_BUTL.Set(tlnum));
}

// 开始功能时间戳记录
int BUTLBegin()
{
   return(g_BUTL.Begin());
}

// 时间戳记录
int BUTLPush(const char *file, int lineno,const char *desc)
{
   return(g_BUTL.Push(file,lineno,desc));
}

// 将时间戳记录dump到文件中
int BUTLDump()
{
   return(g_BUTL.Dump());
}


/* ****** Updated by CHENYH at 2004-3-10 22:17:31 ****** 
// 函数名: SetCol
// 编程  : 陈永华 2004-2-8 23:26:38
// 描述  : 设置CPACK报文位图；当已经用PutRow输出了数据记录，则将上次数据打包发送给原请求端
// 返回  : int 0:成功；与BCC通讯出现问题，建议业务取消处理
// 参数  : void *handle － 暂时就对应的 TRUSERID *, 在本系统没有意义，因为单线程的缘故
// 参数  : ...  用 F_XXXXX 定义的相关字段列表，用END_FIELD表示结束；当handle后即为END_FIELD，则清空位图重新设置位图
*/
int SetCol(TRUSERID *handle,...)
{
	va_list ap;
	int arg;
   ST_PACKHEAD head;
   memset(&head,0,sizeof(head));
	va_start(ap, handle);

/* ****** Updated by CHENYH at 2005-1-25 14:27:25 ****** 
	while ((arg = va_arg(ap, int)) != 0)
*/
   while ((arg=va_arg(ap,int))>=0)
//////////////////////////////////////////////////////////////////////////
	{
		SetParmBit( &head, arg);
	}
	va_end(ap);
   return(g_SvrLink.SetCol(handle,head.ParmBits));
}



/* ****** Updated by CHENYH at 2005-6-27 19:45:04 ****** 
本函数因为有PutRow，所以不再需要了。
// 函数名: PutRowData
// 编程  : 陈永华 2004-2-8 23:30:07
// 描述  : 在输出的CPACK报文中增加一条ST_PACK报体记录，实际对之前用SetCol定义的字段有效，没有定义的无效
// 返回  : int 0:成功；与BCC通讯出现问题，建议业务取消处理
// 参数  : ST_PACK *pdata  － 增加的ST_PACK存放数据
int PutRowData(ST_PACK *pdata)
{
   return(g_SvrLink.PutRowData(pdata));
}
*******************************************************/

// 函数名: AnswerData
// 编程  : 陈永华 2004-2-8 23:32:42
// 描述  : 向ruserid的客户端，发送由SetCol和PutRowData设置的应答返回的数据
// 返回  : int 0:成功；否则即为与BCC通讯出现问题，建议业务取消处理
// 参数  : TRUSERID *ruserid  目标客户端的标识
// 参数  : int retcode 应答数据的返回码 对应ST_CPACK的头中的RetCode
// 参数  : char *szmsg 如果为NULL或“”，则应答数据中，就不包括vsmess字段数据
int AnswerData(TRUSERID *ruserid,int retcode,char *szmsg)
{
   return(g_SvrLink.AnswerData(ruserid,retcode,szmsg,0));
}


// 函数名: AnswerDataPart
// 编程  : 陈永华 2004-2-12 12:12:09
// 描述  : 与AnswerData类似，但是用于通知客户端，还有更多的数据返回
//         常用于将有大批量数据返回，尽管数据项相同但是为了不让客户端长时间等待
//         先发送部分数据。
// 返回  : int 0:成功；否则即为与BCC通讯出现问题，建议业务取消处理
// 参数  : TRUSERID *ruserid
// 参数  : int retcode
// 参数  : char *szmsg
int AnswerDataPart(TRUSERID *ruserid,int retcode,char *szmsg)
{
   return(g_SvrLink.AnswerData(ruserid,retcode,szmsg,1));
}

// 函数名: AnswerDataEx
// 编程  : 陈永华 2004-2-8 23:37:00
// 描述  : 向ruserid的客户端，发送apack和pArrays组成应答返回的数据
// 返回  : int 0:成功；否则即为与BCC通讯出现问题，建议业务取消处理
// 参数  : TRUSERID *ruserid  目标客户端的标识
// 参数  : ST_CPACK *apack  应答数据头和首报体
// 参数  : ST_PACK *pArrays 后续数据报体，当apack->head.RetCount<=1时候，无效 可以填写为NULL
// 参数  : int retcode 应答数据的返回码 对应ST_CPACK的头中的RetCode
// 参数  : char *szmsg 如果为NULL或“”，则应答数据中，就不包括vsmess字段数据
int AnswerDataEx(TRUSERID *ruserid,ST_CPACK *apack,ST_PACK *pArrays,int retcode,char *szmsg)
{
   return(g_SvrLink.AnswerDataEx(ruserid,apack,pArrays,retcode,szmsg));
}

// 函数名: PushData
// 编程  : 陈永华 2004-2-8 23:43:01
// 描述  : 向一个作为服务方式注册的目标点，推送数据
// 返回  : int 0:成功；否则即为与BCC通讯出现问题，建议业务取消处理
// 参数  : int sourceno  推送数据使用的通讯平台的编号，参见TRUSERID::SourceNo
// 参数  : int destno    推送数据的目标通讯平台编号
// 参数  : int funcno    目标服务端在通讯平台上注册的通讯功能号
// 参数  : int batchno   针对该目标点会话批次号
// 参数  : ST_CPACK *ppack  推送的数据包，ppack->head.RetCount<=1，即推送数据不能超过1条报体记录
// 参数  : char pushmode  推送模式，见上述定义的PM_xxx
// 参数  : int acktime   确认回答的期限，以秒计，对于PM_ACK ,PM_ANSWER 有效 
int PushData(int sourceno,int destno,int funcno,int batchno,ST_CPACK *ppack,char pushmode,int acktime)
{
   return(g_SvrLink.PushData(sourceno,destno,funcno,batchno,ppack,pushmode,acktime));
}



// 函数名: ExtCall
// 编程  : 陈永华 2004-3-6 17:47:14
// 描述  : 向另外一个服务点发送请求，要求对方处理应答返回，本功能常常用于不同系统之间的对接，如要求其他外围系统服务
// 返回  : int >=0:成功，返回的为应答数据包体记录数；<0:错误；-2:等待接收应答超时；-1:其他通讯错误
// 参数  : int sourceno  使用的通讯平台的编号，参见TRUSERID::SourceNo
// 参数  : int destno    目标通讯平台编号
// 参数  : int funcno    目标服务端在通讯平台上注册的通讯功能号
// 参数  : int batchno   该目标点会话批次号 (如果确认针对该目标点，不会有其他的推送模式，则可以直接填写为0)
// 参数  : int acktime   该请求的有效时间，以秒计
// 参数  : ST_CPACK *rpack  请求包数据
// 参数  : ST_CPACK *apack  目标点应答的数据返回
// 参数  : ST_PACK *pArrays 应答数据后续包数据
int ExtCall(int sourceno,int destno,int funcno,int batchno,int acktime,ST_CPACK *rpack,ST_CPACK *apack,ST_PACK *pArrays)
{
   return(g_SvrLink.ExtCall(sourceno,destno,funcno,batchno,acktime,rpack,apack,pArrays));
}

int ExtTransfer(unsigned short destno, unsigned short funcno, ST_CPACK *rpack, ST_PACK *pArrays)
{
   return(g_SvrLink.ExtTransfer(destno,funcno,rpack,pArrays));
}

// 函数名: GetRequestHead
// 编程  : 沈海 2008-3-6 09:38:11
// 描述  : 将原始的请求包头复制到phead
// 返回  : void 
// 参数  : ST_PACKHEAD *phead[OUT]: 存放复制的包头
void GetRequestHead(ST_PACKHEAD *phead)
{
   g_SvrLink.GetRequestHead(phead);
}

// 函数名: GetAnswerHead
// 编程  : 沈海 2008-3-6 09:43:29
// 描述  : 将当前应答包头复制到phead
// 返回  : void 
// 参数  : ST_PACKHEAD *phead[OUT]: 存放复制的包头
void GetAnswerHead(ST_PACKHEAD *phead)
{
   g_SvrLink.GetAnswerHead(phead);
}

// 函数名: SetAnswerHead
// 编程  : 沈海 2008-3-13 16:07:29
// 描述  : 将phead复制到应答包
// 返回  : void
// 参数  : TRUSERID *handle[IN]: 暂时不使用，为以后扩展保留 
// 参数  : ST_PACKHEAD *phead[OUT]: 存放复制的包头
void SetAnswerHead(TRUSERID *handle, ST_PACKHEAD *phead)
{
   g_SvrLink.SetAnswerHead(handle, phead);
}



// 函数名: ExtCallNext
// 编程  : 陈永华 2004-3-8 17:31:47
// 描述  : 在调用ExtCall之后，发现对方尚有数据还没有取回来，则用本功能获取后续数据
// 返回  : int >=0:成功，返回的为应答数据包体记录数；<0:错误；-2:等待接收应答超时；-1:其他通讯错误；-3:已经取完了后续数据
// 参数  : int acktime
// 参数  : ST_CPACK *apack
// 参数  : ST_PACK *pArrays
int ExtCallNext(int acktime,ST_CPACK *apack,ST_PACK *pArrays)
{
   return(g_SvrLink.ExtCallNext(acktime,apack,pArrays));
}


// 函数名: PushDataEx
// 编程  : 陈永华 2004-2-9 0:10:53
// 描述  : 向pushdests定义的作为服务方式注册目标点推送数据
// 返回  : int 0:成功；否则即为与BCC通讯出现问题，建议业务取消处理
// 参数  : TPUSHDEST *pushdests 定义的目标点列表
// 参数  : int pdcount  目标点的个数
// 参数  : ST_CPACK *ppack 推送的不超过一条记录的数据包
// 参数  : char pushmode 推送模式，见上述定义的PM_xxx
// 参数  : int acktime  确认回答的期限，以秒计，对于PM_ACK ,PM_ANSWER 有效 
int PushDataEx(TPUSHDEST *pushdests,int pdcount,ST_CPACK *ppack,char pushmode,int acktime)
{
   return(g_SvrLink.PushDataEx(pushdests,pdcount,ppack,pushmode,acktime));
}



// 函数名: PutRow
// 编程  : 陈永华 2004-2-20 10:03:04
// 描述  : 一次性完成PutRowData 和 AnswerData, 但是并不马上发送 （为了与大集中版本兼容）
// 返回  : int 0:成功；否则即为与BCC通讯出现问题，建议业务取消处理
// 参数  : TRUSERID *handle
// 参数  : ST_PACK *pdata
// 参数  : int *pRetCode
// 参数  : char *rtnMsg
int PutRow(TRUSERID *handle,ST_PACK *pdata,int *pRetCode,char *rtnMsg)
{
   return(g_SvrLink.PutRow(handle,pdata,*pRetCode,rtnMsg));
}



// 函数名: CT_ERR_DEAL
// 编程  : 陈永华 2004-2-22 16:39:51
// 描述  : 清除原来准备的应答信息，并且在运行时跟踪文件中记录（错误）信息（为了与集中交易兼容）
// 返回  : int 0:成功；否则即为与BCC通讯出现问题，建议业务取消处理
// 参数  : char *msg
// 参数  : int retcode
int CT_ERR_DEAL(char *msg,int retcode)
{
   return(g_SvrLink.Err_Deal(msg,retcode));
}


// 函数名: Error_Deal
// 编程  : 陈永华 2004-2-22 16:43:34
// 描述  : 清除原来准备的应答信息，并且在运行时跟踪文件中记录（错误）信息 建议新系统使用本函数替代原来的ERR_DEAL
//         合并了原来需要用sprintf生成omsg
// 返回  : int 0:成功；否则即为与BCC通讯出现问题，建议业务取消处理
// 参数  : int retcode
// 参数  : char *omsg  OUT
// 参数  : char *pFormat IN
// 参数  : ... IN
int Error_Deal(int retcode,char *omsg,char *pFormat,...)
{
   va_list pArg;
   va_start(pArg,pFormat);
   vsprintf(omsg,pFormat,pArg);
   va_end(pArg);
   return(CT_ERR_DEAL(omsg,retcode));
}


// 函数名: SQLDebugLog
// 编程  : 陈永华 2004-3-4 17:45:16
// 描述  : 专门为了SQC使用（在C中使用的）记录信息到LOG日志中
// 返回  : void 
// 参数  : int errorcode
// 参数  : char *pFormat
// 参数  : ...
void SQLDebugLog(int errorcode,char *pFormat,...)
{
   char omsg[8192];
   va_list pArg;
   if (g_pLogFile==NULL)
      return;
   va_start(pArg,pFormat);
   vsprintf(omsg,pFormat,pArg);
   va_end(pArg);
   g_pLogFile->WriteLogEx(errorcode,"%s",omsg);   
}

void TextLogOut(int errorcode, char *textlog)
{
   g_pLogFile->WriteLogEx(errorcode,"%s",textlog);
}


// 函数名: CheckProcCancel
// 编程  : 陈永华 2004-3-10 15:44:20
// 描述  : 检查是否本处理请求，前台是否要求停止。注意：这个由于要检查连接上是否有该停止命令而会导致等1毫秒，而使得处理效率降低
// 返回  : int 1:表示前台有要求停止的命令；0:没有
int CheckProcCancel()
{
   if (g_SvrLink.CheckProcCancel())
      return(1);
   else 
      return(0);
}

// 函数名: SetAnswerMode
// 编程  : 陈永华 2004-3-10 18:48:18
// 描述  : 更改应答模式，见AM_xxxx的定义
// 返回  : int 0:成功；否则即为与BCC通讯出现问题，建议业务取消处理
// 参数  : char iAnswerMode 见AM_xxxx的定义
int SetAnswerMode(char iAnswerMode)
{
   return(g_SvrLink.SetAnswerMode(iAnswerMode));
}


// 函数名: BCCMsgLogOut
// 编程  : 陈永华 2004-3-10 19:31:25
// 描述  : 由BCC集中输出本BU的文本日志信息
// 返回  : int 0:成功；否则即为与BCC通讯出现问题，建议业务取消处理
// 参数  : int logid ：本日志的ID号
// 参数  : char *pFormat ：文本日志的格式定义
// 参数  : ... ：以pFormat定义的输出参数
int BCCMsgLogOut(int logid,char *pFormat,...)
{
   char omsg[1024];
   va_list pArg;
   va_start(pArg,pFormat);
   vsprintf(omsg,pFormat,pArg);
   va_end(pArg);
   return(g_SvrLink.BCCLogOut(LT_MSG,logid,strlen(omsg),omsg));
}


// 函数名: ResetNormalCPack
// 编程  : 陈永华 2004-3-11 20:30:59
// 描述  : 根据本业务请求包，设置一个CPACK包头，位图和数据都被清空了
// 返回  : void 
// 参数  : ST_CPACK *pack
void ResetNormalCPack(ST_CPACK *pack,unsigned char nextflag,int recCount)
{
   g_SvrLink.ResetNormalCPack(pack,nextflag,recCount);
}


// 函数名: SetMaxRow
// 编程  : 陈永华 2004-3-22 11:41:26
// 描述  : 设置本次功能处理时候，每个应答包返回的最大记录数，只对本次功能处理有效
// 返回  : int 0:成功；否则即为与BCC通讯出现问题，建议业务取消处理
// 参数  : int maxrows
int SetMaxRow(int maxrows)
{
   return(g_SvrLink.SetMaxRow(maxrows));
}


// 函数名: SetBUError
// 编程  : 陈永华 2004-3-22 11:42:37
// 描述  : 设置本BU出错信息，用于提供给前端程序
// 返回  : int 0:成功；否则即为与BCC通讯出现问题，建议业务取消处理
// 参数  : int errcode
// 参数  : char *pFormat
// 参数  : ...
int SetBUError(int errcode,char *pFormat,...)
{
   char omsg[1024];
   va_list pArg;
   va_start(pArg,pFormat);
   vsprintf(omsg,pFormat,pArg);
   va_end(pArg);
   return(g_SvrLink.SetBUError(errcode,omsg));   
}


// 函数名: SetAnswerTimeout
// 编程  : 陈永华 2004-3-22 12:49:02
// 描述  : 设定本业务每个应答包的超时时间，以毫秒计，常用于如批结算时候特殊的处理
// 返回  : int 0:成功；否则即为与BCC通讯出现问题，建议业务取消处理
// 参数  : unsigned int atimeout  指定的超时时间（以毫秒计）
int SetAnswerTimeout(unsigned int atimeout)
{
   return(g_SvrLink.SetAnswerTimeout(atimeout));
}




// 函数名: ResetAnswerData
// 编程  : 陈永华 2004-3-24 22:16:17
// 描述  : 重置清除已经提交的应答数据，常用于重新执行一个处理，比如因为程序死锁后Retry
// 返回  : int 
int ResetAnswerData()
{
   return(g_SvrLink.ResetAnswerData());
}

// 函数名: GetDRTPSvrRegStatus
// 编程  : 陈永华 2010-1-15 17:11:16
// 描述  : 获取通讯平台上指定服务功能号注册的状态 (只能查DRTP4，且为新版本)
// 返回  : int 0 不存在，1本地存在，2 其它地方存在，3本地和其它地方都存在; -1未知; -1001，-1002: BCC/BU之间数据交换异常
// 参数  : int sourceno [IN]: 通过DRTP的编号，请使用TRUSERID::SourceNo，或0
// 参数  : int svrfuncno [IN]: 指定查询的注册服务功能号
int GetDRTPSvrRegStatus(int sourceno, int svrfuncno)
{
   return(g_SvrLink.GetSvrFuncRegister(sourceno,svrfuncno));
}



// 函数名: GetReqUserID
// 编程  : 陈永华 2010-1-15 18:14:52
// 描述  : 将TRUSERID转换为请求方消息交换的标识字符串
// 返回  : int :返回的标识字符串长度
// 参数  : TRUSERID *handle [IN]: 当为NULL的时候，即为当前请求方
// 参数  : char *sRUserID [OUT]: 标识字符串的缓存，长度应在100字节以上
int GetReqUserID(TRUSERID *handle, char *sRUserID)
{
   return(g_SvrLink.GetReqUserID(handle,sRUserID));
}



// 函数名: BookPostData
// 编程  : 陈永华 2010-1-18 15:32:32
// 描述  : 推送订阅数据综合函数
// 返回  : int 0: 成功提交任务；<0: 错误或失败。其中： -3: sRUserID内部数据错误；-1000: pdlen错误(不能<0或>MAXMSG); 
// 参数  : unsigned int postdno [IN]: 订阅源的标识值
// 参数  : const char *sRUserID[IN]: 订阅源最新的路由数据，根据GetReqUserID获得
// 参数  : void *pdata [IN]: 消息数据，在特殊的pushmode下可以为NULL
// 参数  : int pdlen [IN]: 消息数据长度，在特殊的pushmode下可以为0，但不能大于8000
// 参数  : char pushmode [IN]: 推送订阅模式:PM_CLEAR－放弃所有对该点的推送任务；PM_INACK-不用确认的推送模式；PM_ACK-可靠推送模式
// 参数  : int acktime [IN]: 对PM_ACK有效，即本推送订阅消息的有效时间，秒计－可能会多1秒左右
int BookPostData(unsigned int postdno, const char *sRUserID, void *pdata, int pdlen, char pushmode, int acktime)
{
   return(g_SvrLink.PostBookData(postdno,sRUserID,pdata,pdlen,pushmode,acktime));
}


// 函数名: BookUpdatePost
// 编程  : 陈永华 2010-1-19 10:10:45
// 描述  : 更新订阅目标点的路由信息
// 返回  : int 0: 成功提交任务；<0: 错误或失败。其中： -3: sRUserID内部数据错误；
// 参数  : unsigned int postdno
// 参数  : const char *sRUserID
int BookUpdatePost(unsigned int postdno, const char *sRUserID)
{
   return(g_SvrLink.PostBookData(postdno,sRUserID,NULL,0,'1',0));  // PM_ACK:'1'
}


// 函数名: GetBaseFuncNo
// 编程  : 陈永华 2010-8-19 9:44:25
// 描述  : 取BCC的公共功能号，即在KSMBCC.INI中的BASEFUNCNO=的配置项
//          只能在BU正常启动，并与BCC连接成功后方能获得正确值
// 返回  : int BCC在通讯平台上注册的公共通讯功能号
int GetBaseFuncNo()
{
   return(g_SvrLink.bccBFuncNo);
}


// 函数名: GetBCCID
// 编程  : 陈永华 2010-8-19 9:47:59
// 描述  : 取BCC的ID号，即在KSMBCC.INI中的ID=配置项
//          只能在BU正常启动，并与BCC连接成功后方能获得正确值
// 返回  : int 
int GetBCCID()
{
   return(g_SvrLink.bccID);
}

// 函数名: CheckPushPack
// 编程  : 陈永华 2010-12-2 12:20:55
// 描述  : 检查请求数据是否是属于推送过来的请求包
// 返回  : int : 1 - PM1, 1类推送数据包；2 - 请求功能的推送消息；3 - 应答功能的推送消息；0 - 其他类型
// 参数  : char *oQueueID16 [OUT]: 16字节以上的缓存，用于获取推送请求的QueueID，这个用于匹配原始请求和应答的ID
int CheckPushPack(char *oQueueID16)
{
   return(g_SvrLink.CheckPushPack(oQueueID16));
}

int CBUTL::Set(int tlnum)
{
   Close();
   if (tlnum>0)
   {
      if (tlnum<50)
         tlnum = 50;
      pLog = new T_TICKLOG[tlnum];
      if (pLog!=NULL)
      {
         fp = sh_fopen("cyhbuticks.txt","at",SH_DENYNO);
         m_maxtls = tlnum;
      }
      else
      {
         tlnum = 0;
      }
   }
   return(tlnum);
}

void CBUTL::Close()
{
   m_itl = 0;
   if (m_maxtls>0)
   {
      if (pLog!=NULL)
         delete [] pLog;
      pLog = NULL;
      if (fp!=NULL)
         fclose(fp);
      fp = NULL;
      m_maxtls = 0;
   }
}

int CBUTL::Begin()
{
   if (m_maxtls<=0)
      return(0);
   m_itl = 0;
   return(1);
}

int CBUTL::Push(const char *file, int lineno, const char *desc)
{
   if (m_maxtls<=0)
      return(0);
   if (m_maxtls<=m_itl)
      return(m_itl);
   if (file!=NULL)
   {
      STRNCPY(pLog[m_itl].file,file);
      pLog[m_itl].line = lineno;
      pLog[m_itl++].tickus = GetTickCountUS();
      return(m_itl);
   }
   else
      return(0);
}

int CBUTL::Dump()
{
   int i=-1;
   if (fp!=NULL)
   {
      for (i=0;i<m_itl;++i)
      {
         fprintf(fp,"%d\t%u\t%d\t%s\n",
            i+1,pLog[i].tickus,pLog[i].line,pLog[i].file);
      }
      m_itl = 0;
   }
   return(i);
}
