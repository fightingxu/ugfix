///////////////////////////////////////////////////////////////////////
// this header file was generated by FMI code generator.
// FMI Version: 7.6; Build: 2
// it represents the Java object 'Date'.
// this file includes the necessary wrappings for the JNI calls to the Java object.


#if !defined JAVA_UTILDATE_STUB_H
	#define JAVA_UTILDATE_STUB_H




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
	namespace util{
class Date;
}} // close namespace

namespace java{
	namespace lang{
class Class;
}} // close namespace


using com::mintech::utils::fmi::JNIException;
using java::lang::Object;
using java::util::Date;
using java::lang::Class;

namespace java{
	namespace util{
class Date_stub;


class DLL_EXPORT Date_stub : public Object_interface
{
public:
//////////////////////
// public Constructors
// these constructors are for the C++ stubs. They do not create Java objects!

	// default constructor
	Date_stub();

	// constructor with jobject parameter for methods that return this object
	Date_stub(jobject obj);

	// destructor
	~Date_stub();

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
//Date Public methods
	jint compareTo(const Object& p1);

	jint compareTo(const Date& p1);

	java::lang::Object clone();

	static 	jlong parse(const string& p1);

	bool after(const Date& p1);

	bool before(const Date& p1);

	jint getDate();

	jint getHours();

	jint getMinutes();

	jint getMonth();

	jint getSeconds();

	jlong getTime();

	jint getYear();

	void setTime(const jlong p1);

	static 	jlong UTC(const jint p1, const jint p2, const jint p3, const jint p4, const jint p5, const jint p6);

	jint getDay();

	jint getTimezoneOffset();

	void setDate(const jint p1);

	void setHours(const jint p1);

	void setMinutes(const jint p1);

	void setMonth(const jint p1);

	void setSeconds(const jint p1);

	void setYear(const jint p1);

	string toGMTString();

	string toLocaleString();

//////////////////////////////////
// end of Date Public methods

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
	static jmethodID method_7_ID;
	static jmethodID method_8_ID;
	static jmethodID method_9_ID;
	static jmethodID method_10_ID;
	static jmethodID method_11_ID;
	static jmethodID method_12_ID;
	static jmethodID method_13_ID;
	static jmethodID method_14_ID;
	static jmethodID method_15_ID;
	static jmethodID method_16_ID;
	static jmethodID method_17_ID;
	static jmethodID method_18_ID;
	static jmethodID method_19_ID;
	static jmethodID method_20_ID;
	static jmethodID method_21_ID;
	static jmethodID method_22_ID;
	static jmethodID method_23_ID;
	static jmethodID method_24_ID;
	static jmethodID method_25_ID;
	static jmethodID method_26_ID;

};


}} // close namespace

#endif