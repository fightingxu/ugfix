///////////////////////////////////////////////////////////////////////
//This header file was generated by FMI code generator.
//FMI Version: 7.6; Build: 2
//This is the declaration of the smart pointer for class 'java.util.Enumeration



#if !defined JAVA_UTIL_ENUMERATION_H
	#define JAVA_UTIL_ENUMERATION_H


#include "java/util/Enumeration_stub.h"



//These incudes are needed for the methods of the Stub
#include "java/util/Enumeration_interface.h"


using namespace com::mintech::utils::fmi;

namespace java{
	namespace util{

class Enumeration;


class DLL_EXPORT Enumeration : public virtual java::lang::Object
{
public:
/////////////////////
//Public Stub methods

//Public methods from java.lang.object
	string toString();

//End of methods from java.lang.Object


//Enumeration Public methods
	bool hasMoreElements();

	java::lang::Object nextElement();

//End of Enumeration Public methods

//End public Stub methods

public:
////////////////////////////////
//Internal Smart Pointer methods

	//Constructor / Destructor
	Enumeration();

	//Copy constructor
	Enumeration(const Enumeration& copy);

	//Constructor with stub for returned objects (a new stub should return as a smart pointer)
	Enumeration(Enumeration_stub* stub);

	//Constructor with jobject for returned objects
	Enumeration(jobject obj);

	//Constructor with const int for handling NULL
	Enumeration(const int null);

	//Set the stub
	void setStub(Enumeration_interface* stub);

	//Get the stub
	Object_interface* getStub() const;

	//operator= for two smart pointers
	Enumeration& operator=(const Enumeration& copy);

	//operator= for NULL
	Enumeration& operator=(const int null);

	//operator== for two smart pointers
	bool operator==(Enumeration& obj);

	//operator== for NULL
	bool operator==(const int null);

	//operator!= for two smart pointers
	bool operator!=(Enumeration& obj);

	//operator!= for NULL
	bool operator!=(const int null);

	//isInstanceOf: checks if this object is an instance of the class represented by the
	//smart pointer parameter
	bool isInstanceOf(Object& checkObj);

	//isAssignableFrom: checks if this object can be safely cast from checkObj
	static bool isAssignableFrom(const Object& checkObj);

	//Casting methods
	static Enumeration castFrom_Object(const Object& base);
};


}} //Close namespace



#endif
