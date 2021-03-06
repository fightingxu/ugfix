///////////////////////////////////////////////////////////////////////
//This header file was generated by FMI code generator.
//FMI Version: 7.6; Build: 2
//This is the declaration of the smart pointer for class 'java.security.PublicKey



#if !defined JAVA_SECURITY_PUBLICKEY_H
	#define JAVA_SECURITY_PUBLICKEY_H


#include "java/security/PublicKey_stub.h"
#include "java/security/Key.h"



//These incudes are needed for the methods of the Stub
#include "java/security/PublicKey_interface.h"


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
	namespace security{
class Key;
}} //Close namespace


using namespace com::mintech::utils::fmi;
using namespace java::security;

namespace java{
	namespace security{

class PublicKey;


class DLL_EXPORT PublicKey :  public virtual java::security::Key{
public:
/////////////////////
//Public Stub methods

//Public methods from java.lang.object
	string toString();

//End of methods from java.lang.Object


//PublicKey Public methods
	string getAlgorithm();

	FByteArray getEncoded();

	string getFormat();

//End of PublicKey Public methods

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
	PublicKey();

	//Copy constructor
	PublicKey(const PublicKey& copy);

	//Constructor with stub for returned objects (a new stub should return as a smart pointer)
	PublicKey(PublicKey_stub* stub);

	//Constructor with jobject for returned objects
	PublicKey(jobject obj);

	//Constructor with const int for handling NULL
	PublicKey(const int null);

	//Set the stub
	void setStub(PublicKey_interface* stub);

	//Get the stub
	Object_interface* getStub() const;

	//operator= for two smart pointers
	PublicKey& operator=(const PublicKey& copy);

	//operator= for NULL
	PublicKey& operator=(const int null);

	//operator== for two smart pointers
	bool operator==(PublicKey& obj);

	//operator== for NULL
	bool operator==(const int null);

	//operator!= for two smart pointers
	bool operator!=(PublicKey& obj);

	//operator!= for NULL
	bool operator!=(const int null);

	//isInstanceOf: checks if this object is an instance of the class represented by the
	//smart pointer parameter
	bool isInstanceOf(Object& checkObj);

	//isAssignableFrom: checks if this object can be safely cast from checkObj
	static bool isAssignableFrom(const Object& checkObj);

	//Casting methods
	static PublicKey castFrom_Object(const Object& base);

	static PublicKey castFrom_Key(const Key& base);

	static PublicKey castFrom_Serializable(const Serializable& base);
};


}} //Close namespace



#endif
