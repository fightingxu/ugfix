/********************************************************************
	created:	2011/09/14
	created:	14:9:2011   22:33
	filename: 	C:\dd\projects\FIXIII\UGate\ugcts\KSCTS.h
	file path:	C:\dd\projects\FIXIII\UGate\ugcts
	file base:	KSCTS
	file ext:	h
	author:		CHENYH
	
	purpose:	本类为金仕达证券交易系统接口的集合，也是内部资源的集合
   为了能够保存和检索关键数据，特别通过一个ESQL数据资源
*********************************************************************/
// KSCTS.h: interface for the CKSCTS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KSCTS_H__4174D347_21EE_483D_95CA_3A149FB7B5F5__INCLUDED_)
#define AFX_KSCTS_H__4174D347_21EE_483D_95CA_3A149FB7B5F5__INCLUDED_

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
typedef map<string,string> M_CXLCLORDID; 

typedef struct _T_HWGSDM
{
   char onbehalf[21];
   char hwgsdm[21];
} T_HWGSDM;

#define MAXOUTTHREADS 20
#define MAXINTHREADS 10

class CKSCTS  
{
private:
   CMUTEX m_DBMutex;  // 专门保护数据库资源使用

   char   m_XPackFile[256];
   bool   m_bRunning;  // 是否处于启动状态

   int m_XCompCnt;
   T_HWGSDM *m_pXComp;

   int m_SvrDestNo;  // KSFTS服务器注册的通信平台节点号
   int m_SvrFuncNo;  // KSFTS服务器注册在通信平台的功能号

   long m_LastDoneID;
   time_t m_LastDoneTime;  // 上次读取RealDone的时间点
   DONEID_SET m_DoneIDSet;
   int  m_DoneCnt;  // 成交处理计数器

   CMUTEX m_CCMutex; // 保护m_Cancels线程安全
   M_CXLCLORDID m_Cancels;  // 保存撤单的ClOrdID-OrigClOrdID的数据对 (未完成的)

   time_t m_LastOutTime;  // 上次最后处理Out消息的时间点
   int  m_OutCnt;

   BCHANDLE m_bch;  // 专用查KSCTS服务器的空闲情况

public:
   char m_LocalID[12];    // 本接口的本地端ID，在组包的时候需要!
   char m_PartnerID[12];  // 本接口的对手端ID，在组包的时候需要!

   int m_ReDoneIDCnt;   // 成交的DoneID的冗余最大记录数
   int m_CJSJRY;        // 成交记录读取的时间回退数，毫秒计

   char m_WTYYB[4];   // 委托营业部
   char m_WTFSx[8];   // 外部委托时的委托方式；
   char m_WTFSi[2];   //  内部表中的委托方式；ENTRUST_METHOD

   CDRTPData m_DRouters; // 通信平台资源
   int m_OThreadCnt;  // 配置向KSCTS提交请求处理的线程数
   COutThread m_OThreads[MAXOUTTHREADS];

   int m_IThreadCnt; // 配置KSCTS模式方式下向平台提交请求的线程数
   CInThread m_IThreads[MAXINTHREADS];

   CCJThread m_CJThread;

   int m_Status;   // 当前状态: -1:暂停；0:还没有启动；1:正在启动中；2: 与KSCTS连接成功，正在工作中
private:
	bool CheckKSCTSSvr(char *emsg);
	bool PreOpen(char *emsg);
	bool CheckACancelReject(const char *origclordid, const char *clordid);
	void AddDoneProcessed(long done_id);
	bool bDoneProcessed(long done_id);
public:
	bool HaveACancelReject(const char *origclordid);
	int SendToFIXSvr(const char *fixmsg);
	int GetOutMsg(char *fixmsg);
	int TryCallSvr(BCHANDLE bch, char *errMsg);
	int CallNext(BCHANDLE bch, char *errMsg);

   // 描述  : 对本连接做Reset处理，清除之前处理缓存的数据，并进入关闭状态
   // 返回  : int <0: 失败；否则，成功
   // 参数  : const char *sPartnerID [IN]: 指定操作Session的 PartnerID
   // 参数  : char *emsg [OUT]: 当返回失败的时候，返回失败信息
	int EndOfDay(const char *sLocalID, const char *sPartnerID,char *emsg);

	int GetStatus(char *statusmsg,unsigned int smsize);
	void ClOrderCxlDone(T_UGDATA *pUGData);
	void RegisterCancelOrder(const char *sOrigClOrdID, const char *sClOrdID);
	void GetCancelClOrdID(T_UGDATA *pUGData);
	int CheckCxlReject();
	bool BindCJRecv(BSHANDLE bsh);

	void HaveARealDone(T_REAL_DONE *pRealDone);

   // 函数名: FetchCJHBRecords
   // 编程  : 陈永华 2011-9-20 0:27:41
   // 描述  : 从证券交易系统数据库中读取属于FIX委托类型的成交记录和撤单记录
   // 返回  : int : 返回读取的记录数
	int FetchCJHBRecords();

   // 函数名: CKSCTS::CallSvr
   // 编程  : 陈永华 2011-9-18 11:26:31
   // 描述  : 向KSCTS服务器调用功能
   // 返回  : int <0: 调用失败, 参见errMsg的输出信息；-103:属于接收应答超时
   //             >=0: 调用成功，检查bch中的返回信息
   // 参数  : BCHANDLE bch [IN/OUT]: 调用和返回用的数据缓存句柄
   // 参数  : char *errMsg [OUT]: 在返回失败的时候，填写具体的错误信息
	int CallSvr(BCHANDLE bch, char *errMsg);

   // 函数名: DBGetEntrustStatus
   // 编程  : 陈永华 2011-9-18 10:18:50
   // 描述  : 从KSCTS的ENTRUST表中查指定委托的数据，当返回为1的时候:
   //          sSellSide = ENTRUST.MARKET_CODE;
   //          sOrderID = ENTRUST.RPT_CONTRACT;
   //          sOrdStatus = ENTRUST.ENTRUST_STATUS;
   //          sExecInst = ENTRUST.EXCHANGE_ERR_CODE;
   //          sAccount = ENTRUST.HOLDER_ACC_NO;
   //          sClientID = ENTRUST.CUST_NO;
   // 返回  : int -1: 失败，数据库异常(也有可能有多条); 
   //             0: 没有找到指定委托记录；
   //             1: 找到，并对pUGData中的上述数据进行修改
   // 参数  : const char *sENTRUST_METHOD [IN]: KSCTS内部的委托方式，即g_KSCTS.m_WTFSi值
   // 参数  : T_UGDATA *pUGData[IN/OUT]: 用pUGData->sOrigClOrdID作为委托合同号来指定委托记录；
   //                   当返回1的时候，更改上述几个字段，但采用KSCTS的表示方式
   int GetDBEntrustStatus(T_UGDATA *pUGData);

	int InsertFIXEntrust(T_UGDATA *pUGData);
	char * GetHWGSDM(const char *onbehalf);
	int LoadHWGSDM();
	void GetCurrcncy(char *fix,char *local,int iflag);  
	void Close();
	bool IsRunning();
	const char * GetXPackFile();
	int Open(const char *sLocalID, const char *sPartnerID,char *emsg);
	void Exit();
	int Initialize();
	CKSCTS();
	virtual ~CKSCTS();

};

extern CKSCTS g_KSCTS;
#define PUTLINE(msg) printf("%s @ %s-%d\n",msg,__FILE__,__LINE__)

#endif // !defined(AFX_KSCTS_H__4174D347_21EE_483D_95CA_3A149FB7B5F5__INCLUDED_)
