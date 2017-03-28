/********************************************************************
	created:	2011/09/14
	created:	14:9:2011   21:28
	filename: 	C:\dd\projects\FIXIII\UGate\ugcts\CJThread.h
	file path:	C:\dd\projects\FIXIII\UGate\ugcts
	file base:	CJThread
	file ext:	h
	author:		CHENYH
	
	purpose:	ר���ڴ�����˴�֤ȯ����ϵͳ���͸���UGate�ĳɽ���������Ϣ����
      ����ÿ���߳�Ҳͬʱ�������ݿ���ѯ�ķ�ʽ�����֤ȯ����ϵͳ���й�FIXί��
      �򳷵��Ļر���¼��

      ����UGATE�е����ദ���������첽��Ϣ����ʽ���ڲ���ʱҲ�����ں����ݿ�
      ���������ϣ�Ӧ�ò���̫������ˣ�Ϊ�˱�̼򻯣��Ȳ��õ��̴߳���ʽ����
      
*********************************************************************/
// CJThread.h: interface for the CCJThread class.
// ����ר�Ŵ���������KSCTS�ĳɽ���Ϣ���պʹ�����
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
   int m_cjjs; // �ɽ��������
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
