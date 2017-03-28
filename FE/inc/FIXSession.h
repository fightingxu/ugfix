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

#define ETX_CREJECT     'x'   // ��ϵͳ��չ�ã���ʾMsgType='9': �������ܾ������

#define CANCELEDSNO     999999

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



class CFIXSession  
{
private:
   int m_InMsgSeqNo;

   char m_OutMsg[MAXFIXMSGLEN];  // OutThreadר�õ�buf

   bool m_bToEOD;  // 2013/4/27 14:30:23 ������δ��Session֮ǰ����FEȥ��EOD�ᵼ������ܳ����쳣��
                   // Ϊ����Ҫ����ʽ�򿪺�ȥ����Ƿ�Ҫ��EOD��������ϴ�δ��FE�е�Session����EOD

public:

   // 2012/12/25 20:11:15
   int m_InMsgs;  // FE�е�InMsgs
   int m_OutMsgs; // FE�е�OutMsgs

   string m_LocalID;
   string m_PartnerID;
   int m_LastStatus;
   //string m_StatusMsg;
   char m_sStatusMsg[100];

   int m_reload; // ��װ���ü���
   bool m_InOpen; // ��ʾ���ڴ�״̬

   /* Removed by CHENYH @ 2012/8/24 17:11:31
   ����ʹ������Ķ���, ���Ǹ���UGATE���ṩ�Ķ���
   // ������FE��handleMessageReceived��ֱ�Ӵ�������FS�ύ��Ϣ���ݣ�����ƺ��������û��ɶ����
   // ������FS���ύ��Ϣ���ݵ����д�������ͨ���첽���͵ģ���ˣ���������Ҫ�ȴ�����ˣ�Ҳ��
   // ���ᵼ��FE����������ˣ��Ͳ�����Ҫ�����inMsg�����ˡ�
   CMutexEvent inMsgMutexEvent;
   L_MSGDATA inMsgs;
   //////////////////////////////////////////////////////////////////////////
   
   CMutexEvent outMsgMutexEvent;
   L_MSGDATA outMsgs[2];      // ע�⣺��Ϊ���ܹ�����Ϣ���������ȼ�:0 ���� 1
   */

   CMUTEX m_SSDMutex;   // Ϊ�˱���SS_OData
   L_ORDDATA SS_OData;  // Ϊ�˸��Է����������ExecRpt / CancelReject����Ϣ

   time_t m_OTRunTime;  // Out�̵߳�����ˢ��ʱ��
   bool m_bStop;        // ��Ϊ�����߳��Ƿ�ֹͣ�˳��ļ��

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
