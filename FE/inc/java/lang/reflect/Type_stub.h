///////////////////////////////////////////////////////////////////////
// this header file was generated by FMI code generator.
// FMI Version: 7.6; Build: 2
// it represents the Java object 'Type'.
// this file includes the necessary wrappings for the JNI calls to the Java object.


#if !defined JAVA_LANG_REFLECTTYPE_STUB_H
	#define JAVA_LANG_REFLECTTYPE_STUB_H


#include "java/lang/reflect/Type_interface.h"


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

using com::mintech::utils::fmi::JNIException;

namespace java{
	namespace lang{
		namespace reflect{
class Type_stub;


class DLL_EXPORT Type_stub : public Type_interface
{
public:
//////////////////////
// public Constructors
// these constructors are for the C++ stubs. They do not create Java objects!

	// default constructor
	Type_stub();

	// constructor with jobject parameter for methods that return this object
	Type_stub(jobject obj);

	// destructor
	~Type_stub();

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

};


}}} // close namespace

#endif