/********************************************************************
	created:	2011/09/15
	created:	15:9:2011   9:46
	filename: 	C:\dd\projects\FIXIII\UGate\ugcts\DRTPData.h
	file path:	C:\dd\projects\FIXIII\UGate\ugcts
	file base:	DRTPData
	file ext:	h
	author:		CHENYH
	
	purpose:	Ϊ�˹���ͨ��ƽ̨�ڵ�Ĳ�����������״̬��
      ��Ϊ�ݴ����ã����豾�������ӵĶ��ͨ��ƽ̨������
      �����;��ȵģ���һ���ڵ��쳣�����е��Կͻ���ʽ
      ����ģ�������������һ���ڵ���棻

      �������Ϊ��
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
   int m_LastOK;  // �ϴγɹ�����BCCallRequest�Ľڵ�
   int m_AckTime; //
   
   bool m_bSvrReg; // �Ƿ��Ѿ�ע����CJSvr

public:
   int m_nDRTPs;  // ��ʵ�����õ�ͨ��ƽ̨�ڵ���
   // ����Ǳ��뽨�ģ�Ҳͬʱ���ڼ��ͨ��ƽ̨�Ƿ���������
   int  m_CJSvr[MAXDRTPNODES]; // Ϊ���ճɽ��ر�������Ϣ�����ķ�������
   int  m_bcno[MAXDRTPNODES];  // �ͻ������õĸ���DRTP�ڵ���
   int  m_CJFuncNo;

private:
   
public:
	int CallNext(BCHANDLE bch, char *errMsg);
	int TryCallSvr(BCHANDLE bch, int destno, int funcno, char *errMsg);
	bool BindBSCJRecv(BSHANDLE bsh);
	int CallSvr(BCHANDLE bch, int destno, int funcno, char *errMsg);
   // -1: �����쳣; -2: CJRecvû������1: CJRecvSvr����������0: û������
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
