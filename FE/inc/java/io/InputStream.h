///////////////////////////////////////////////////////////////////////
//This header file was generated by FMI code generator.
//FMI Version: 7.6; Build: 2
//This is the declaration of the smart pointer for class 'java.io.InputStream



#if !defined JAVA_IO_INPUTSTREAM_H
	#define JAVA_IO_INPUTSTREAM_H


#include "java/io/InputStream_stub.h"


//These incudes are needed for the methods of the Stub


using namespace com::mintech::utils::fmi;

namespace java{
	namespace io{

class InputStream;


class DLL_EXPORT InputStream : public virtual java::lang::Object
{
public:
/////////////////////
//Public Stub methods

//Public methods from java.lang.object
	string toString();

//End of methods from java.lang.Object


//InputStream Public methods
	/* throws java.io.IOException */
	void close();

	void mark(const jint p1);

	/* throws java.io.IOException */
	void reset();

	/* throws java.io.IOException */
	jint read();

	/* throws java.io.IOException */
	jint available();

	/* throws java.io.IOException */
	jlong skip(const jlong p1);

	bool markSupported();

//End of InputStream Public methods

//End public Stub methods

public:
////////////////////////////////
//Internal Smart Pointer methods

	//Constructor / Destructor
	InputStream();

	//Copy constructor
	InputStream(const InputStream& copy);

	//Constructor with stub for returned objects (a new stub should return as a smart pointer)
	InputStream(InputStream_stub* stub);

	//Constructor with jobject for returned objects
	InputStream(jobject obj);

	//Constructor with const int for handling NULL
	InputStream(const int null);

	//Set the stub
	void setStub(InputStream_stub* stub);

	//Get the stub
	Object_interface* getStub() const;

	//operator= for two smart pointers
	InputStream& operator=(const InputStream& copy);

	//operator= for NULL
	InputStream& operator=(const int null);

	//operator== for two smart pointers
	bool operator==(InputStream& obj);

	//operator== for NULL
	bool operator==(const int null);

	//operator!= for two smart pointers
	bool operator!=(InputStream& obj);

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
