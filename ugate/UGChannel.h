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

class CUGChannel  // �������FIX���ԣ�����ÿ��Session�Ĺ����ˣ����Գ���ϵͳ�����Ƕ��ֵĹ���
{
private:
   // �����ÿ�ܹ���
   CMutexEvent outMsgMutexEvent;
   L_MSGDATA outMsgs[2];      // ע�⣺��Ϊ���ܹ�����Ϣ���������ȼ�:0 ���� 1

   CLuaFIX m_LuaFIX;    // 2012/5/18 22:16:03
   CMUTEX m_LuaMutex;   

public:
   char m_PartnerID[12];   // ��Channel��PartnerID
   int  m_Status;          // Ŀǰ�ĶԱ�Channel��״̬
   int  m_Load;            // Ŀǰ��Channel�ĸ���ֵ
   bool m_bStop;           // �Ƿ�ֹͣ�˳��ļ��


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
