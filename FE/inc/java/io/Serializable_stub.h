///////////////////////////////////////////////////////////////////////
// this header file was generated by FMI code generator.
// FMI Version: 7.6; Build: 2
// it represents the Java object 'Serializable'.
// this file includes the necessary wrappings for the JNI calls to the Java object.


#if !defined JAVA_IOSERIALIZABLE_STUB_H
	#define JAVA_IOSERIALIZABLE_STUB_H


#include "java/io/Serializable_interface.h"


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
	namespace io{
class Serializable_stub;


class DLL_EXPORT Serializable_stub : public Serializable_interface
{
public:
//////////////////////
// public Constructors
// these constructors are for the C++ stubs. They do not create Java objects!

	// default constructor
	Serializable_stub();

	// constructor with jobject parameter for methods that return this object
	Serializable_stub(jobject obj);

	// destructor
	~Serializable_stub();

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


}} // close namespace

#endif
