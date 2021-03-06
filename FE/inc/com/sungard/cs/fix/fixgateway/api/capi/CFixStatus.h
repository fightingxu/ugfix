///////////////////////////////////////////////////////////////////////
//This header file was generated by FMI code generator.
//FMI Version: 7.6; Build: 2
//This is the declaration of the smart pointer for class 'com.sungard.cs.fix.fixgateway.api.capi.CFixStatus



#if !defined COM_SUNGARD_CS_FIX_FIXGATEWAY_API_CAPI_CFIXSTATUS_H
	#define COM_SUNGARD_CS_FIX_FIXGATEWAY_API_CAPI_CFIXSTATUS_H


#include "com/sungard/cs/fix/fixgateway/api/capi/CFixStatus_stub.h"


//These incudes are needed for the methods of the Stub
#include "com/mintech/utils/fmi/builtin/arrays/FObjectArray.h"


using namespace com::mintech::utils::fmi;

namespace com{
	namespace sungard{
		namespace cs{
			namespace fix{
				namespace fixgateway{
					namespace api{
						namespace capi{

class CFixStatus;


class DLL_EXPORT CFixStatus : public virtual java::lang::Object
{
public:
/////////////////////
//Public Stub methods

//Public methods from java.lang.object
	string toString();

//End of methods from java.lang.Object


//CFixStatus Public methods
	jint getFixState();

	jint getPrevFixState();

	string getMessageFormat();

	jint getExpectedInSeqNum();

	jint getExpectedOutSeqNum();

	jint getOutQueueSize();

	string getStateReasonText();

	jint getStateReasonCode();

	string getSenderCompID();

	string getTargetCompID();

	string getSessionID();

	string getCommString();

	FObjectArray getSupportedSend();

	FObjectArray getSupportedReceive();

	string getSupportedSendStr();

	string getSupportedReceiveStr();

//End of CFixStatus Public methods

//End public Stub methods

public:
////////////////////////////////
//Internal Smart Pointer methods

	//Constructor / Destructor
	CFixStatus();

	//Copy constructor
	CFixStatus(const CFixStatus& copy);

	//Constructor with stub for returned objects (a new stub should return as a smart pointer)
	CFixStatus(CFixStatus_stub* stub);

	//Constructor with jobject for returned objects
	CFixStatus(jobject obj);

	//Constructor with const int for handling NULL
	CFixStatus(const int null);

	//Set the stub
	void setStub(CFixStatus_stub* stub);

	//Get the stub
	Object_interface* getStub() const;

	//operator= for two smart pointers
	CFixStatus& operator=(const CFixStatus& copy);

	//operator= for NULL
	CFixStatus& operator=(const int null);

	//operator== for two smart pointers
	bool operator==(CFixStatus& obj);

	//operator== for NULL
	bool operator==(const int null);

	//operator!= for two smart pointers
	bool operator!=(CFixStatus& obj);

	//operator!= for NULL
	bool operator!=(const int null);

	//isInstanceOf: checks if this object is an instance of the class represented by the
	//smart pointer parameter
	bool isInstanceOf(Object& checkObj);

	//isAssignableFrom: checks if this object can be safely cast from checkObj
	static bool isAssignableFrom(const Object& checkObj);
};


}}}}}}} //Close namespace



#endif
