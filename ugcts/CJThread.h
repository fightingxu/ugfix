/********************************************************************
	created:	2011/09/14
	created:	14:9:2011   21:28
	filename: 	C:\dd\projects\FIXIII\UGate\ugcts\CJThread.h
	file path:	C:\dd\projects\FIXIII\UGate\ugcts
	file base:	CJThread
	file ext:	h
	author:		CHENYH
	
	purpose:	专用于处理金仕达证券交易系统推送给本UGate的成交、撤单消息处理；
      另外每个线程也同时采用数据库轮询的方式，检查证券交易系统中有关FIX委托
      或撤单的回报记录。

      由于UGATE中的这类处理，都采用异步消息处理方式，内部耗时也就是在和数据库
      交换数据上，应该不会太慢，因此，为了编程简化，先采用单线程处理方式进行
      
*********************************************************************/
// CJThread.h: interface for the CCJThread class.
// 这是专门处理来自于KSCTS的成交消息接收和处理部分
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CJTHREAD_H__4341B074_54B5_4D61_98E0_34DE1F38D591__INCLUDED_)
#define AFX_CJTHREAD_H__4341B074_54B5_4D61_98E0_34DE1F38D591__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "UGDBFuncs.h"
#include <set>
#include <vector>
#include "nbccsvr.h"
#include "nbccclt.h"

typedef std::set<long> DONEID_SET;
typedef std::vector<T_REAL_DONE> V_REALDONE;

class CCJThread  
{
private:
   time_t m_lastcxlchk;
   int m_cjjs; // 成交处理计数
public:
   int m_ID;
   BSHANDLE m_bs;
   
private:
	int CheckBSData();
public:
	bool Restore(const char *partnerid, char *emsg);
	void ToStopCJProcess();
	int Run();
	bool ToStartCJProcess(char *emsg);
	void Exit();
	int Initialize(char *eMsg);
	CCJThread();
	virtual ~CCJThread();

};

#endif // !defined(AFX_CJTHREAD_H__4341B074_54B5_4D61_98E0_34DE1F38D591__INCLUDED_)
