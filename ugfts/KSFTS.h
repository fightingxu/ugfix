// KSFTS.h: interface for the CKSFTS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KSFTS_H__E5512CCC_2F28_4F4E_9621_17CC8C9ABB6C__INCLUDED_)
#define AFX_KSFTS_H__E5512CCC_2F28_4F4E_9621_17CC8C9ABB6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <map>
#include "CJThread.h"
#include "InThread.h"
#include "OutThread.h"
#include "DRTPData.h"
#include "mutex.h"

using namespace std;
typedef struct _T_CLORDINFO {
   char sOrigClOrdID[21];  // 原始委托号
   char sClOrdID[21];      // 撤单委托号
   char sVsvarstr1[21];    // KSFTS内部关键的下单席位号(即交易所指定的操作员号)
} T_CLORDINFO;

typedef map<string,T_CLORDINFO> M_CLORDID; // 委托号，[Orig]ClOrdID
typedef map<string,string> M_MARKET;  // FIXExchCode, FTSExchCode 对照表

#define MAXOUTTHREADS 20
#define MAXINTHREADS 10

class CKSFTS  
{
private:   
   char   m_XPackFile[256];
   bool   m_bRunning;  // 是否处于启动状态
   
   int m_SvrDestNo;
   int m_SvrFuncNo;

   time_t m_LastDoneTime;  // 上次处理回报的时间点
   int  m_DoneCnt;  // 回报处理计数器
   char   m_LastIContractNo[13]; // 上次回报处理的内部合同号 
   char   m_LastClOrdID[21];  // 上次回报处理的ClOrdID

   time_t m_LastOutTime;  // 上次最后处理Out消息的时间点
   int  m_OutCnt;
   
   BCHANDLE m_bch;  // 专用查KSFTS服务器的空闲情况
   
public:
   char m_LocalID[12];    // 本接口的本地端ID，在组包的时候需要!
   char m_PartnerID[12];  // 本接口的对手端ID，在组包的时候需要!

   //char m_WTYYB[4];   // 委托营业部
   char m_WTFSx[8];   // 外部委托时的委托方式；

   char m_Operator[24];  // FIX平台的操作员代码

   CDRTPData m_DRouters; // 通信平台资源
   int m_OThreadCnt;  // 配置向KSCTS提交请求处理的线程数
   COutThread m_OThreads[MAXOUTTHREADS];
   
   int m_IThreadCnt; // 配置KSCTS模式方式下向平台提交请求的线程数
   CInThread m_IThreads[MAXINTHREADS];
   
   CCJThread m_CJThread;
   
   int m_Status;   // 当前状态: -1:暂停；0:还没有启动；1:正在启动中；2: 与KSCTS连接成功，正在工作中

   CMUTEX m_WTHMutex;
   M_CLORDID m_WTHMap; // 委托号-ClOrdID号对照表

   M_MARKET m_Market; // 交易所代码对照表

private:
	bool CheckKSFTSSvr(char *emsg);
	bool PreOpen(char *emsg);
	int LoadMarketCode();
   
public:
	const char * GetExchange(const char *sMarketCode);
	int TryCallSvr(BCHANDLE bch, char *errMsg);
	void HaveAnOutMsg();
	char * GetSeatNoFromWTH(const char *sWTH, char *buf, unsigned int bufsize);
	char * GetCustNoFromWTH(const char *sWTH, char *buf, unsigned int bufsize);
	int GetIWTH(const char *sWTH);
	void GetWTH(int iwth, const char *custno, const char *seatno, char *sWTH);
	char * GetOperator();
	int RestoreCJ(char *emsg);
	int UpdateClOrdID(const char *sWTH, const char *sClOrdID);
	int EndOfDay(const char *sLocalID, const char *sPartnerID,char *emsg);
	void Close();
	void Exit();
	int GetStatus(char *statusmsg,unsigned int smsize);
	bool BindCJRecv(BSHANDLE bsh);
	int GetOutMsg(char *fixmsg);
	bool IsRunning();
	char * GetMarketCode(T_UGDATA *pUGData, char *sMarketCode);
	int SendToFIXSvr(const char *fixmsg);
	int GetWTH(const char *sOrigClOrdID, char *sWTHs[], char *vsvarstrs[]);
	int GetClOrdID(const char *sWTH, char *sOrigClOrdID, char *sClOrdID);
	void RegisterWTHClOrdID(const char *sWTH, const char *sOrigClOrdID ,const char *vsvarstr1);
	int Initialize();
	int Open(const char *sLocalID, const char *sPartnerID,char *emsg);
   int CallNext(BCHANDLE bch, char *errMsg);
	int CallSvr(BCHANDLE bch, char *errMsg);
	const char * GetXPackFile();
	CKSFTS();
	virtual ~CKSFTS();

};

extern CKSFTS g_KSFTS;
//#define FIX_OPERATOR "FIXAPPSvr"  // 在恢复成交的时候也需要

#endif // !defined(AFX_KSFTS_H__E5512CCC_2F28_4F4E_9621_17CC8C9ABB6C__INCLUDED_)
