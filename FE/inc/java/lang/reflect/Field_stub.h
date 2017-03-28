///////////////////////////////////////////////////////////////////////
// this header file was generated by FMI code generator.
// FMI Version: 7.6; Build: 2
// it represents the Java object 'Field'.
// this file includes the necessary wrappings for the JNI calls to the Java object.


#if !defined JAVA_LANG_REFLECTFIELD_STUB_H
	#define JAVA_LANG_REFLECTFIELD_STUB_H


#include "com/mintech/utils/fmi/builtin/arrays/FObjectArray.h"


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
class FObjectArray;
}}}}}} // close namespace

namespace java{
	namespace lang{
		namespace reflect{
class Field;
}}} // close namespace

namespace java{
	namespace lang{
class Object;
}} // close namespace

namespace java{
	namespace lang{
		namespace annotation{
class Annotation;
}}} // close namespace

namespace java{
	namespace lang{
class Class;
}} // close namespace

namespace java{
	namespace lang{
		namespace reflect{
class Type;
}}} // close namespace

namespace java{
	namespace lang{
		namespace reflect{
class AccessibleObject;
}}} // close namespace


using com::mintech::utils::fmi::JNIException;
using com::mintech::utils::fmi::builtin::arrays::FObjectArray;
using java::lang::Object;
using java::lang::annotation::Annotation;
using java::lang::Class;
using java::lang::reflect::Type;
using java::lang::reflect::AccessibleObject;

namespace java{
	namespace lang{
		namespace reflect{
class Field_stub;


class DLL_EXPORT Field_stub : public Object_interface
{
public:
//////////////////////
// public Constructors
// these constructors are for the C++ stubs. They do not create Java objects!

	// default constructor
	Field_stub();

	// constructor with jobject parameter for methods that return this object
	Field_stub(jobject obj);

	// destructor
	~Field_stub();

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
//Field Public methods
	jint getModifiers();

	/* throws java.lang.IllegalArgumentException, java.lang.IllegalAccessException */
	bool getBoolean(const Object& p1);

	/* throws java.lang.IllegalArgumentException, java.lang.IllegalAccessException */
	short getByte(const Object& p1);

	/* throws java.lang.IllegalArgumentException, java.lang.IllegalAccessException */
	jshort getShort(const Object& p1);

	/* throws java.lang.IllegalArgumentException, java.lang.IllegalAccessException */
	jchar getChar(const Object& p1);

	/* throws java.lang.IllegalArgumentException, java.lang.IllegalAccessException */
	jint getInt(const Object& p1);

	/* throws java.lang.IllegalArgumentException, java.lang.IllegalAccessException */
	jlong getLong(const Object& p1);

	/* throws java.lang.IllegalArgumentException, java.lang.IllegalAccessException */
	jfloat getFloat(const Object& p1);

	/* throws java.lang.IllegalArgumentException, java.lang.IllegalAccessException */
	jdouble getDouble(const Object& p1);

	string getName();

	/* throws java.lang.IllegalArgumentException, java.lang.IllegalAccessException */
	java::lang::Object get(const Object& p1);

	java::lang::annotation::Annotation getAnnotation(const Class& p1);

	FObjectArray getDeclaredAnnotations();

	java::lang::Class getDeclaringClass();

	bool isSynthetic();

	java::lang::reflect::Type getGenericType();

	java::lang::Class getType();

	bool isEnumConstant();

	/* throws java.lang.IllegalArgumentException, java.lang.IllegalAccessException */
	void set(const Object& p1, const Object& p2);

	/* throws java.lang.IllegalArgumentException, java.lang.IllegalAccessException */
	void setBoolean(const Object& p1, const jboolean p2);

	/* throws java.lang.IllegalArgumentException, java.lang.IllegalAccessException */
	void setByte(const Object& p1, const jbyte p2);

	/* throws java.lang.IllegalArgumentException, java.lang.IllegalAccessException */
	void setChar(const Object& p1, const jchar p2);

	/* throws java.lang.IllegalArgumentException, java.lang.IllegalAccessException */
	void setDouble(const Object& p1, const jdouble p2);

	/* throws java.lang.IllegalArgumentException, java.lang.IllegalAccessException */
	void setFloat(const Object& p1, const jfloat p2);

	/* throws java.lang.IllegalArgumentException, java.lang.IllegalAccessException */
	void setInt(const Object& p1, const jint p2);

	/* throws java.lang.IllegalArgumentException, java.lang.IllegalAccessException */
	void setLong(const Object& p1, const jlong p2);

	/* throws java.lang.IllegalArgumentException, java.lang.IllegalAccessException */
	void setShort(const Object& p1, const jshort p2);

	string toGenericString();

	FObjectArray getAnnotations();

	bool isAnnotationPresent(const Class& p1);

	bool isAccessible();

	/* throws java.lang.SecurityException */
	void setAccessible(const jboolean p1);

//////////////////////////////////
// end of Field Public methods

//////////////////////////////
// public data members methods
	////////////////////////////////////////
	// public data members retrieval methods
	//'final' fields
	static jint get_PUBLIC();

	static jint get_DECLARED();

	//////////////////////////////////
	// public data members set methods
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
	static jmethodID method_27_ID;
	static jmethodID method_28_ID;
	static jmethodID method_29_ID;
	static jmethodID method_30_ID;
	static jmethodID method_31_ID;
	static jmethodID method_32_ID;
	static jmethodID method_33_ID;

	// IDs for static data members
	static jfieldID staticField_1_ID;
	static jfieldID staticField_2_ID;

};


}}} // close namespace

#endif