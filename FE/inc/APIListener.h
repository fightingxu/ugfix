// APIListener.h: interface for the CAPIListener class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APILISTENER_H__C8FAF8B0_530E_454D_A768_10CF75646038__INCLUDED_)
#define AFX_APILISTENER_H__C8FAF8B0_530E_454D_A768_10CF75646038__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CApiListener.h"

class CAPIListener : public CApiListener  
{
public:
	void handleMsgReceived(const char *msgTxt);
   CAPIListener();
	virtual ~CAPIListener();

	void handleStateChanged(const char* sessionID, int newState, int oldState, int reasonCode, const char* reasonText);
	void handleAsyncError(const char* sessionID, int errCode, const char* errTxt);
};


int transState(int oldState);

#endif // !defined(AFX_APILISTENER_H__C8FAF8B0_530E_454D_A768_10CF75646038__INCLUDED_)
