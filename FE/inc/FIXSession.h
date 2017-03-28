// FIXSession.h: interface for the CFIXSession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIXSESSION_H__F2D6DE78_B147_4782_A8EB_E6246FA8DC3D__INCLUDED_)
#define AFX_FIXSESSION_H__F2D6DE78_B147_4782_A8EB_E6246FA8DC3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>
#include <list>
#include <map>
#include "mutex.h"
#include "MsgDataList.h"
#include "ugate.h"


// for TAG39-OrdStatus; TAG150-ExecType
#define ET_NEW          '0'   // 0 = New
#define ET_PFILLED      '1'   // 1 = Partial fill (Replaced)
#define ET_FILLED       '2'   // 2 = Fill (Replaced)
#define ET_DFD          '3'   // 3 = Done for day
#define ET_CANCELED     '4'   // 4 = Canceled
#define ET_REPLACE      '5'   // 5 = Replace
#define ET_PENDINGC     '6'   // 6 = Pending Cancel (e.g. result of Order Cancel Request)
#define ET_STOPPED      '7'   // 7 = Stopped
#define ET_REJECTED     '8'   // 8 = Rejected
#define ET_SUSPENDED    '9'   // 9 = Suspended
#define ET_PENDINGN     'A'   // A = Pending New
#define ET_CALCULATED   'B'   // B = Calculated
#define ET_EXPIRED      'C'   // C = Expired
#define ET_RESTATED     'D'   // D = Restated (ExecutionRpt sent unsolicited by sellside, with ExecRestatementReason (378) set)
#define ET_PENDINGR     'E'   // E = Pending Replace (e.g. result of Order Cancel/Replace Request)
#define ET_TRADE        'F'   // F = Trade (partial fill or fill)
#define ET_TRADECORRECT 'G'   // G = Trade Correct (formerly an ExecTransType (20))
#define ET_TRADECANCEL  'H'   // H = Trade Cancel (formerly an ExecTransType)
#define ET_ORDERSTATUS  'I'   // I = Order Status (formerly an ExecTransType)

#define ETX_CREJECT     'x'   // 本系统扩展用，表示MsgType='9': 撤单被拒绝的情况

#define CANCELEDSNO     999999

class COrdExec  
{
public:
   char     ExecType;      // Tag150 - ExecType 见上
   int      ExecID;        // ExecID的nnn
   double   CumQty;        // Tag14
   string   FIXMsg;
public:
   COrdExec();
   COrdExec(const COrdExec &copyExec);
   virtual ~COrdExec();
   
};
typedef std::list<COrdExec> L_ORDEXEC;

class COrderData  
{
public:
   string   ClOrdID;          // BS's Order ID     11 / 41
   int      nDays;            // ExecID:  'nnnDmm-<OrderID>'中的D后面的mm
   double   OrderQty;         // Order Qty
   double   CumQty;           //                   
   // 由于实际应用中将会存在 Unsolicited Cancel的情况  2009-5-4 11:39:25
   // bool     bCanceled;        // 是否已经有(6 = Pending Cancel) or (E = Pending Replace) 以便顺序决定是否可以发送 Cancel Reject
   unsigned char bmCancel;    // 0x01位，表示是否有Order Cancel/Order Replace的请求; 0x02位，表示是否有Pending Cancel/Pending Replace
   int      SentSeqNo;        // 已经发送了的订单执行序号
   L_ORDEXEC   ExecList;      // 
   
public:
   COrderData();
   COrderData(const COrderData &copyData);
   virtual ~COrderData();
   
};
typedef std::map<string, COrderData> L_ORDDATA;
typedef L_ORDDATA::iterator IT_ORDDATA;



class CFIXSession  
{
private:
   int m_InMsgSeqNo;

   char m_OutMsg[MAXFIXMSGLEN];  // OutThread专用的buf

   bool m_bToEOD;  // 2013/4/27 14:30:23 由于在未打开Session之前，让FE去做EOD会导致其可能出现异常，
                   // 为此需要在正式打开后去检查是否要做EOD，以完成上次未对FE中的Session做的EOD

public:

   // 2012/12/25 20:11:15
   int m_InMsgs;  // FE中的InMsgs
   int m_OutMsgs; // FE中的OutMsgs

   string m_LocalID;
   string m_PartnerID;
   int m_LastStatus;
   //string m_StatusMsg;
   char m_sStatusMsg[100];

   int m_reload; // 重装配置计数
   bool m_InOpen; // 表示处于打开状态

   /* Removed by CHENYH @ 2012/8/24 17:11:31
   不再使用这里的队列, 而是改用UGATE中提供的队列
   // 由于在FE的handleMessageReceived中直接处理了向FS提交消息数据，因此似乎这个缓存没有啥用了
   // 另外向FS的提交消息数据的所有处理，都是通过异步推送的，因此，几乎不需要等待，因此，也就
   // 不会导致FE的阻塞。因此，就不再需要下面的inMsg队列了。
   CMutexEvent inMsgMutexEvent;
   L_MSGDATA inMsgs;
   //////////////////////////////////////////////////////////////////////////
   
   CMutexEvent outMsgMutexEvent;
   L_MSGDATA outMsgs[2];      // 注意：这为了能够将消息分两级优先级:0 高于 1
   */

   CMUTEX m_SSDMutex;   // 为了保护SS_OData
   L_ORDDATA SS_OData;  // 为了给对方发送有序的ExecRpt / CancelReject等消息

   time_t m_OTRunTime;  // Out线程的运行刷新时间
   bool m_bStop;        // 作为各个线程是否停止退出的检查

private:
	void ReflushStatus();
	int RestoreInMsg(int msglen, const char *fixmsg);
	void RestoreInFIXMsgs();
	void RestoreOutFIXMsgs();
	IT_ORDDATA CheckSSOrderData(T_UGDATA *pUGData);

public:
	void CheckEODAfterOpen();
	bool IsNewInMsg(int msgseqnum);
	unsigned int GetLoad();
	bool IsLoadFESession();
	void SetError(int status, const char *eMsg, int inmsgs, int outmsgs);
	bool IsRun();
	void ToStopThreads();
	void OTRun();
	int GetStatusInfo(char *statusinfo, unsigned int sisize);
	void StatusChanged(int newState, int oldState, int reasonCode, const char *reasonText);
	int GetReloadCount();
	int DoEODProcess();
	int UpdateSSData(T_UGDATA *pUGData, const char *fixmsg);
	bool PreOpen(char *eMsg);
	void HaveOutMsg(int msglen, const char *msg,int plevel=0);
	void Set(const char *sLocalID, const char *sPartnerID);
	CFIXSession();
	virtual ~CFIXSession();

};

// FIX Session Out Thread Entry:
void OThreadRun(void *pAvg); 


#endif // !defined(AFX_FIXSESSION_H__F2D6DE78_B147_4782_A8EB_E6246FA8DC3D__INCLUDED_)
