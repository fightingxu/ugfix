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
   char     ExecType;      // Tag150 - ExecType ����
   int      ExecID;        // ExecID��nnn
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
   int      nDays;            // ExecID:  'nnnDmm-<OrderID>'�е�D�����mm
   double   OrderQty;         // Order Qty
   double   CumQty;           //                   
   // ����ʵ��Ӧ���н������ Unsolicited Cancel�����  2009-5-4 11:39:25
   // bool     bCanceled;        // �Ƿ��Ѿ���(6 = Pending Cancel) or (E = Pending Replace) �Ա�˳������Ƿ���Է��� Cancel Reject
   unsigned char bmCancel;    // 0x01λ����ʾ�Ƿ���Order Cancel/Order Replace������; 0x02λ����ʾ�Ƿ���Pending Cancel/Pending Replace
   int      SentSeqNo;        // �Ѿ������˵Ķ���ִ�����
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
   CMUTEX m_mutex;         // Ϊ�˱�֤���ⲿ���õĹ��ܲ��͹����̳߳�ͻ

   int m_opentime;         // HHMM
   int m_closetime;        // HHMM
   int m_eodtime;          // HHMM��<0: ���Զ�ִ��EOD����
   std::string mfpath;
   std::string bfpath;

   int m_connectmode;      // CM_TCP_SERVER or CM_TCP_CLIENT

   std::string m_luser;    // ������Է����͵��û��� 
   std::string m_lpass;    // ������Է����͵Ŀ���

   std::string m_puser;    // �Է����û���
   std::string m_ppass;    // �Է��Ŀ���

   std::string m_logpath;  // ��־·��

   //////////////////////////////////////////////////////////////////////////
   // �������ڲ���¼�õ�
   CMutexEvent inMsgMutexEvent;
   L_MSGDATA inMsgs;
   //////////////////////////////////////////////////////////////////////////
   
   CMutexEvent outMsgMutexEvent;
   L_MSGDATA outMsgs[2];      // ע�⣺��Ϊ���ܹ�����Ϣ���������ȼ�:0 ���� 1
   
   CMUTEX m_SSDMutex;   // Ϊ�˱���SS_OData
   L_ORDDATA SS_OData;  // Ϊ�˸��Է����������ExecRpt / CancelReject����Ϣ
   
   time_t m_OTRunTime;  // Out�̵߳�����ˢ��ʱ��

   bool m_bStop;  // �ⲿָʾ�Ƿ��˳�
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
