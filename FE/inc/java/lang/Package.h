///////////////////////////////////////////////////////////////////////
//This header file was generated by FMI code generator.
//FMI Version: 7.6; Build: 2
//This is the declaration of the smart pointer for class 'java.lang.Package



#if !defined JAVA_LANG_PACKAGE_H
	#define JAVA_LANG_PACKAGE_H


#include "java/lang/Package_stub.h"


//These incudes are needed for the methods of the Stub
#include "com/mintech/utils/fmi/builtin/arrays/FObjectArray.h"


using namespace com::mintech::utils::fmi;

namespace java{
	namespace lang{

class Package;


class DLL_EXPORT Package : public virtual java::lang::Object
{
public:
/////////////////////
//Public Stub methods

//Public methods from java.lang.object
	string toString();

//End of methods from java.lang.Object


//Package Public methods
	string getName();

	java::lang::annotation::Annotation getAnnotation(const Class& p1);

	FObjectArray getAnnotations();

	FObjectArray getDeclaredAnnotations();

	static 	java::lang::Package getPackage(const string& p1);

	bool isAnnotationPresent(const Class& p1);

	static 	FObjectArray getPackages();

	bool isSealed();

	bool isSealed(const URL& p1);

	/* throws java.lang.NumberFormatException */
	bool isCompatibleWith(const string& p1);

	string getImplementationTitle();

	string getImplementationVendor();

	string getImplementationVersion();

	string getSpecificationTitle();

	string getSpecificationVendor();

	string getSpecificationVersion();

//End of Package Public methods

//End public Stub methods

public:
////////////////////////////////
//Internal Smart Pointer methods

	//Constructor / Destructor
	Package();

	//Copy constructor
	Package(const Package& copy);

	//Constructor with stub for returned objects (a new stub should return as a smart pointer)
	Package(Package_stub* stub);

	//Constructor with jobject for returned objects
	Package(jobject obj);

	//Constructor with const int for handling NULL
	Package(const int null);

	//Set the stub
	void setStub(Package_stub* stub);

	//Get the stub
	Object_interface* getStub() const;

	//operator= for two smart pointers
	Package& operator=(const Package& copy);

	//operator= for NULL
	Package& operator=(const int null);

	//operator== for two smart pointers
	bool operator==(Package& obj);

	//operator== for NULL
	bool operator==(const int null);

	//operator!= for two smart pointers
	bool operator!=(Package& obj);

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
