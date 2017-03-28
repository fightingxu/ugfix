///////////////////////////////////////////////////////////////////////
//This header file was generated by FMI code generator.
//FMI Version: 7.6; Build: 2
//This is the declaration of the smart pointer for class 'java.security.cert.Certificate



#if !defined JAVA_SECURITY_CERT_CERTIFICATE_H
	#define JAVA_SECURITY_CERT_CERTIFICATE_H


#include "java/security/cert/Certificate_stub.h"


//These incudes are needed for the methods of the Stub
#include "com/mintech/utils/fmi/builtin/arrays/FByteArray.h"


using namespace com::mintech::utils::fmi;

namespace java{
	namespace security{
		namespace cert{

class Certificate;


class DLL_EXPORT Certificate : public virtual java::lang::Object
{
public:
/////////////////////
//Public Stub methods

//Public methods from java.lang.object
	string toString();

//End of methods from java.lang.Object


//Certificate Public methods
	string getType();

	/* throws java.security.cert.CertificateException, java.security.NoSuchAlgorithmException, java.security.InvalidKeyException, java.security.NoSuchProviderException, java.security.SignatureException */
	void verify(const PublicKey& p1);

	/* throws java.security.cert.CertificateException, java.security.NoSuchAlgorithmException, java.security.InvalidKeyException, java.security.NoSuchProviderException, java.security.SignatureException */
	void verify(const PublicKey& p1, const string& p2);

	/* throws java.security.cert.CertificateEncodingException */
	FByteArray getEncoded();

	java::security::PublicKey getPublicKey();

//End of Certificate Public methods

//End public Stub methods

public:
////////////////////////////////
//Internal Smart Pointer methods

	//Constructor / Destructor
	Certificate();

	//Copy constructor
	Certificate(const Certificate& copy);

	//Constructor with stub for returned objects (a new stub should return as a smart pointer)
	Certificate(Certificate_stub* stub);

	//Constructor with jobject for returned objects
	Certificate(jobject obj);

	//Constructor with const int for handling NULL
	Certificate(const int null);

	//Set the stub
	void setStub(Certificate_stub* stub);

	//Get the stub
	Object_interface* getStub() const;

	//operator= for two smart pointers
	Certificate& operator=(const Certificate& copy);

	//operator= for NULL
	Certificate& operator=(const int null);

	//operator== for two smart pointers
	bool operator==(Certificate& obj);

	//operator== for NULL
	bool operator==(const int null);

	//operator!= for two smart pointers
	bool operator!=(Certificate& obj);

	//operator!= for NULL
	bool operator!=(const int null);

	//isInstanceOf: checks if this object is an instance of the class represented by the
	//smart pointer parameter
	bool isInstanceOf(Object& checkObj);

	//isAssignableFrom: checks if this object can be safely cast from checkObj
	static bool isAssignableFrom(const Object& checkObj);
};


}}} //Close namespace



#endif