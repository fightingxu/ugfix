///////////////////////////////////////////////////////////////////////
// this header file was generated by FMI code generator.
// FMI Version: 7.6; Build: 2
// it represents the Java object 'URL'.
// this file includes the necessary wrappings for the JNI calls to the Java object.


#if !defined JAVA_NETURL_STUB_H
	#define JAVA_NETURL_STUB_H




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
	namespace io{
class InputStream;
}} // close namespace

namespace java{
	namespace net{
class URI;
}} // close namespace

namespace java{
	namespace net{
class URLConnection;
}} // close namespace

namespace java{
	namespace net{
class URL;
}} // close namespace

namespace java{
	namespace lang{
class Class;
}} // close namespace


using com::mintech::utils::fmi::JNIException;
using java::lang::Object;
using java::io::InputStream;
using java::net::URI;
using java::net::URLConnection;
using java::net::URL;
using java::lang::Class;

namespace java{
	namespace net{
class URL_stub;


class DLL_EXPORT URL_stub : public Object_interface
{
public:
//////////////////////
// public Constructors
// these constructors are for the C++ stubs. They do not create Java objects!

	// default constructor
	URL_stub();

	// constructor with jobject parameter for methods that return this object
	URL_stub(jobject obj);

	// destructor
	~URL_stub();

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
//URL Public methods
	/* throws java.io.IOException */
	java::io::InputStream openStream();

	string getPath();

	string getAuthority();

	string getQuery();

	/* throws java.net.URISyntaxException */
	java::net::URI toURI();

	string getFile();

	string getHost();

	string getProtocol();

	/* throws java.io.IOException */
	java::net::URLConnection openConnection();

	string getRef();

	/* throws java.io.IOException */
	java::lang::Object getContent();

	jint getDefaultPort();

	jint getPort();

	string getUserInfo();

	bool sameFile(const URL& p1);

	string toExternalForm();

//////////////////////////////////
// end of URL Public methods

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

};


}} // close namespace

#endif