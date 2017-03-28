///////////////////////////////////////////////////////////////////////
//This header file was generated by FMI code generator.
//FMI Version: 7.6; Build: 2
//This is the declaration of the smart pointer for class 'com.sungard.cs.fix.fixgateway.api.capi.CSessionsIDEnum



#if !defined COM_SUNGARD_CS_FIX_FIXGATEWAY_API_CAPI_CSESSIONSIDENUM_H
	#define COM_SUNGARD_CS_FIX_FIXGATEWAY_API_CAPI_CSESSIONSIDENUM_H


#include "com/sungard/cs/fix/fixgateway/api/capi/CSessionsIDEnum_stub.h"


//These incudes are needed for the methods of the Stub


using namespace com::mintech::utils::fmi;

namespace com{
	namespace sungard{
		namespace cs{
			namespace fix{
				namespace fixgateway{
					namespace api{
						namespace capi{

class CSessionsIDEnum;


class DLL_EXPORT CSessionsIDEnum : public virtual java::lang::Object
{
public:
/////////////////////
//Public Stub methods

//Public methods from java.lang.object
	string toString();

//End of methods from java.lang.Object


//CSessionsIDEnum Public methods
	bool hasMoreElements();

	/* throws java.util.NoSuchElementException */
	com::sungard::cs::fix::fixgateway::api::capi::CSessionID nextElement();

//End of CSessionsIDEnum Public methods

//End public Stub methods

public:
////////////////////////////////
//Internal Smart Pointer methods

	//Constructor / Destructor
	CSessionsIDEnum();

	//Copy constructor
	CSessionsIDEnum(const CSessionsIDEnum& copy);

	//Constructor with stub for returned objects (a new stub should return as a smart pointer)
	CSessionsIDEnum(CSessionsIDEnum_stub* stub);

	//Constructor with jobject for returned objects
	CSessionsIDEnum(jobject obj);

	//Constructor with const int for handling NULL
	CSessionsIDEnum(const int null);

	//Set the stub
	void setStub(CSessionsIDEnum_stub* stub);

	//Get the stub
	Object_interface* getStub() const;

	//operator= for two smart pointers
	CSessionsIDEnum& operator=(const CSessionsIDEnum& copy);

	//operator= for NULL
	CSessionsIDEnum& operator=(const int null);

	//operator== for two smart pointers
	bool operator==(CSessionsIDEnum& obj);

	//operator== for NULL
	bool operator==(const int null);

	//operator!= for two smart pointers
	bool operator!=(CSessionsIDEnum& obj);

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
