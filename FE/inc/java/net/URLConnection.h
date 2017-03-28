///////////////////////////////////////////////////////////////////////
//This header file was generated by FMI code generator.
//FMI Version: 7.6; Build: 2
//This is the declaration of the smart pointer for class 'java.net.URLConnection



#if !defined JAVA_NET_URLCONNECTION_H
	#define JAVA_NET_URLCONNECTION_H


#include "java/net/URLConnection_stub.h"


//These incudes are needed for the methods of the Stub


using namespace com::mintech::utils::fmi;

namespace java{
	namespace net{

class URLConnection;


class DLL_EXPORT URLConnection : public virtual java::lang::Object
{
public:
/////////////////////
//Public Stub methods

//Public methods from java.lang.object
	string toString();

//End of methods from java.lang.Object


//URLConnection Public methods
	java::net::URL getURL();

	/* throws java.io.IOException */
	java::security::Permission getPermission();

	/* throws java.io.IOException */
	java::lang::Object getContent();

	/* throws java.io.IOException */
	java::io::InputStream getInputStream();

	/* throws java.io.IOException */
	void connect();

	void setRequestProperty(const string& p1, const string& p2);

	jlong getDate();

	jint getContentLength();

	static 	java::net::FileNameMap getFileNameMap();

	string getHeaderField(const jint p1);

	string getHeaderField(const string& p1);

	string getHeaderFieldKey(const jint p1);

	jlong getLastModified();

	void addRequestProperty(const string& p1, const string& p2);

	string getContentType();

	java::util::Map getRequestProperties();

	string getRequestProperty(const string& p1);

	static 	string guessContentTypeFromName(const string& p1);

	/* throws java.io.IOException */
	static 	string guessContentTypeFromStream(const InputStream& p1);

	bool getAllowUserInteraction();

	jint getConnectTimeout();

	string getContentEncoding();

	static 	bool getDefaultAllowUserInteraction();

	static 	string getDefaultRequestProperty(const string& p1);

	bool getDefaultUseCaches();

	bool getDoInput();

	bool getDoOutput();

	jlong getExpiration();

	jlong getHeaderFieldDate(const string& p1, const jlong p2);

	jint getHeaderFieldInt(const string& p1, const jint p2);

	java::util::Map getHeaderFields();

	jlong getIfModifiedSince();

	/* throws java.io.IOException */
	java::io::OutputStream getOutputStream();

	jint getReadTimeout();

	bool getUseCaches();

	void setAllowUserInteraction(const jboolean p1);

	void setConnectTimeout(const jint p1);

	static 	void setDefaultAllowUserInteraction(const jboolean p1);

	static 	void setDefaultRequestProperty(const string& p1, const string& p2);

	void setDefaultUseCaches(const jboolean p1);

	void setDoInput(const jboolean p1);

	void setDoOutput(const jboolean p1);

	static 	void setFileNameMap(const FileNameMap& p1);

	void setIfModifiedSince(const jlong p1);

	void setReadTimeout(const jint p1);

	void setUseCaches(const jboolean p1);

//End of URLConnection Public methods

//End public Stub methods

public:
////////////////////////////////
//Internal Smart Pointer methods

	//Constructor / Destructor
	URLConnection();

	//Copy constructor
	URLConnection(const URLConnection& copy);

	//Constructor with stub for returned objects (a new stub should return as a smart pointer)
	URLConnection(URLConnection_stub* stub);

	//Constructor with jobject for returned objects
	URLConnection(jobject obj);

	//Constructor with const int for handling NULL
	URLConnection(const int null);

	//Set the stub
	void setStub(URLConnection_stub* stub);

	//Get the stub
	Object_interface* getStub() const;

	//operator= for two smart pointers
	URLConnection& operator=(const URLConnection& copy);

	//operator= for NULL
	URLConnection& operator=(const int null);

	//operator== for two smart pointers
	bool operator==(URLConnection& obj);

	//operator== for NULL
	bool operator==(const int null);

	//operator!= for two smart pointers
	bool operator!=(URLConnection& obj);

	//operator!= for NULL
	bool operator!=(const int null);

	//isInstanceOf: checks if this object is an instance of the class represented by the
	//smart pointer parameter
	bool isInstanceOf(Object& checkObj);

	//isAssignableFrom: checks if this object can be safely cast from checkObj
	static bool isAssignableFrom(const Object& checkObj);
};


}} //Close namespace



#endif