///////////////////////////////////////////////////////////////////////
// this header file was generated by FMI code generator.
// FMI Version: 7.6; Build: 2
// it represents the Java object 'CByteString'.
// this file includes the necessary wrappings for the JNI calls to the Java object.


#if !defined COM_SUNGARD_CS_FIX_FIXGATEWAY_API_CAPICBYTESTRING_STUB_H
	#define COM_SUNGARD_CS_FIX_FIXGATEWAY_API_CAPICBYTESTRING_STUB_H


#include "com/mintech/utils/fmi/builtin/arrays/FByteArray.h"


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

namespace com{
	namespace mintech{
		namespace utils{
			namespace fmi{
				namespace builtin{
					namespace arrays{
class FByteArray;
}}}}}} // close namespace

namespace java{
	namespace lang{
class Class;
}} // close namespace

namespace java{
	namespace lang{
class Object;
}} // close namespace


using com::mintech::utils::fmi::JNIException;
using com::mintech::utils::fmi::builtin::arrays::FByteArray;
using java::lang::Class;
using java::lang::Object;

namespace com{
	namespace sungard{
		namespace cs{
			namespace fix{
				namespace fixgateway{
					namespace api{
						namespace capi{
class CByteString_stub;


class DLL_EXPORT CByteString_stub : public Object_interface
{
public:
//////////////////////
// public Constructors
// these constructors are for the C++ stubs. They do not create Java objects!

	// default constructor
	CByteString_stub();

	// constructor with jobject parameter for methods that return this object
	CByteString_stub(jobject obj);

	// destructor
	~CByteString_stub();

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
//CByteString Public methods
	jint getLength();

	FByteArray getArr();

	string getStr();

//////////////////////////////////
// end of CByteString Public methods

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
	static jmethodID method_4_ID;

};


}}}}}}} // close namespace

#endif
