/********************************************************************
	created:	2011/08/17
	created:	17:8:2011   10:19
	filename: 	C:\dd\projects\FIXIII\UGate\ugate\UGateManage.h
	file path:	C:\dd\projects\FIXIII\UGate\ugate
	file base:	UGateManage
	file ext:	h
	author:		CHENYH
	
	purpose:	用这个类，将大部分的UGATE的属性含在里面，同时它又是接收，
   并处理来自于UDL消息的内部工作线程；
   而本线程，则是专门用于系统状态心跳信号向平台发送
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
#define RT_UGUDLCMD  411730   // IN: UGLOGIN/UGLOGOUT; return: CHANNELs OPEN/CLOSE cmd Received; 在启动的时候返回成功时候，会有一系列的Channel状态更新命令
#define RT_UPSTATUS  411731   // OUT: Channel Open/Close Command.  <LocalID>|<PartnerID>:<Status>
#define RT_CLOSEUDL  411732   // OUT: Close all Channels

#define RT_CHECKEOD  411756   // IN: Check EOD of Partner <0-UG>|<UGID>|<PARTNERID>
#define RT_CEODDONE  411757   // IN: Channel EOD Done Notification <UGID>|<PARTNERID>

#define RT_GETBSEXE  411768   // IN: Get BSExec from FS <flag>|<BuySide>...
#define RT_GETSSORD  411769   // IN: Get SSOrders from FS <flag>|<SellSide>...

#define RT_NEWORDER  411701   // IN / OUT: NewOrderSingle FIX Message
#define RT_ORDERCXL  411702   // IN / OUT: OrderCancel FIX Message
//#define RT_CXLREJECT 411703   // IN / OUT: Cancel Reject FIX Message -- 用411705了
#define RT_ORDSTREQ  411704   // IN / OUT: Order Status Request FIX Message
#define RT_EXECREP   411705   // IN / OUT: Execution Report FIX Message

#define RT_RESINMSG  411710   // IN: Restore IN-Message - 如果FS已经处理了，则不要返回和推送任何消息给UG

#define RT_OTHERBUS  411799   // IN / OUT: 一些普通查询和应答的FIX业务消息




class CUGateManage : public CWThread  
{
private:
   CSvrLink m_XPLink; // 专门用于向平台外调或推送消息用的连接，需要保护   
   CMUTEX m_XPLMutex; // 专门保护m_XPLink资源的，因为CSvrLink原来仅仅给单线程的BU使用；
   CUGChannel m_Channel[MAXCHANNELS]; // 
   
public:

   TIniFile m_inifile;  // 读取配置文件中的配置用的

   int m_UGDestNo;  // INI Load: 本UG挂接的DRTP的YYBDM or BranchNo

   int m_FSDestNo;
   int m_FSFuncNo;
   int m_FSAckTime;

   int m_UDLType; // 0 - FIXSession类；1 - 并行无恢复或局部恢复的Channel

   time_t m_lastEODTime;  // 上次EOD检查时间点

   time_t m_lastUDLTime;  // 上次UDL状态更新时间
   int m_UDLStatusRtn; // UDL状态检查返回, >=0: 正常；<0: 异常，需要重启才能恢复
   int m_UDLRefStatus;    // UDL状态更新间隔时间，用秒计

   char m_LocalID[12];
   char m_UDLStatus[4096]; // 用于记录从UDL获得的状态消息串
   char m_PartnerID[256]; // 当为多个的时候，则用 ';'分割

   int m_iDebug;  // 控制日志输出的模式: 0 - 啥都不记录；1 - 只是记录业务消息；2 - 只是记录UDL状态记录；3 - 都记录

   int m_nChannels; // 当前设置的Channel个数

   int m_OutMode;   // 0-采用UDLOnMessageOut, UDL内部管理；1-UDL调用UG_GetOutMsg/UG_HaveOutMsg

   bool m_bFilterASC;  // 在发送出去的Text-TAG58中是否过滤中文信息字符
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
   // !! 如下两个函数，专门在OUTMODE!=0的配置下，被UDL调用的，内部不用
   // 函数名: GetOutMsg
   // 编程  : 陈永华 2011-9-16 22:26:59
   // 描述  : 专门提供给UDL调用的方法，
   // 返回  : int 
   // 参数  : const char *partnerid
   // 参数  : int outwaitms
   // 参数  : char *msgbuf
	int GetOutMsg(const char *partnerid, int outwaitms, char *msgbuf);

   // 函数名: HaveOutMsg
   // 编程  : 陈永华 2011-9-16 22:27:05
   // 描述  : 
   // 返回  : int 
   // 参数  : const char *parterid
   // 参数  : const char *msg
   // 参数  : int plevel
	int HaveOutMsg(const char *parterid, const char *msg, int plevel);
   //////////////////////////////////////////////////////////////////////////

   // imode: 0 - 用推送消息411731触发EOD；1- 用应答触发EOD
   int CheckEOD(int imode, const char *partnerid);

	const char * GetPartners();
	int GetBSExecRepts(const char *BSPartnerID, L_MSGDATA &msglist);
   // 函数名: HaveMessageIn
   // 编程  : 陈永华 2011-8-20 17:32:43
   // 描述  : 向FS平台以推送方式提交消息 (多线程保护)
   // 返回  : int <0: 失败；否则成功
   // 参数  : int reqtype [IN]: 消息的功能号
   // 参数  : int pmode [IN]: 0 - 不可靠的方式提交(有可能没有能够交给平台)；1 - 可靠提交(若一切正常，则一定会提交给平台的)
   // 参数  : const char *inmsg [IN]: 需要提交的消息字符串
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
