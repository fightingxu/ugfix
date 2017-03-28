// UGChannel.h: interface for the CUGChannel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGCHANNEL_H__2FF9D82A_4D5B_4699_9CA3_DBFF71F3A279__INCLUDED_)
#define AFX_UGCHANNEL_H__2FF9D82A_4D5B_4699_9CA3_DBFF71F3A279__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "mutex.h"
#include "MsgDataList.h"
#include "LuaFIX.h"

class CUGChannel  // 这里相对FIX而言，就是每个Session的管理了；而对常规系统，就是对手的管理
{
private:
   // 当采用框架管理
   CMutexEvent outMsgMutexEvent;
   L_MSGDATA outMsgs[2];      // 注意：这为了能够将消息分两级优先级:0 高于 1

   CLuaFIX m_LuaFIX;    // 2012/5/18 22:16:03
   CMUTEX m_LuaMutex;   

public:
   char m_PartnerID[12];   // 本Channel的PartnerID
   int  m_Status;          // 目前的对本Channel的状态
   int  m_Load;            // 目前本Channel的负载值
   bool m_bStop;           // 是否停止退出的检查


private:

public:
	void CloseLuaFile();
	bool LoadLuaFile();
	void FormatOutFIXData(CFIXData *pfixdata);
	void FormatInFIXData(CFIXData *pfixdata);
	int GetOutMsgSize();
	int GetOutMsg(int outwaitms, char *msgbuf);
	void HaveOutMsg(int msglen, const char *msg, int &plevel);
	void UpdateStatus(int status);
	void ChannelStatus(int status, int load, const char *eMsg);
	int CloseChannel();
	int OpenChannel();
	CUGChannel();
	virtual ~CUGChannel();

};

#endif // !defined(AFX_UGCHANNEL_H__2FF9D82A_4D5B_4699_9CA3_DBFF71F3A279__INCLUDED_)
