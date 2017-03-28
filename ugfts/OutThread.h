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
   // 当前正在处理中的数据
   char m_fixmsg[MAXFIXMSGLEN];
   FIXDATAHANDLE m_fh;  // 主要为了那些在T_UGDATA中没有包含的扩展域数据读取用
   T_UGDATA m_ugdata;
   char m_WTZT[2];   // 在KSFTS中的委托状态，在一分二的委托中，则用两个字符分别表示第一笔和第二笔
   char m_sWTH[2][40];  // 两笔用 <委托号lserial0>+|+<客户号sholder_ac_no>+|+<席位号sserial2>组合的内部标识
   char m_vsvarstr1[2][24];  // 即所谓的 下单席位 （交易所指定的报盘操作员）
   int  m_OrderQty[2];
   int  m_CumQty[2];
   double m_AvxPx[2];
   
public:
   int m_ID; // 线程编号
   BCHANDLE m_bc;
   int m_omsgcnt;  // 启动后的处理的数以表示活动中，<0:表示停止
   
private:
	int QueryPositionStatus();
	int ReturnRequestRejected(int rejcode, char *errmsg);
	int QueryFundStatus();
	int GetAllWTH(const char *sOrigClOrdID);
	int MayToBeCanceled(int iwt);
	int ReturnCancelRejected();
   
   int CancelAnOrder(int iwt,char *fvalue256);  // 对单一个委托进行撤单请求

	int QueryLimitPrice(T_UGDATA *pUGData, char *sFTSMarketCode);
	int ReturnOrderReject();
	char * GetClientNo(const char *sClientID, char *sClientNo);  // 取FTS要求的客户号
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
