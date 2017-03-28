// KSFTS.h: interface for the CKSFTS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KSFTS_H__E5512CCC_2F28_4F4E_9621_17CC8C9ABB6C__INCLUDED_)
#define AFX_KSFTS_H__E5512CCC_2F28_4F4E_9621_17CC8C9ABB6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <map>
#include "CJThread.h"
#include "InThread.h"
#include "OutThread.h"
#include "DRTPData.h"
#include "mutex.h"

using namespace std;
typedef struct _T_CLORDINFO {
   char sOrigClOrdID[21];  // ԭʼί�к�
   char sClOrdID[21];      // ����ί�к�
   char sVsvarstr1[21];    // KSFTS�ڲ��ؼ����µ�ϯλ��(��������ָ���Ĳ���Ա��)
} T_CLORDINFO;

typedef map<string,T_CLORDINFO> M_CLORDID; // ί�кţ�[Orig]ClOrdID
typedef map<string,string> M_MARKET;  // FIXExchCode, FTSExchCode ���ձ�

#define MAXOUTTHREADS 20
#define MAXINTHREADS 10

class CKSFTS  
{
private:   
   char   m_XPackFile[256];
   bool   m_bRunning;  // �Ƿ�������״̬
   
   int m_SvrDestNo;
   int m_SvrFuncNo;

   time_t m_LastDoneTime;  // �ϴδ���ر���ʱ���
   int  m_DoneCnt;  // �ر����������
   char   m_LastIContractNo[13]; // �ϴλر�������ڲ���ͬ�� 
   char   m_LastClOrdID[21];  // �ϴλر������ClOrdID

   time_t m_LastOutTime;  // �ϴ������Out��Ϣ��ʱ���
   int  m_OutCnt;
   
   BCHANDLE m_bch;  // ר�ò�KSFTS�������Ŀ������
   
public:
   char m_LocalID[12];    // ���ӿڵı��ض�ID���������ʱ����Ҫ!
   char m_PartnerID[12];  // ���ӿڵĶ��ֶ�ID���������ʱ����Ҫ!

   //char m_WTYYB[4];   // ί��Ӫҵ��
   char m_WTFSx[8];   // �ⲿί��ʱ��ί�з�ʽ��

   char m_Operator[24];  // FIXƽ̨�Ĳ���Ա����

   CDRTPData m_DRouters; // ͨ��ƽ̨��Դ
   int m_OThreadCnt;  // ������KSCTS�ύ��������߳���
   COutThread m_OThreads[MAXOUTTHREADS];
   
   int m_IThreadCnt; // ����KSCTSģʽ��ʽ����ƽ̨�ύ������߳���
   CInThread m_IThreads[MAXINTHREADS];
   
   CCJThread m_CJThread;
   
   int m_Status;   // ��ǰ״̬: -1:��ͣ��0:��û��������1:���������У�2: ��KSCTS���ӳɹ������ڹ�����

   CMUTEX m_WTHMutex;
   M_CLORDID m_WTHMap; // ί�к�-ClOrdID�Ŷ��ձ�

   M_MARKET m_Market; // ������������ձ�

private:
	bool CheckKSFTSSvr(char *emsg);
	bool PreOpen(char *emsg);
	int LoadMarketCode();
   
public:
	const char * GetExchange(const char *sMarketCode);
	int TryCallSvr(BCHANDLE bch, char *errMsg);
	void HaveAnOutMsg();
	char * GetSeatNoFromWTH(const char *sWTH, char *buf, unsigned int bufsize);
	char * GetCustNoFromWTH(const char *sWTH, char *buf, unsigned int bufsize);
	int GetIWTH(const char *sWTH);
	void GetWTH(int iwth, const char *custno, const char *seatno, char *sWTH);
	char * GetOperator();
	int RestoreCJ(char *emsg);
	int UpdateClOrdID(const char *sWTH, const char *sClOrdID);
	int EndOfDay(const char *sLocalID, const char *sPartnerID,char *emsg);
	void Close();
	void Exit();
	int GetStatus(char *statusmsg,unsigned int smsize);
	bool BindCJRecv(BSHANDLE bsh);
	int GetOutMsg(char *fixmsg);
	bool IsRunning();
	char * GetMarketCode(T_UGDATA *pUGData, char *sMarketCode);
	int SendToFIXSvr(const char *fixmsg);
	int GetWTH(const char *sOrigClOrdID, char *sWTHs[], char *vsvarstrs[]);
	int GetClOrdID(const char *sWTH, char *sOrigClOrdID, char *sClOrdID);
	void RegisterWTHClOrdID(const char *sWTH, const char *sOrigClOrdID ,const char *vsvarstr1);
	int Initialize();
	int Open(const char *sLocalID, const char *sPartnerID,char *emsg);
   int CallNext(BCHANDLE bch, char *errMsg);
	int CallSvr(BCHANDLE bch, char *errMsg);
	const char * GetXPackFile();
	CKSFTS();
	virtual ~CKSFTS();

};

extern CKSFTS g_KSFTS;
//#define FIX_OPERATOR "FIXAPPSvr"  // �ڻָ��ɽ���ʱ��Ҳ��Ҫ

#endif // !defined(AFX_KSFTS_H__E5512CCC_2F28_4F4E_9621_17CC8C9ABB6C__INCLUDED_)
