///////////////////////////////////////////////////////////////////////
//This header file was generated by FMI code generator.
//FMI Version: 7.6; Build: 2
//This is the declaration of the smart pointer for class 'java.security.ProtectionDomain



#if !defined JAVA_SECURITY_PROTECTIONDOMAIN_H
	#define JAVA_SECURITY_PROTECTIONDOMAIN_H


#include "java/security/ProtectionDomain_stub.h"


//These incudes are needed for the methods of the Stub
#include "com/mintech/utils/fmi/builtin/arrays/FObjectArray.h"


using namespace com::mintech::utils::fmi;

namespace java{
	namespace security{

class ProtectionDomain;


class DLL_EXPORT ProtectionDomain : public virtual java::lang::Object
{
public:
/////////////////////
//Public Stub methods

//Public methods from java.lang.object
	string toString();

//End of methods from java.lang.Object


//ProtectionDomain Public methods
	java::lang::ClassLoader getClassLoader();

	java::security::CodeSource getCodeSource();

	java::security::PermissionCollection getPermissions();

	FObjectArray getPrincipals();

	bool implies(const Permission& p1);

//End of ProtectionDomain Public methods

//End public Stub methods

public:
////////////////////////////////
//Internal Smart Pointer methods

	//Constructor / Destructor
	ProtectionDomain();

	//Copy constructor
	ProtectionDomain(const ProtectionDomain& copy);

	//Constructor with stub for returned objects (a new stub should return as a smart pointer)
	ProtectionDomain(ProtectionDomain_stub* stub);

	//Constructor with jobject for returned objects
	ProtectionDomain(jobject obj);

	//Constructor with const int for handling NULL
	ProtectionDomain(const int null);

	//Set the stub
	void setStub(ProtectionDomain_stub* stub);

	//Get the stub
	Object_interface* getStub() const;

	//operator= for two smart pointers
	ProtectionDomain& operator=(const ProtectionDomain& copy);

	//operator= for NULL
	ProtectionDomain& operator=(const int null);

	//operator== for two smart pointers
	bool operator==(ProtectionDomain& obj);

	//operator== for NULL
	bool operator==(const int null);

	//operator!= for two smart pointers
	bool operator!=(ProtectionDomain& obj);

	//operator!= for NULL
	bool operator!=(const int null);

	//isInstanceOf: checks if this object is an instance of the class represented by the
	//smart pointer parameter
	bool isInstanceOf(Object& checkObj);

	//isAssignableFrom: checks if this object can be safely cast from checkObj
	static bool isAssignableFrom(const Object& checkObj);
};


}} //Close namespace



#endif
