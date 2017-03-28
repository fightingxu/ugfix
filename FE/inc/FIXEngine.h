// FIXEngine.h: interface for the CFIXEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIXENGINE_H__4FBD124A_BBC2_4AB2_9FD2_A59B1BABFE1F__INCLUDED_)
#define AFX_FIXENGINE_H__4FBD124A_BBC2_4AB2_9FD2_A59B1BABFE1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "StdAfx_Fmi.h"
#include "com/mintech/utils/fmi/JNIException.h"
#include "com/sungard/cs/fix/fixgateway/api/capi/CFixEngineFactory.h"
#include "com/sungard/cs/fix/fixgateway/api/capi/CProperties.h"
#include "com/sungard/cs/fix/fixgateway/api/capi/CManagedAPI.h"

#include "APIListener.h"
#include "FIXSession.h"

#define MAXFIXSESSIONS 20  // 与UGateManage.h中的 MAXCHANNELS 一致

class CFIXEngine  
{
private:
   CProperties m_defaultprop;
   CManagedAPI m_managedAPI;
   CAPIListener m_apilistener;

   // 原来在m_conf中的 //////////////////////////////////////////////////////
   char jar_path[256];
   char jar_param[256];
   int  receive_mode;
   char workPath[256];  // 系统全局定义的工作日志路径
   //////////////////////////////////////////////////////////////////////////
public:
   bool m_bOutMsgLog;  // 是否记录日志 2012/6/10 20:37:16

   JNIEnv *m_vm;

   char sLocalID[12];  // UG1
   char sPartnerIDs[256];  //  ML;THOMSON;GL;BLP;BNP;BCL;SWHK;CLSA or KSCTS

   int  m_nSessions;
   CFIXSession m_Session[MAXFIXSESSIONS];

private:
	int GetFESessionStatus(CFIXSession *pSession, char *statusinfo, unsigned int sisize);
	bool ToOpenFESession(CFIXSession *pSession, char *emsg);
   void createManagedAPI(const char *config_file);

public:
	void ReflushStatus(CFIXSession *pSession);
	bool ResetFIXSessionData(const char *partnerid);
	void FEHaveInMessage(const char *fixmsg);
	void UpdateStatusChanged(const char* sessionID, int newState, int oldState, int reasonCode, const char* reasonText);
	int EndOfDay(const char *sLocalID, const char *sPartnerID,char *emsg);
	int ReadFEMsgData(const char *IN_OUT, const char *partnerid, L_MSGDATA &mlist);
	CFIXSession * FindFIXSession(const char *partnerid, const char *localid=NULL);
	int SendFIXMessage2FE(const char *fixmsg);
	int DoEOD(const char *partnerid);
	int CloseSession(const char *localid, const char *partnerid, char *emsg);
	int OpenSession(const char *localid, const char *partnerid, char *emsg);
	int GetSessionStatus(char *statusmsg,unsigned int smsize);
	void Exit();
   // 初始化 JAVA 虚拟机环境 
	bool Start();
	CFIXEngine();
	virtual ~CFIXEngine();

};

extern CFIXEngine g_FIXEngine;

#endif // !defined(AFX_FIXENGINE_H__4FBD124A_BBC2_4AB2_9FD2_A59B1BABFE1F__INCLUDED_)
