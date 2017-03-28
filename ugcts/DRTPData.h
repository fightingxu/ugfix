/********************************************************************
	created:	2011/09/15
	created:	15:9:2011   9:46
	filename: 	C:\dd\projects\FIXIII\UGate\ugcts\DRTPData.h
	file path:	C:\dd\projects\FIXIII\UGate\ugcts
	file base:	DRTPData
	file ext:	h
	author:		CHENYH
	
	purpose:	为了管理通信平台节点的参数和其连接状态等
      而为容错配置，假设本程序连接的多个通信平台是属于
      互备和均等的，即一个节点异常，所有的以客户方式
      处理的，都可以用另外一个节点代替；

      相关配置为：
      XPACK=cpack.dat
      DRTPNODES=1
      DRTP1=172.28.120.205:3000:100
      DRTP2=127.0.0.1:3000:100
      
        BCLOG=1  // Out BCCCLT's KLG
        BSLOG=1  // Out BCCSVR's KLG
        

*********************************************************************/
// DRTPData.h: interface for the CDRTPData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRTPDATA_H__82599C13_5444_419D_B2D5_958FCBD760DC__INCLUDED_)
#define AFX_DRTPDATA_H__82599C13_5444_419D_B2D5_958FCBD760DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "nbccclt.h"
#include "nbccsvr.h"

#define MAXDRTPNODES 10

class CDRTPData  
{
private:
   char m_DRTPPara[MAXDRTPNODES][80]; // 172.28.120.205:3000:100
   int m_LastOK;  // 上次成功调用BCCallRequest的节点
   int m_AckTime; //
   
   bool m_bSvrReg; // 是否已经注册了CJSvr

public:
   int m_nDRTPs;  // 即实际配置的通信平台节点数
   // 这个是必须建的，也同时用于检查通信平台是否连接正常
   int  m_CJSvr[MAXDRTPNODES]; // 为接收成交回报推送消息而建的服务连接
   int  m_bcno[MAXDRTPNODES];  // 客户连接用的各个DRTP节点编号
   int  m_CJFuncNo;

private:
   
public:
	int CallNext(BCHANDLE bch, char *errMsg);
	int TryCallSvr(BCHANDLE bch, int destno, int funcno, char *errMsg);
	bool BindBSCJRecv(BSHANDLE bsh);
	int CallSvr(BCHANDLE bch, int destno, int funcno, char *errMsg);
   // -1: 参数异常; -2: CJRecv没启动；1: CJRecvSvr连接正常；0: 没连接上
	int isLinkOK(int id);
	void ToStopCJRecv();
	bool ToStartCJRecv(char *errMsg);
	int GetNodeIP(int id, char *ip, unsigned int ipsize);
	int GetNodePort(int id);
	int GetNodeBranch(int id);
	int Initialize(char *errMsg);
	CDRTPData();
	virtual ~CDRTPData();

};

#endif // !defined(AFX_DRTPDATA_H__82599C13_5444_419D_B2D5_958FCBD760DC__INCLUDED_)
