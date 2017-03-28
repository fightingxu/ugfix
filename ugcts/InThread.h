/********************************************************************
	created:	2011/09/14
	created:	14:9:2011   21:44
	filename: 	C:\dd\projects\FIXIII\UGate\ugcts\InThread.h
	file path:	C:\dd\projects\FIXIII\UGate\ugcts
	file base:	InThread
	file ext:	h
	author:		CHENYH
	
	purpose:	专门为从证券交易系统提供外盘交易的通道，目前尚无明确的需求，
      但也为金仕达证券交易系统框架下，提供KSFIX III平台支持的接入方法
*********************************************************************/
// InThread.h: interface for the CInThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTHREAD_H__F81D5F0F_0432_4251_851E_EE5948836E35__INCLUDED_)
#define AFX_INTHREAD_H__F81D5F0F_0432_4251_851E_EE5948836E35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CInThread  
{
private:
public:
   int m_ID; // 线程编号
   
private:
public:
	CInThread();
	virtual ~CInThread();

};

#endif // !defined(AFX_INTHREAD_H__F81D5F0F_0432_4251_851E_EE5948836E35__INCLUDED_)
