// ***************************************************************
//  OutThread   version:  1.0   ? date: 09/14/2011
//  -------------------------------------------------------------
//  本类为管理由UGate向金仕达证券交易系统提交消息用的线程资源和相关方法
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
   // 当前正在处理中的数据
   char m_fixmsg[MAXFIXMSGLEN];
   FIXDATAHANDLE m_fh;
   T_UGDATA m_ugdata;

public:
   int m_ID; // 线程编号
   BCHANDLE m_bc;
   int m_omsgcnt;  // 启动后的处理的数以表示活动中，<0:表示停止

private:
	int HandleOrderCancelRequest();
	int HandleKSCTSETFRequest(char side);
	int HandleNewOrderSingleNormal();
	int ReturnOrderReject();
	int HandleNewOrderSingle();
	int OProcess(); // 处理当前收到的数据

	int QueryPositionStatus();
	int ReturnRequestRejected(int rejcode, char *errmsg);
	int QueryFundStatus();

public:
   // 检查KSCTS应用服务器的状态（是否正常可以提供服务）

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
