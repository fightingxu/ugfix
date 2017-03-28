///////////////////////////////////////////////////////////////////////
// this header file was generated by FMI code generator.
// FMI Version: 7.6; Build: 2
// it represents the Java object 'CodeSigner'.
// this file includes the necessary wrappings for the JNI calls to the Java object.


#if !defined JAVA_SECURITYCODESIGNER_STUB_H
	#define JAVA_SECURITYCODESIGNER_STUB_H




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
	namespace lang{
class Object;
}} // close namespace

namespace java{
	namespace security{
		namespace cert{
class CertPath;
}}} // close namespace

namespace java{
	namespace security{
class Timestamp;
}} // close namespace

namespace java{
	namespace lang{
class Class;
}} // close namespace


using com::mintech::utils::fmi::JNIException;
using java::lang::Object;
using java::security::cert::CertPath;
using java::security::Timestamp;
using java::lang::Class;

namespace java{
	namespace security{
class CodeSigner_stub;


class DLL_EXPORT CodeSigner_stub : public Object_interface
{
public:
//////////////////////
// public Constructors
// these constructors are for the C++ stubs. They do not create Java objects!

	// default constructor
	CodeSigner_stub();

	// constructor with jobject parameter for methods that return this object
	CodeSigner_stub(jobject obj);

	// destructor
	~CodeSigner_stub();

//////////////////
// utility methods
	// initialize all the IDs
	static void initialize();

	// get the object's full name
	virtual const char* getFullName();

	// get the class holder
	jclass getCls();

// end utility methods
//////////////////////

///////////////////////////////////////
// public methods from java.lang.object
	string toString();


// end of methods from java.lang.Object
///////////////////////////////////////


//////////////////////////////////
//CodeSigner Public methods
	java::security::cert::CertPath getSignerCertPath();

	java::security::Timestamp getTimestamp();

//////////////////////////////////
// end of CodeSigner Public methods

//////////////////////////////
// public data members methods
//end public data members methods
/////////////////////////////////

private:
	// indicates if an instance of this stub has already been created
	static bool m_firstTime;

	// class holder (defined static to allow accessibility to static methods)
	static jclass m_cls;

	// the object's full name
	static char* m_objectName;

private:
	// java.lang.Class getName() method's ID
	static jmethodID m_getName_method_ID;

	// java.lang.Object Methods' IDs
	static jmethodID method_1_ID;

	// methods' IDs
	static jmethodID method_2_ID;
	static jmethodID method_3_ID;

};


}} // close namespace

#endif