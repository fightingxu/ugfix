///////////////////////////////////////////////////////////////////////
//This header file was generated by FMI code generator.
//FMI Version: 7.6; Build: 2
//This is the declaration of the smart pointer for class 'java.lang.reflect.Constructor



#if !defined JAVA_LANG_REFLECT_CONSTRUCTOR_H
	#define JAVA_LANG_REFLECT_CONSTRUCTOR_H


#include "java/lang/reflect/Constructor_stub.h"


//These incudes are needed for the methods of the Stub
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

namespace java{
	namespace lang{
		namespace reflect{
class AccessibleObject;
}}} //Close namespace


using namespace com::mintech::utils::fmi;
using namespace java::lang::reflect;

namespace java{
	namespace lang{
		namespace reflect{

class Constructor;


class DLL_EXPORT Constructor : public virtual java::lang::Object
{
public:
/////////////////////
//Public Stub methods

//Public methods from java.lang.object
	string toString();

//End of methods from java.lang.Object


//Constructor Public methods
	jint getModifiers();

	string getName();

	java::lang::annotation::Annotation getAnnotation(const Class& p1);

	FObjectArray getDeclaredAnnotations();

	java::lang::Class getDeclaringClass();

	FObjectArray getParameterTypes();

	FObjectArray getTypeParameters();

	bool isSynthetic();

	string toGenericString();

	FObjectArray getExceptionTypes();

	FObjectArray getGenericExceptionTypes();

	FObjectArray getGenericParameterTypes();

	FObjectArray getParameterAnnotations();

	bool isVarArgs();

	FObjectArray getAnnotations();

	bool isAnnotationPresent(const Class& p1);

	bool isAccessible();

	/* throws java.lang.SecurityException */
	void setAccessible(const jboolean p1);

//End of Constructor Public methods

//Public data members methods
	//Public data members retrieval methods
	//'final' fields
	static jint get_PUBLIC();

	static jint get_DECLARED();

	//Public data members set methods
//End public data members methods
//End public Stub methods

public:
////////////////////////////////
//Internal Smart Pointer methods

	//Constructor / Destructor
	Constructor();

	//Copy constructor
	Constructor(const Constructor& copy);

	//Constructor with stub for returned objects (a new stub should return as a smart pointer)
	Constructor(Constructor_stub* stub);

	//Constructor with jobject for returned objects
	Constructor(jobject obj);

	//Constructor with const int for handling NULL
	Constructor(const int null);

	//Set the stub
	void setStub(Constructor_stub* stub);

	//Get the stub
	Object_interface* getStub() const;

	//operator= for two smart pointers
	Constructor& operator=(const Constructor& copy);

	//operator= for NULL
	Constructor& operator=(const int null);

	//operator== for two smart pointers
	bool operator==(Constructor& obj);

	//operator== for NULL
	bool operator==(const int null);

	//operator!= for two smart pointers
	bool operator!=(Constructor& obj);

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
