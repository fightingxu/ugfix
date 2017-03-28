// FIXSession.h: interface for the CFIXSession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIXSESSION_H__094D5AC4_9FA2_4A8F_91D1_59510B42E61E__INCLUDED_)
#define AFX_FIXSESSION_H__094D5AC4_9FA2_4A8F_91D1_59510B42E61E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "tcp.h"
#include <string>
#include "FIXData.h"
#include "logfile.h"
#include "FIXAppData.h"

// 由于本类不可以以"发起方(Client)" 和 "服务方(Server)" 两种方式进行，因此，这里不负责连接的建立和登陆过程的控制
class CFIXSession  
{
public: 
   CFIXAppData m_Persistence;
   CLogFile m_LogFile;
   
   char m_FSMPath[260];
   char m_FSBPath[260];

   //////////////////////////////////////////////////////////////////////////
   // 需要外部设置的各类参数
   char m_FSName[64];
   bool bNeedSendingTime; // 本Session的FIX消息中是否需要SendingTime

   std::string m_localid;
   std::string m_partnerid;
   std::string m_fixversion;
   
   unsigned int m_outHeartBtInt; // = setup.heartbtInt(30);
   unsigned int m_inHeartBtInt;  // = setup.heartbtInt(30) + setup.heartbtLatency(5);
   
   //////////////////////////////////////////////////////////////////////////
   // Server模式的时候：在外部建立连接的时候设置，Client则在建立连接之前设置，并使用它们
   char m_partnerip[64];     // 对端的IP地址
   int  m_partnerport;       // 对端的端口号

   //////////////////////////////////////////////////////////////////////////
   // 下面是外部可以检查的数据：
   CTcpSocket m_sock;
   CFIXData m_recvFIXData;  // 当收到了完整数据包后，从m_datakeep中截取的消息数据，转存到这里

   int  m_state;    // 本FIX连接的状态类型
   enum FIXSTATE 
   {
      FIXST_CLOSE,
      FIXST_CONNECTING,    // 连接链路已经建立，但还没有完成LOGN之前
      FIXST_OPEN           // LOGON消息交换完毕，开始进行正式的FIX数据交换状态
   };
   
   time_t tmLastRecv; // 最后一次收到对方消息的时间点
   time_t tmLogon;    // 正式登录时间
   time_t tmLastSent; // 最后一次发送消息的时间点，用于心跳控制
   
   int incomingSeqNumber;  // 最后一个收到消息的序号
   int outgoingSeqNumber;  // 最后一个发送消息的序号
   
protected:
   int m_GapFillSeqNo;   // <=0: 同步状态；>0: 即需要填补或被Reset到指定的序号，才恢复到同步状态

   T_REJECTMSG m_rejmsg;

   char m_datakeep[MAXFIXDATALENGTH];  // 保存已经接收到的尚未完整的数据缓存
   int  m_InMsgLen;  // 当CheckDataKeep为true时候，为当前完整的InMsg长度
   int  m_dklen;   // 已经接收到的数据临时保存长度
   
   unsigned int TestReqID;   // MsgType=1的时候用，存放最后一次Test消息中的，用于同步（检查对方该发送的消息已经全部被本方收到）
   time_t tmTestReq;        // 0 - 还没有发送TestReq包，或者收到的了对方对应的HeartBeat包； 否则，表示已经发送了TestReq，但还没有收到对应的HeartBeat包
   
   int  logon;   // Logon消息发送状态 : 0 没有发送过；1 已经发送了Logon消息；2 已经收到Logon，并也已经发送了Logout，并且本连接被关闭了 (注意在做EOD的主动发起方要将logon归位)
   int  logout;   // Logout消息发送状态 : 0 没有发送过；1 已经发送了Logout消息；2 已经收到Logout，并也已经发送了Logout，并且本连接被关闭了
public:
   int GetStatus();
   // 设置本Session的心跳间隔参数
   void SetHeartBtInt(int hbt, int hbtlatency);

protected:
	int OnLogout();
	int DoEndOfDay();

	bool SetFIXVersion(const char *fixversion);
	bool IsLinkOK();
	void SetSendingTime(bool bMandatory);
	void ToClose();

	int OnSequenceReset();

   // ip_port - <PartnerIP>:<PartnerPort>
	bool SetPartnerConnect(const char *ip_port);

   // sessionid: <LocalID>-<PartnerID>
	bool SetSessionID(const char *sessionid);
   
   // 函数名: InitOutFIXData
   // 编程  : 陈永华 2011-4-22 22:54:36
   // 描述  : 将 pFIXData的头部初始化
   // 返回  : void 
   // 参数  : CFIXData *pFIXData [OUT]: 被设置的CFIXData
   // 参数  : const char *MsgType [IN]: MsgType的值
   void InitOutFIXData(CFIXData *pFIXData, const char *MsgType);
   
   // 函数名: SendFIXMsg
   // 编程  : 陈永华 2011-4-22 22:48:14
   // 描述  : 将pfixdata以标准的FIX规范格式发送给对方
   // 返回  : int <0: 发送错误；>0: 成功，返回发出去的消息序号 outgoingMsgSeqNum
   // 参数  : CFIXData *pfixdata [IN]: 已经设置好的fix消息数据
   int SendFIXMsg(CFIXData *pfixdata);

	CFIXSession();
	virtual ~CFIXSession();

   virtual void OnUndefinedInMsgType();

   int ToCheckTest();

	int SendResendRequest(int beginSeqNo, int endSeqNo=0);
	int CheckInSequenceNumber();
   // Function name: CFIXSession::OpenFIXStorePath
   // Author       : CHENYH 2012/5/26 14:13:13
   // Description  : 打开FIX状态持久化，并恢复InSeq和OutSeq，已准备正式数据交换
   //  !!! 本操作要在正式确认为已设定的Session之后，才可调用。
   //  CM_TCP_SERVER: 是在接受到对方连接，并得到Logon消息后，确认本连接的Session之后，准备发送Logon消息之前调用；
   //  CM_TCP_CLIENT: 则是设定好Session之后，准备发送Logon消息之前调用。
   // Return type  : bool 返回是否打开成功
   // Argument : const char *mpath [IN]: 主存储目录路径，必须为有，并且可以创建的路径；否则，将返回失败
   // Argument : const char *bkpath [OUT]: 备存储目录路径，可以为NULL或""来表示无备存储路径
   bool OpenFIXStorePath(const char *mpath, const char *bkpath=NULL);
   
	int ResendFIXMsg(char *fixdata, int fdlen);
	bool ValidRecvSessionID();
   // 当收到Session Level的ResendRequest的标准处理
	int OnResendRequest();
   // 发送SeqReset的标准FIX Session Level的消息
	int SendSeqReset(int tag34, int NewSeqNum, bool Gap_Fill=true, bool dup=false);
	int SendTestReq();
	int SendLogout(const char *logouttxt=NULL);
	int OnHeartBeat();
	int SendHeartBt(const char *TestReqID,const char *tag10031=NULL);
	int OnTestReq(const char *tag10031=NULL);
	int SendLogon(const char *UserName=NULL, const char *Password=NULL, bool bResetSeqNum=false);
	int SendRejectMsg(T_REJECTMSG *pRejMsg);


   // 函数名: CheckRecvFIXData
   // 编程  : 陈永华 2011-4-22 22:56:17
   // 描述  : 检查连接上是否有完整的FIX消息数据
   // 返回  : bool true - m_recFIXData中即为刚刚收到的fix消息数据；false - 还没有收到完整的fix消息
   // 参数  : int timeout [IN]: 完整数据接收的等待时间 (ms)
	bool CheckRecvFIXData(int timeout);

   // 函数名: SendFIXMsg
   // 编程  : 陈永华 2011-4-22 22:51:06
   // 描述  : 将规范化的FIX消息pmsg发送给对方
   // 返回  : int <0: 发送错误；>0: 成功
   // 参数  : const char *pmsg [IN]: fix消息字符串
   // 参数  : int msglen [IN]: fix消息pmsg的长度，以字节计
	int SendFIXMsg(const char *pmsg, int msglen);

private:
   bool ValidFIXData(const char *fixmsg,int fmlen);
   bool CheckDataKeep();
   
};

char *BuildTag52(char *tag52); // 取当前UTCDateTime

#endif // !defined(AFX_FIXSESSION_H__094D5AC4_9FA2_4A8F_91D1_59510B42E61E__INCLUDED_)
