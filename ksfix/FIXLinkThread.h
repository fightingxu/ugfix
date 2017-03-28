// FIXLinkThread.h: interface for the CFIXLinkThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIXLINKTHREAD_H__E88A6F16_B642_42AC_979A_677443FF22D4__INCLUDED_)
#define AFX_FIXLINKTHREAD_H__E88A6F16_B642_42AC_979A_677443FF22D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WThread.h"
#include "FIXSession.h"
#include "MsgDataList.h"

#ifdef _KSFIXSERVER
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
#else
typedef void *L_ORDDATA;
#endif


#define CM_TCP_SERVER 0
#define CM_TCP_CLIENT 1

class CFIXLinkThread : 
	public CFIXSession, 
	public CWThread  
{
public:
private:
   CMUTEX m_mutex;         // 为了保证被外部调用的功能不和工作线程冲突

   int m_opentime;         // HHMM
   int m_closetime;        // HHMM
   int m_eodtime;          // HHMM，<0: 不自动执行EOD工作
   std::string mfpath;
   std::string bfpath;

   int m_connectmode;      // CM_TCP_SERVER or CM_TCP_CLIENT

   std::string m_luser;    // 本方向对方发送的用户名 
   std::string m_lpass;    // 本方向对方发送的口令

   std::string m_puser;    // 对方的用户名
   std::string m_ppass;    // 对方的口令

   std::string m_logpath;  // 日志路径

   //////////////////////////////////////////////////////////////////////////
   // 以下是内部记录用的
   CMutexEvent inMsgMutexEvent;
   L_MSGDATA inMsgs;
   //////////////////////////////////////////////////////////////////////////
   
   CMutexEvent outMsgMutexEvent;
   L_MSGDATA outMsgs[2];      // 注意：这为了能够将消息分两级优先级:0 高于 1
   
   CMUTEX m_SSDMutex;   // 为了保护SS_OData
   L_ORDDATA SS_OData;  // 为了给对方发送有序的ExecRpt / CancelReject等消息
   
   time_t m_OTRunTime;  // Out线程的运行刷新时间

   bool m_bStop;  // 外部指示是否退出
public:
	bool IsFree();
	void HaveOutMsg(int msglen, const char *msg, int plevel);
	int GetInMsg(char *msgbuf, unsigned int waitms);
	void ToCloseSession();
	int ToDoEndOfDay();
	void SetEODTime(int iHHMM);
	bool SetFIXPath(const char *mpath, const char *bkpath);
	int ToOpen(const char *svrip, int svrport);
	void SetSession(const char *localid, const char *partnerid, const char *fixversion="FIX.4.4");
	void SetUserPassword(const char *lusername, const char *lpassword, const char *pusername, const char *ppassword);
	void SetLogPath(const char *logpath);
	CFIXLinkThread();
	virtual ~CFIXLinkThread();
private:
	void MayOutMsg();
	int OnLogon();
	void CheckEOD(time_t tmnow);
	int Run();
	int StartWorkThread();
protected:
	virtual void OnReject();
	int GetOutMsg(char *msgbuf);
	void HaveInMsg();
	void OnRecvInMsg();
};

#endif // !defined(AFX_FIXLINKTHREAD_H__E88A6F16_B642_42AC_979A_677443FF22D4__INCLUDED_)
