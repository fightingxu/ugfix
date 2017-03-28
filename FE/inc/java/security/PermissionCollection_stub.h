///////////////////////////////////////////////////////////////////////
// this header file was generated by FMI code generator.
// FMI Version: 7.6; Build: 2
// it represents the Java object 'PermissionCollection'.
// this file includes the necessary wrappings for the JNI calls to the Java object.


#if !defined JAVA_SECURITYPERMISSIONCOLLECTION_STUB_H
	#define JAVA_SECURITYPERMISSIONCOLLECTION_STUB_H




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
class Permission;
}} // close namespace

namespace java{
	namespace util{
class Enumeration;
}} // close namespace

namespace java{
	namespace lang{
class Class;
}} // close namespace

namespace java{
	namespace lang{
class Object;
}} // close namespace


using com::mintech::utils::fmi::JNIException;
using java::security::Permission;
using java::util::Enumeration;
using java::lang::Class;
using java::lang::Object;

namespace java{
	namespace security{
class PermissionCollection_stub;


class DLL_EXPORT PermissionCollection_stub : public Object_interface
{
public:
//////////////////////
// public Constructors
// these constructors are for the C++ stubs. They do not create Java objects!

	// default constructor
	PermissionCollection_stub();

	// constructor with jobject parameter for methods that return this object
	PermissionCollection_stub(jobject obj);

	// destructor
	~PermissionCollection_stub();

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
//PermissionCollection Public methods
	void add(const Permission& p1);

	java::util::Enumeration elements();

	bool implies(const Permission& p1);

	void setReadOnly();

	bool isReadOnly();

//////////////////////////////////
// end of PermissionCollection Public methods

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
	static jmethodID method_5_ID;
	static jmethodID method_6_ID;

};


}} // close namespace

#endif