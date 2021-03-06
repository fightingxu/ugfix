///////////////////////////////////////////////////////////////////////
//This header file was generated by FMI code generator.
//FMI Version: 7.6; Build: 2
//This is the declaration of the smart pointer for class 'java.security.Permission



#if !defined JAVA_SECURITY_PERMISSION_H
	#define JAVA_SECURITY_PERMISSION_H


#include "java/security/Permission_stub.h"


//These incudes are needed for the methods of the Stub


using namespace com::mintech::utils::fmi;

namespace java{
	namespace security{

class Permission;


class DLL_EXPORT Permission : public virtual java::lang::Object
{
public:
/////////////////////
//Public Stub methods

//Public methods from java.lang.object
	string toString();

//End of methods from java.lang.Object


//Permission Public methods
	string getName();

	string getActions();

	bool implies(const Permission& p1);

	java::security::PermissionCollection newPermissionCollection();

	/* throws java.lang.SecurityException */
	void checkGuard(const Object& p1);

//End of Permission Public methods

//End public Stub methods

public:
////////////////////////////////
//Internal Smart Pointer methods

	//Constructor / Destructor
	Permission();

	//Copy constructor
	Permission(const Permission& copy);

	//Constructor with stub for returned objects (a new stub should return as a smart pointer)
	Permission(Permission_stub* stub);

	//Constructor with jobject for returned objects
	Permission(jobject obj);

	//Constructor with const int for handling NULL
	Permission(const int null);

	//Set the stub
	void setStub(Permission_stub* stub);

	//Get the stub
	Object_interface* getStub() const;

	//operator= for two smart pointers
	Permission& operator=(const Permission& copy);

	//operator= for NULL
	Permission& operator=(const int null);

	//operator== for two smart pointers
	bool operator==(Permission& obj);

	//operator== for NULL
	bool operator==(const int null);

	//operator!= for two smart pointers
	bool operator!=(Permission& obj);

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
