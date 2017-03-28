///////////////////////////////////////////////////////////////////////
//This header file was generated by FMI code generator.
//FMI Version: 7.6; Build: 2
//This is the declaration of the smart pointer for class 'java.security.Key



#if !defined JAVA_SECURITY_KEY_H
	#define JAVA_SECURITY_KEY_H


#include "java/security/Key_stub.h"
#include "java/io/Serializable.h"



//These incudes are needed for the methods of the Stub
#include "java/security/Key_interface.h"


namespace com{
	namespace mintech{
		namespace utils{
			namespace fmi{
class JNIException;
}}}}

namespace com{
	namespace mintech{
		namespace utils{
			namespace fmi{
class FMIException;
}}}}

namespace java{
	namespace io{
class Serializable;
}} //Close namespace


using namespace com::mintech::utils::fmi;
using namespace java::io;

namespace java{
	namespace security{

class Key;


class DLL_EXPORT Key :  public virtual java::io::Serializable{
public:
/////////////////////
//Public Stub methods

//Public methods from java.lang.object
	string toString();

//End of methods from java.lang.Object


//Key Public methods
	string getAlgorithm();

	FByteArray getEncoded();

	string getFormat();

//End of Key Public methods

//Public data members methods
	//Public data members retrieval methods
	//'final' fields
	static jlong get_serialVersionUID();

	//Public data members set methods
//End public data members methods
//End public Stub methods

public:
////////////////////////////////
//Internal Smart Pointer methods

	//Constructor / Destructor
	Key();

	//Copy constructor
	Key(const Key& copy);

	//Constructor with stub for returned objects (a new stub should return as a smart pointer)
	Key(Key_stub* stub);

	//Constructor with jobject for returned objects
	Key(jobject obj);

	//Constructor with const int for handling NULL
	Key(const int null);

	//Set the stub
	void setStub(Key_interface* stub);

	//Get the stub
	Object_interface* getStub() const;

	//operator= for two smart pointers
	Key& operator=(const Key& copy);

	//operator= for NULL
	Key& operator=(const int null);

	//operator== for two smart pointers
	bool operator==(Key& obj);

	//operator== for NULL
	bool operator==(const int null);

	//operator!= for two smart pointers
	bool operator!=(Key& obj);

	//operator!= for NULL
	bool operator!=(const int null);

	//isInstanceOf: checks if this object is an instance of the class represented by the
	//smart pointer parameter
	bool isInstanceOf(Object& checkObj);

	//isAssignableFrom: checks if this object can be safely cast from checkObj
	static bool isAssignableFrom(const Object& checkObj);

	//Casting methods
	static Key castFrom_Object(const Object& base);

	static Key castFrom_Serializable(const Serializable& base);
};


}} //Close namespace



#endif
