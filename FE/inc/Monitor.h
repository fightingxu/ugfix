// Monitor.h: interface for the CMonitor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONITOR_H__63ED7C38_8C0D_407C_8283_0F22ABC1346B__INCLUDED_)
#define AFX_MONITOR_H__63ED7C38_8C0D_407C_8283_0F22ABC1346B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <fstream>

#include "interface_def.h"
#include "mypub.h"

class CMonitor : public IMonitor  
{
	CManagedAPI m_managedApi;
	CShrDataQueue m_dataq;
protected:
	CMonitor();
public:
	static CShrMonitor create_instance();
	virtual ~CMonitor();
		
	CManagedAPI getManagedAPI();
	void setManagedAPI(CManagedAPI CApi);
	CShrDataQueue getDataQueue();
	void setDataQueue(CShrDataQueue Dataq);

	void run();
	void NormalMonitor(std::vector<std::string> const& validSes);
	void SpecialMonitor(std::vector<std::string> const& delSes);

	int transState(int oldState);
	int checkState();
};

class Clogfile
{
	std::ofstream fout;
public:
	Clogfile() {
		fout.open("log.txt");
	}
	void write(char *msg, char *sourcefile, int lineno) {
		fout << getfmttime(NULL, 0, NULL) << '-' << msg << std::endl;
		fout.flush();
	}
};

#endif // !defined(AFX_MONITOR_H__63ED7C38_8C0D_407C_8283_0F22ABC1346B__INCLUDED_)
