// OutThread.h: interface for the COutThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTTHREAD_H__766197DB_F79A_459C_BEEF_A45774D86895__INCLUDED_)
#define AFX_OUTTHREAD_H__766197DB_F79A_459C_BEEF_A45774D86895__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "fixbase.h"
#include "ugate.h"
#include "nbccclt.h"

class COutThread  
{
private:
   // ��ǰ���ڴ����е�����
   char m_fixmsg[MAXFIXMSGLEN];
   FIXDATAHANDLE m_fh;  // ��ҪΪ����Щ��T_UGDATA��û�а�������չ�����ݶ�ȡ��
   T_UGDATA m_ugdata;
   char m_WTZT[2];   // ��KSFTS�е�ί��״̬����һ�ֶ���ί���У����������ַ��ֱ��ʾ��һ�ʺ͵ڶ���
   char m_sWTH[2][40];  // ������ <ί�к�lserial0>+|+<�ͻ���sholder_ac_no>+|+<ϯλ��sserial2>��ϵ��ڲ���ʶ
   char m_vsvarstr1[2][24];  // ����ν�� �µ�ϯλ ��������ָ���ı��̲���Ա��
   int  m_OrderQty[2];
   int  m_CumQty[2];
   double m_AvxPx[2];
   
public:
   int m_ID; // �̱߳��
   BCHANDLE m_bc;
   int m_omsgcnt;  // ������Ĵ�������Ա�ʾ��У�<0:��ʾֹͣ
   
private:
	int QueryPositionStatus();
	int ReturnRequestRejected(int rejcode, char *errmsg);
	int QueryFundStatus();
	int GetAllWTH(const char *sOrigClOrdID);
	int MayToBeCanceled(int iwt);
	int ReturnCancelRejected();
   
   int CancelAnOrder(int iwt,char *fvalue256);  // �Ե�һ��ί�н��г�������

	int QueryLimitPrice(T_UGDATA *pUGData, char *sFTSMarketCode);
	int ReturnOrderReject();
	char * GetClientNo(const char *sClientID, char *sClientNo);  // ȡFTSҪ��Ŀͻ���
	int QueryFTSOrders(T_UGDATA *pUGData);
	int HandleOrderCancelRequest();
	int HandleNewOrderSingle();
	int OProcess();

public:
	bool Restore(const char *partnerid, char *emsg);
	void ToStopOutProcess();
	bool ToStartOutProcess(char *emsg);
	int Run();
	void Exit();
	int Initialize(int id, char *emsg);
	COutThread();
	virtual ~COutThread();

};

#endif // !defined(AFX_OUTTHREAD_H__766197DB_F79A_459C_BEEF_A45774D86895__INCLUDED_)
