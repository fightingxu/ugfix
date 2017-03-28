/********************************************************************
	created:	2011/09/14
	created:	14:9:2011   22:33
	filename: 	C:\dd\projects\FIXIII\UGate\ugcts\KSCTS.h
	file path:	C:\dd\projects\FIXIII\UGate\ugcts
	file base:	KSCTS
	file ext:	h
	author:		CHENYH
	
	purpose:	����Ϊ���˴�֤ȯ����ϵͳ�ӿڵļ��ϣ�Ҳ���ڲ���Դ�ļ���
   Ϊ���ܹ�����ͼ����ؼ����ݣ��ر�ͨ��һ��ESQL������Դ
*********************************************************************/
// KSCTS.h: interface for the CKSCTS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KSCTS_H__4174D347_21EE_483D_95CA_3A149FB7B5F5__INCLUDED_)
#define AFX_KSCTS_H__4174D347_21EE_483D_95CA_3A149FB7B5F5__INCLUDED_

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
typedef map<string,string> M_CXLCLORDID; 

typedef struct _T_HWGSDM
{
   char onbehalf[21];
   char hwgsdm[21];
} T_HWGSDM;

#define MAXOUTTHREADS 20
#define MAXINTHREADS 10

class CKSCTS  
{
private:
   CMUTEX m_DBMutex;  // ר�ű������ݿ���Դʹ��

   char   m_XPackFile[256];
   bool   m_bRunning;  // �Ƿ�������״̬

   int m_XCompCnt;
   T_HWGSDM *m_pXComp;

   int m_SvrDestNo;  // KSFTS������ע���ͨ��ƽ̨�ڵ��
   int m_SvrFuncNo;  // KSFTS������ע����ͨ��ƽ̨�Ĺ��ܺ�

   long m_LastDoneID;
   time_t m_LastDoneTime;  // �ϴζ�ȡRealDone��ʱ���
   DONEID_SET m_DoneIDSet;
   int  m_DoneCnt;  // �ɽ����������

   CMUTEX m_CCMutex; // ����m_Cancels�̰߳�ȫ
   M_CXLCLORDID m_Cancels;  // ���泷����ClOrdID-OrigClOrdID�����ݶ� (δ��ɵ�)

   time_t m_LastOutTime;  // �ϴ������Out��Ϣ��ʱ���
   int  m_OutCnt;

   BCHANDLE m_bch;  // ר�ò�KSCTS�������Ŀ������

public:
   char m_LocalID[12];    // ���ӿڵı��ض�ID���������ʱ����Ҫ!
   char m_PartnerID[12];  // ���ӿڵĶ��ֶ�ID���������ʱ����Ҫ!

   int m_ReDoneIDCnt;   // �ɽ���DoneID����������¼��
   int m_CJSJRY;        // �ɽ���¼��ȡ��ʱ��������������

   char m_WTYYB[4];   // ί��Ӫҵ��
   char m_WTFSx[8];   // �ⲿί��ʱ��ί�з�ʽ��
   char m_WTFSi[2];   //  �ڲ����е�ί�з�ʽ��ENTRUST_METHOD

   CDRTPData m_DRouters; // ͨ��ƽ̨��Դ
   int m_OThreadCnt;  // ������KSCTS�ύ��������߳���
   COutThread m_OThreads[MAXOUTTHREADS];

   int m_IThreadCnt; // ����KSCTSģʽ��ʽ����ƽ̨�ύ������߳���
   CInThread m_IThreads[MAXINTHREADS];

   CCJThread m_CJThread;

   int m_Status;   // ��ǰ״̬: -1:��ͣ��0:��û��������1:���������У�2: ��KSCTS���ӳɹ������ڹ�����
private:
	bool CheckKSCTSSvr(char *emsg);
	bool PreOpen(char *emsg);
	bool CheckACancelReject(const char *origclordid, const char *clordid);
	void AddDoneProcessed(long done_id);
	bool bDoneProcessed(long done_id);
public:
	bool HaveACancelReject(const char *origclordid);
	int SendToFIXSvr(const char *fixmsg);
	int GetOutMsg(char *fixmsg);
	int TryCallSvr(BCHANDLE bch, char *errMsg);
	int CallNext(BCHANDLE bch, char *errMsg);

   // ����  : �Ա�������Reset�������֮ǰ����������ݣ�������ر�״̬
   // ����  : int <0: ʧ�ܣ����򣬳ɹ�
   // ����  : const char *sPartnerID [IN]: ָ������Session�� PartnerID
   // ����  : char *emsg [OUT]: ������ʧ�ܵ�ʱ�򣬷���ʧ����Ϣ
	int EndOfDay(const char *sLocalID, const char *sPartnerID,char *emsg);

	int GetStatus(char *statusmsg,unsigned int smsize);
	void ClOrderCxlDone(T_UGDATA *pUGData);
	void RegisterCancelOrder(const char *sOrigClOrdID, const char *sClOrdID);
	void GetCancelClOrdID(T_UGDATA *pUGData);
	int CheckCxlReject();
	bool BindCJRecv(BSHANDLE bsh);

	void HaveARealDone(T_REAL_DONE *pRealDone);

   // ������: FetchCJHBRecords
   // ���  : ������ 2011-9-20 0:27:41
   // ����  : ��֤ȯ����ϵͳ���ݿ��ж�ȡ����FIXί�����͵ĳɽ���¼�ͳ�����¼
   // ����  : int : ���ض�ȡ�ļ�¼��
	int FetchCJHBRecords();

   // ������: CKSCTS::CallSvr
   // ���  : ������ 2011-9-18 11:26:31
   // ����  : ��KSCTS���������ù���
   // ����  : int <0: ����ʧ��, �μ�errMsg�������Ϣ��-103:���ڽ���Ӧ��ʱ
   //             >=0: ���óɹ������bch�еķ�����Ϣ
   // ����  : BCHANDLE bch [IN/OUT]: ���úͷ����õ����ݻ�����
   // ����  : char *errMsg [OUT]: �ڷ���ʧ�ܵ�ʱ����д����Ĵ�����Ϣ
	int CallSvr(BCHANDLE bch, char *errMsg);

   // ������: DBGetEntrustStatus
   // ���  : ������ 2011-9-18 10:18:50
   // ����  : ��KSCTS��ENTRUST���в�ָ��ί�е����ݣ�������Ϊ1��ʱ��:
   //          sSellSide = ENTRUST.MARKET_CODE;
   //          sOrderID = ENTRUST.RPT_CONTRACT;
   //          sOrdStatus = ENTRUST.ENTRUST_STATUS;
   //          sExecInst = ENTRUST.EXCHANGE_ERR_CODE;
   //          sAccount = ENTRUST.HOLDER_ACC_NO;
   //          sClientID = ENTRUST.CUST_NO;
   // ����  : int -1: ʧ�ܣ����ݿ��쳣(Ҳ�п����ж���); 
   //             0: û���ҵ�ָ��ί�м�¼��
   //             1: �ҵ�������pUGData�е��������ݽ����޸�
   // ����  : const char *sENTRUST_METHOD [IN]: KSCTS�ڲ���ί�з�ʽ����g_KSCTS.m_WTFSiֵ
   // ����  : T_UGDATA *pUGData[IN/OUT]: ��pUGData->sOrigClOrdID��Ϊί�к�ͬ����ָ��ί�м�¼��
   //                   ������1��ʱ�򣬸������������ֶΣ�������KSCTS�ı�ʾ��ʽ
   int GetDBEntrustStatus(T_UGDATA *pUGData);

	int InsertFIXEntrust(T_UGDATA *pUGData);
	char * GetHWGSDM(const char *onbehalf);
	int LoadHWGSDM();
	void GetCurrcncy(char *fix,char *local,int iflag);  
	void Close();
	bool IsRunning();
	const char * GetXPackFile();
	int Open(const char *sLocalID, const char *sPartnerID,char *emsg);
	void Exit();
	int Initialize();
	CKSCTS();
	virtual ~CKSCTS();

};

extern CKSCTS g_KSCTS;
#define PUTLINE(msg) printf("%s @ %s-%d\n",msg,__FILE__,__LINE__)

#endif // !defined(AFX_KSCTS_H__4174D347_21EE_483D_95CA_3A149FB7B5F5__INCLUDED_)
