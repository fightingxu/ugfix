///////////////////////////////////////////////////////////////////////
//This header file was generated by FMI code generator.
//FMI Version: 7.6; Build: 2
//This is the declaration of the smart pointer for class 'com.sungard.cs.fix.fixgateway.api.capi.CStatesHash



#if !defined COM_SUNGARD_CS_FIX_FIXGATEWAY_API_CAPI_CSTATESHASH_H
	#define COM_SUNGARD_CS_FIX_FIXGATEWAY_API_CAPI_CSTATESHASH_H


#include "com/sungard/cs/fix/fixgateway/api/capi/CStatesHash_stub.h"


//These incudes are needed for the methods of the Stub


using namespace com::mintech::utils::fmi;

namespace com{
	namespace sungard{
		namespace cs{
			namespace fix{
				namespace fixgateway{
					namespace api{
						namespace capi{

class CStatesHash;


class DLL_EXPORT CStatesHash : public virtual java::lang::Object
{
public:
/////////////////////
//Public Stub methods

//Public methods from java.lang.object
	string toString();

//End of methods from java.lang.Object


//CStatesHash Public methods
	jint get(const CSessionID& p1);

	com::sungard::cs::fix::fixgateway::api::capi::CSessionsIDEnum elements();

	com::sungard::cs::fix::fixgateway::api::capi::CStatesEnum keys();

//End of CStatesHash Public methods

//End public Stub methods

public:
////////////////////////////////
//Internal Smart Pointer methods

	//Constructor / Destructor
	CStatesHash();

	//Copy constructor
	CStatesHash(const CStatesHash& copy);

	//Constructor with stub for returned objects (a new stub should return as a smart pointer)
	CStatesHash(CStatesHash_stub* stub);

	//Constructor with jobject for returned objects
	CStatesHash(jobject obj);

	//Constructor with const int for handling NULL
	CStatesHash(const int null);

	//Set the stub
	void setStub(CStatesHash_stub* stub);

	//Get the stub
	Object_interface* getStub() const;

	//operator= for two smart pointers
	CStatesHash& operator=(const CStatesHash& copy);

	//operator= for NULL
	CStatesHash& operator=(const int null);

	//operator== for two smart pointers
	bool operator==(CStatesHash& obj);

	//operator== for NULL
	bool operator==(const int null);

	//operator!= for two smart pointers
	bool operator!=(CStatesHash& obj);

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
