// CJThread.h: interface for the CCJThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CJTHREAD_H__E9E6B54B_0DF4_4ACA_8CCD_F09590DE3969__INCLUDED_)
#define AFX_CJTHREAD_H__E9E6B54B_0DF4_4ACA_8CCD_F09590DE3969__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "nbccsvr.h"
#include "ugate.h"

class CCJThread  
{
private:
   time_t m_lasttm;
   int m_cjjs; // 成交处理计数
public:
   BSHANDLE m_bs;
   char m_fixmsg[MAXFIXMSGLEN];
   T_UGDATA m_ugdata;
   
private:
	int F854024(char *emsg);
	int F854021(char *emsg);
   int F854020(char *emsg);
	char * GetWTH(char *sWTH);
	int ToProcessPM(char *emsg);

public:
	void ToStopCJProcess();
	bool Restore(const char *partnerid, char *emsg);
	int Run();
	bool ToStartCJProcess(char *emsg);
	void Exit();
	int Initialize(char *eMsg);
	CCJThread();
	virtual ~CCJThread();

};

#endif // !defined(AFX_CJTHREAD_H__E9E6B54B_0DF4_4ACA_8CCD_F09590DE3969__INCLUDED_)
