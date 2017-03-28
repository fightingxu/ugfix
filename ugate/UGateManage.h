/********************************************************************
	created:	2011/08/17
	created:	17:8:2011   10:19
	filename: 	C:\dd\projects\FIXIII\UGate\ugate\UGateManage.h
	file path:	C:\dd\projects\FIXIII\UGate\ugate
	file base:	UGateManage
	file ext:	h
	author:		CHENYH
	
	purpose:	������࣬���󲿷ֵ�UGATE�����Ժ������棬ͬʱ�����ǽ��գ�
   ������������UDL��Ϣ���ڲ������̣߳�
   �����̣߳�����ר������ϵͳ״̬�����ź���ƽ̨����
*********************************************************************/
// UGateManage.h: interface for the CUGateManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGATEMANAGE_H__791816BD_1ACA_45EE_9C9D_F859DE9544C6__INCLUDED_)
#define AFX_UGATEMANAGE_H__791816BD_1ACA_45EE_9C9D_F859DE9544C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "mutex.h"
#include "WThread.h"
#include "svrlink.h"
#include "profile.h"
#include "UGChannel.h"
#include "MsgDataList.h"

#define MAXCHANNELS 20

// IN: UG->FS; OUT: FS->UG(->UDL->Partner)
#define RT_UGUDLCMD  411730   // IN: UGLOGIN/UGLOGOUT; return: CHANNELs OPEN/CLOSE cmd Received; ��������ʱ�򷵻سɹ�ʱ�򣬻���һϵ�е�Channel״̬��������
#define RT_UPSTATUS  411731   // OUT: Channel Open/Close Command.  <LocalID>|<PartnerID>:<Status>
#define RT_CLOSEUDL  411732   // OUT: Close all Channels

#define RT_CHECKEOD  411756   // IN: Check EOD of Partner <0-UG>|<UGID>|<PARTNERID>
#define RT_CEODDONE  411757   // IN: Channel EOD Done Notification <UGID>|<PARTNERID>

#define RT_GETBSEXE  411768   // IN: Get BSExec from FS <flag>|<BuySide>...
#define RT_GETSSORD  411769   // IN: Get SSOrders from FS <flag>|<SellSide>...

#define RT_NEWORDER  411701   // IN / OUT: NewOrderSingle FIX Message
#define RT_ORDERCXL  411702   // IN / OUT: OrderCancel FIX Message
//#define RT_CXLREJECT 411703   // IN / OUT: Cancel Reject FIX Message -- ��411705��
#define RT_ORDSTREQ  411704   // IN / OUT: Order Status Request FIX Message
#define RT_EXECREP   411705   // IN / OUT: Execution Report FIX Message

#define RT_RESINMSG  411710   // IN: Restore IN-Message - ���FS�Ѿ������ˣ���Ҫ���غ������κ���Ϣ��UG

#define RT_OTHERBUS  411799   // IN / OUT: һЩ��ͨ��ѯ��Ӧ���FIXҵ����Ϣ




class CUGateManage : public CWThread  
{
private:
   CSvrLink m_XPLink; // ר��������ƽ̨�����������Ϣ�õ����ӣ���Ҫ����   
   CMUTEX m_XPLMutex; // ר�ű���m_XPLink��Դ�ģ���ΪCSvrLinkԭ�����������̵߳�BUʹ�ã�
   CUGChannel m_Channel[MAXCHANNELS]; // 
   
public:

   TIniFile m_inifile;  // ��ȡ�����ļ��е������õ�

   int m_UGDestNo;  // INI Load: ��UG�ҽӵ�DRTP��YYBDM or BranchNo

   int m_FSDestNo;
   int m_FSFuncNo;
   int m_FSAckTime;

   int m_UDLType; // 0 - FIXSession�ࣻ1 - �����޻ָ���ֲ��ָ���Channel

   time_t m_lastEODTime;  // �ϴ�EOD���ʱ���

   time_t m_lastUDLTime;  // �ϴ�UDL״̬����ʱ��
   int m_UDLStatusRtn; // UDL״̬��鷵��, >=0: ������<0: �쳣����Ҫ�������ָܻ�
   int m_UDLRefStatus;    // UDL״̬���¼��ʱ�䣬�����

   char m_LocalID[12];
   char m_UDLStatus[4096]; // ���ڼ�¼��UDL��õ�״̬��Ϣ��
   char m_PartnerID[256]; // ��Ϊ�����ʱ������ ';'�ָ�

   int m_iDebug;  // ������־�����ģʽ: 0 - ɶ������¼��1 - ֻ�Ǽ�¼ҵ����Ϣ��2 - ֻ�Ǽ�¼UDL״̬��¼��3 - ����¼

   int m_nChannels; // ��ǰ���õ�Channel����

   int m_OutMode;   // 0-����UDLOnMessageOut, UDL�ڲ�����1-UDL����UG_GetOutMsg/UG_HaveOutMsg

   bool m_bFilterASC;  // �ڷ��ͳ�ȥ��Text-TAG58���Ƿ����������Ϣ�ַ�
private:
	int FormatInMsg(char *inmsg, int imlen);
	int CheckEOD_AllChannel();
	void HandleOutFIXMessage(const char *fixmsg, const char *partnerid=NULL);
	void HandleChannelStatus(const char *cmd);
	int InChannelStatus(char *instatus);
	int CheckUDLStatus();
	void ToLogout();
	bool CheckUGParameter();
	int Run();
   int EODDone(const char *partnerid);
   

public:
	int HaveMessageIn(int reqtype, int pmode, CFIXData *pfixdata);
	void ReloadKFXFile(int iChannel);
	bool GetChannelInfo(int iChannel, char *info256);
	int GetSSOrders(int flag,const char *sSSPartnerID, L_MSGDATA &msglist);
	int GetOutMsgSize(const char *partnerid);
	void ToSetOutMode(int outmode);

   //////////////////////////////////////////////////////////////////////////
   // !! ��������������ר����OUTMODE!=0�������£���UDL���õģ��ڲ�����
   // ������: GetOutMsg
   // ���  : ������ 2011-9-16 22:26:59
   // ����  : ר���ṩ��UDL���õķ�����
   // ����  : int 
   // ����  : const char *partnerid
   // ����  : int outwaitms
   // ����  : char *msgbuf
	int GetOutMsg(const char *partnerid, int outwaitms, char *msgbuf);

   // ������: HaveOutMsg
   // ���  : ������ 2011-9-16 22:27:05
   // ����  : 
   // ����  : int 
   // ����  : const char *parterid
   // ����  : const char *msg
   // ����  : int plevel
	int HaveOutMsg(const char *parterid, const char *msg, int plevel);
   //////////////////////////////////////////////////////////////////////////

   // imode: 0 - ��������Ϣ411731����EOD��1- ��Ӧ�𴥷�EOD
   int CheckEOD(int imode, const char *partnerid);

	const char * GetPartners();
	int GetBSExecRepts(const char *BSPartnerID, L_MSGDATA &msglist);
   // ������: HaveMessageIn
   // ���  : ������ 2011-8-20 17:32:43
   // ����  : ��FSƽ̨�����ͷ�ʽ�ύ��Ϣ (���̱߳���)
   // ����  : int <0: ʧ�ܣ�����ɹ�
   // ����  : int reqtype [IN]: ��Ϣ�Ĺ��ܺ�
   // ����  : int pmode [IN]: 0 - ���ɿ��ķ�ʽ�ύ(�п���û���ܹ�����ƽ̨)��1 - �ɿ��ύ(��һ����������һ�����ύ��ƽ̨��)
   // ����  : const char *inmsg [IN]: ��Ҫ�ύ����Ϣ�ַ���
	int HaveMessageIn(int reqtype,int pmode,const char *inmsg);

	int Processing();
	CUGChannel * FindChannel(const char *sPartnerID);
	void ToExit();
	int Initialize();
	int xProcess(TRUSERID *handle,char *rdata,int rdlen,int *iRetCode, char *szMsg);
	int LoadIni(const char *inifile);
	CUGateManage();
	virtual ~CUGateManage();

};

extern CUGateManage g_UGate;

#endif // !defined(AFX_UGATEMANAGE_H__791816BD_1ACA_45EE_9C9D_F859DE9544C6__INCLUDED_)
