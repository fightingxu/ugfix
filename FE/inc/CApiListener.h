#include <stdlib.h>
#include "com/mintech/utils/fmi/Environment.h"
//#include "com/sungard/cs/fix/fixgateway/api/capi/CMessageHandle.h"
//using namespace com::sungard::cs::fix::fixgateway::api::capi;

class CApiListener
{
public:
	
	virtual void handleStateChanged(const char* sessionID, int newState, int oldState, int reasonCode, const char* reasonText) = 0;
	
   /****************** Updated by CYH @ 2011/09/01 *******************
	virtual void handleMessageReceived(CMessageHandle message) = 0;
   *******************************************************************/
   virtual void handleMsgReceived(const char *msgTxt) = 0;

	virtual void handleAsyncError(const char* sessionID, int errCode, const char* errTxt) = 0;

};
