///////////////////////////////////////////////////////////////////////
//This header file was generated by FMI code generator.
//FMI Version: 7.6; Build: 2
//This is the declaration of the smart pointer for class 'com.sungard.cs.fix.fixgateway.api.capi.CManagedAPI



#if !defined COM_SUNGARD_CS_FIX_FIXGATEWAY_API_CAPI_CMANAGEDAPI_H
	#define COM_SUNGARD_CS_FIX_FIXGATEWAY_API_CAPI_CMANAGEDAPI_H


#include "com/sungard/cs/fix/fixgateway/api/capi/CManagedAPI_stub.h"


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

class CManagedAPI;


class DLL_EXPORT CManagedAPI : public virtual java::lang::Object
{
public:
/////////////////////
//Public Stub methods

//Public methods from java.lang.object
	string toString();

//End of methods from java.lang.Object


//CManagedAPI Public methods
	jint getState();

	/* throws com.sungard.cs.fix.fixgateway.api.FIXException */
	void close();

	/* throws com.sungard.cs.fix.fixgateway.api.FIXException */
	void open();

	com::sungard::cs::fix::fixgateway::api::capi::CProperties getParameters();

	void newAPI(com::sungard::cs::fix::fixgateway::api::capi::CProperties p1);

	/* throws com.sungard.cs.fix.fixgateway.api.FIXException */
	void attach(const CFixListenerRef& p1);

	/* throws com.sungard.cs.fix.fixgateway.api.FIXException */
	void detach(const CFixListenerRef& p1);

	/* throws com.sungard.cs.fix.fixgateway.api.FIXException */
	void controlCommand(const string& p1);

	/* throws com.sungard.cs.fix.fixgateway.api.FIXException */
	void sendMessage(const string& p1);

	/* throws com.sungard.cs.fix.fixgateway.api.FIXException */
	com::sungard::cs::fix::fixgateway::api::capi::CFixStatus getStatus(const string& p1);

	/* throws com.sungard.cs.fix.fixgateway.api.FIXException */
	com::sungard::cs::fix::fixgateway::api::capi::CFixStatus getStatus();

	/* throws com.sungard.cs.fix.fixgateway.api.FIXException */
	com::sungard::cs::fix::fixgateway::api::capi::CMessageHandle getRejectedMessage(const string& p1);

	/* throws com.sungard.cs.fix.fixgateway.api.FIXException */
	com::sungard::cs::fix::fixgateway::api::capi::CMessageHandle getRejectedMessage(const CMessageHandle& p1);

	/* throws com.sungard.cs.fix.fixgateway.api.FIXException */
	void putLogLine(const string& p1, const jint p2);

	/* throws com.sungard.cs.fix.fixgateway.api.FIXException */
	com::sungard::cs::fix::fixgateway::api::capi::CStatesHash getStates();

	/* throws com.sungard.cs.fix.fixgateway.api.FIXException */
	void resendMessage(const string& p1);

	/* throws com.sungard.cs.fix.fixgateway.api.FIXException */
	void restoreIncomingMessages(const string& p1, const jlong p2, const jint p3, const jint p4, const jboolean p5);

	/* throws com.sungard.cs.fix.fixgateway.api.FIXException */
	void restoreIncomingMessages(const jlong p1, const jlong p2, const jint p3, const jboolean p4);

	/* throws com.sungard.cs.fix.fixgateway.api.FIXException */
	com::sungard::cs::fix::fixgateway::api::capi::CMessageEnum getIncomingMessages(const string& p1, const jlong p2, const jint p3, const jint p4);

	/* throws com.sungard.cs.fix.fixgateway.api.FIXException */
	com::sungard::cs::fix::fixgateway::api::capi::CMessageEnum getIncomingMessages(const jlong p1, const jlong p2, const jint p3);

	jlong millisToKey(const jlong p1);

	void startDispatcher();

	void stopDispatcher();

	void startRealtimeDispatcher();

	void stopRealtimeDispatcher();

	/* throws com.sungard.cs.fix.fixgateway.api.FIXException */
	com::sungard::cs::fix::fixgateway::api::capi::CMessageHandle receiveMessage();

	/* throws com.sungard.cs.fix.fixgateway.api.FIXException */
	void advanceMessage();

	com::sungard::cs::fix::fixgateway::api::capi::CLogFactory getLogFactory();

	static 	string get_reasonDescr(const jint p1);

	static 	string get_appStateDescr(const jint p1);

	static 	string get_stateDescr(const jint p1);

//End of CManagedAPI Public methods

//Public data members methods
	//Public data members retrieval methods
	//'final' fields
	static jint get_CLOSED();

	static jint get_CONNECTING();

	static jint get_OPEN();

	static jint get_DISCONNECTING();

	static jint get_ERROR();

	static FObjectArray get_stateDescr();

	static jint get_OFF_THE_SHELF_APPLICATION_STOPPED();

	static jint get_OFF_THE_SHELF_APPLICATION_STARTED();

	static FObjectArray get_appStateDescr();

	static jint get_API_REQUEST();

	static jint get_PARTNER_REQUEST();

	static jint get_ENCRYPTION_PROBLEM();

	static jint get_CONNECTION_REFUSED();

	static jint get_PARTNER_REJECT();

	static jint get_SEQUENCE_NUMBER();

	static jint get_COMM_PROBLEM();

	static jint get_IN_SYNC();

	static jint get_DATA_PROB();

	static FObjectArray get_reasonDescr();

	//Public data members set methods
//End public data members methods
//End public Stub methods

public:
////////////////////////////////
//Internal Smart Pointer methods

	//Constructor / Destructor
	CManagedAPI();

	//Copy constructor
	CManagedAPI(const CManagedAPI& copy);

	//Constructor with stub for returned objects (a new stub should return as a smart pointer)
	CManagedAPI(CManagedAPI_stub* stub);

	//Constructor with jobject for returned objects
	CManagedAPI(jobject obj);

	//Constructor with const int for handling NULL
	CManagedAPI(const int null);

	//Set the stub
	void setStub(CManagedAPI_stub* stub);

	//Get the stub
	Object_interface* getStub() const;

	//operator= for two smart pointers
	CManagedAPI& operator=(const CManagedAPI& copy);

	//operator= for NULL
	CManagedAPI& operator=(const int null);

	//operator== for two smart pointers
	bool operator==(CManagedAPI& obj);

	//operator== for NULL
	bool operator==(const int null);

	//operator!= for two smart pointers
	bool operator!=(CManagedAPI& obj);

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
