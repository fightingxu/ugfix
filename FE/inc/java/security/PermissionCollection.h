///////////////////////////////////////////////////////////////////////
//This header file was generated by FMI code generator.
//FMI Version: 7.6; Build: 2
//This is the declaration of the smart pointer for class 'java.security.PermissionCollection



#if !defined JAVA_SECURITY_PERMISSIONCOLLECTION_H
	#define JAVA_SECURITY_PERMISSIONCOLLECTION_H


#include "java/security/PermissionCollection_stub.h"


//These incudes are needed for the methods of the Stub


using namespace com::mintech::utils::fmi;

namespace java{
	namespace security{

class PermissionCollection;


class DLL_EXPORT PermissionCollection : public virtual java::lang::Object
{
public:
/////////////////////
//Public Stub methods

//Public methods from java.lang.object
	string toString();

//End of methods from java.lang.Object


//PermissionCollection Public methods
	void add(const Permission& p1);

	java::util::Enumeration elements();

	bool implies(const Permission& p1);

	void setReadOnly();

	bool isReadOnly();

//End of PermissionCollection Public methods

//End public Stub methods

public:
////////////////////////////////
//Internal Smart Pointer methods

	//Constructor / Destructor
	PermissionCollection();

	//Copy constructor
	PermissionCollection(const PermissionCollection& copy);

	//Constructor with stub for returned objects (a new stub should return as a smart pointer)
	PermissionCollection(PermissionCollection_stub* stub);

	//Constructor with jobject for returned objects
	PermissionCollection(jobject obj);

	//Constructor with const int for handling NULL
	PermissionCollection(const int null);

	//Set the stub
	void setStub(PermissionCollection_stub* stub);

	//Get the stub
	Object_interface* getStub() const;

	//operator= for two smart pointers
	PermissionCollection& operator=(const PermissionCollection& copy);

	//operator= for NULL
	PermissionCollection& operator=(const int null);

	//operator== for two smart pointers
	bool operator==(PermissionCollection& obj);

	//operator== for NULL
	bool operator==(const int null);

	//operator!= for two smart pointers
	bool operator!=(PermissionCollection& obj);

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
