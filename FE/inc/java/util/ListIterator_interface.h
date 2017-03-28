///////////////////////////////////////////////////////////////////////
//This header file was generated by FMI code generator.
//FMI Version: 7.6; Build: 2
//It represents the Java object 'ListIterator_interface'.
//This file includs the necessary wrappings for the JNI calls to the Java object.


#if !defined JAVA_UTIL_LISTITERATOR_INTERFACE_H
	#define JAVA_UTIL_LISTITERATOR_INTERFACE_H



#include "com/mintech/utils/fmi/JNIException.h"
#include "com/mintech/utils/fmi/JNIError.h"
#include "com/mintech/utils/fmi/FMIException.h"
#include "java/lang/Object_interface.h"
#include "java/util/Iterator_interface.h"


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
}} //Close namespace

namespace java{
	namespace util{
class Iterator_interface;
}} //Close namespace


using namespace com::mintech::utils::fmi;
using namespace java::lang;
using namespace java::util;

namespace java{
	namespace util{
class ListIterator_interface;

class DLL_EXPORT ListIterator_interface :  public java::util::Iterator_interface
{
public:
//Public Methods
	//Destructor
	virtual ~ListIterator_interface() { }

	virtual void add(const Object& p1) = 0;

	virtual bool hasNext() = 0;

	virtual java::lang::Object next() = 0;

	virtual void remove() = 0;

	virtual void set(const Object& p1) = 0;

	virtual bool hasPrevious() = 0;

	virtual jint nextIndex() = 0;

	virtual java::lang::Object previous() = 0;

	virtual jint previousIndex() = 0;

	//get method for the object name
	virtual const char* getFullName() = 0;

	//get / set methods for the Java object reference
	virtual jobject getReference() const		{ return m_ref;	}

	virtual void setReference(jobject ref)		{ m_ref = ref;	}

};

}} //Close namespace



#endif