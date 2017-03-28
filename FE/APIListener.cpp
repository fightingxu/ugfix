// APIListener.cpp: implementation of the CAPIListener class.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "xpub.h"
#include "APIListener.h"
#include "FIXEngine.h"
#include "ugate.h"

#include "com/mintech/utils/fmi/JNIThrowable.h"
#include "com/sungard/cs/fix/fixgateway/api/capi/CManagedAPI.h"

using com::mintech::utils::fmi::JNIThrowable;
using com::sungard::cs::fix::fixgateway::api::capi::CManagedAPI;

#include "jni.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAPIListener::CAPIListener()
{

}

CAPIListener::~CAPIListener()
{

}


void CAPIListener::handleStateChanged(const char* sessionID, int newState, int oldState, int reasonCode, const char* reasonText)
{
   newState = transState(newState);
   oldState = transState(oldState);
   g_FIXEngine.UpdateStatusChanged(sessionID,newState,oldState,reasonCode,reasonText);
}

//DEL void CAPIListener::handleMessageReceived(CMessageHandle message)
//DEL {
//DEL    std::string cs;
//DEL 	try {
//DEL #if 0
//DEL       const char *pdata = g_FIXEngine.m_vm->GetStringUTFChars((jstring)(message.getData()),false);
//DEL       string astr = pdata;
//DEL 		Environment::Utf8ToGbk(astr, cs);
//DEL #else
//DEL       cs = message.getData();
//DEL #endif
//DEL 	}
//DEL 	catch (JNIThrowable je)
//DEL 	{
//DEL 		OutErrorFile("FE_throwMsgRecv", je.getStack(), __FILE__, __LINE__);
//DEL 		return ;
//DEL 	}
//DEL 	catch (...)
//DEL 	{
//DEL 		return ;
//DEL 	}
//DEL    g_FIXEngine.FEHaveInMessage(cs.c_str());
//DEL }

void CAPIListener::handleMsgReceived(const char *msgTxt)
{
   g_FIXEngine.FEHaveInMessage(msgTxt);   
}


void CAPIListener::handleAsyncError(const char* sessionID, int errCode, const char* errTxt)
{
   UG_WriteLog(80000,"AsyncError:%s - EC(%d) %s",sessionID,errCode,errTxt);
}

int transState(int oldState)
{
	int retval;
	switch (oldState) {
	case 0: // Close
   case 3: // DISCONNECTING
		retval = 0;   
		break;
	case 1: // CONNECTING
		retval = 1;
		break;
	case 2: // OPEN
		retval = 2;
		break;
	case 4: // ERROR
   default:
		retval = -2;
		break;
	}
	return retval;
}

