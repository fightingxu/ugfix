// ***************************************************************
//  OutThread   version:  1.0   ? date: 09/14/2011
//  -------------------------------------------------------------
//  ����Ϊ������UGate����˴�֤ȯ����ϵͳ�ύ��Ϣ�õ��߳���Դ����ط���
//  -------------------------------------------------------------
//  Copyright (C) 2011 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
// OutThread.h: interface for the COutThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTTHREAD_H__1EF8CA62_7D24_4003_BF4B_BAF4266F613B__INCLUDED_)
#define AFX_OUTTHREAD_H__1EF8CA62_7D24_4003_BF4B_BAF4266F613B__INCLUDED_

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
   FIXDATAHANDLE m_fh;
   T_UGDATA m_ugdata;

public:
   int m_ID; // �̱߳��
   BCHANDLE m_bc;
   int m_omsgcnt;  // ������Ĵ�������Ա�ʾ��У�<0:��ʾֹͣ

private:
	int HandleOrderCancelRequest();
	int HandleKSCTSETFRequest(char side);
	int HandleNewOrderSingleNormal();
	int ReturnOrderReject();
	int HandleNewOrderSingle();
	int OProcess(); // ����ǰ�յ�������

	int QueryPositionStatus();
	int ReturnRequestRejected(int rejcode, char *errmsg);
	int QueryFundStatus();

public:
   // ���KSCTSӦ�÷�������״̬���Ƿ����������ṩ����

	bool Restore(const char *partnerid, char *emsg);

	void ToStopOutProcess();
	int Run();
	bool ToStartOutProcess(char *emsg);
	void Exit();
	int Initialize(int id, char *emsg);
	COutThread();
	virtual ~COutThread();

};

#endif // !defined(AFX_OUTTHREAD_H__1EF8CA62_7D24_4003_BF4B_BAF4266F613B__INCLUDED_)
