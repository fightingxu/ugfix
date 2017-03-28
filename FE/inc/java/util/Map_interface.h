///////////////////////////////////////////////////////////////////////
//This header file was generated by FMI code generator.
//FMI Version: 7.6; Build: 2
//It represents the Java object 'Map_interface'.
//This file includs the necessary wrappings for the JNI calls to the Java object.


#if !defined JAVA_UTIL_MAP_INTERFACE_H
	#define JAVA_UTIL_MAP_INTERFACE_H



#include "com/mintech/utils/fmi/JNIException.h"
#include "com/mintech/utils/fmi/JNIError.h"
#include "com/mintech/utils/fmi/FMIException.h"
#include "java/lang/Object_interface.h"


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
class Set;
}} //Close namespace

namespace java{
	namespace util{
class Map;
}} //Close namespace

namespace java{
	namespace util{
class Collection;
}} //Close namespace


using namespace com::mintech::utils::fmi;
using namespace java::lang;
using namespace java::util;

namespace java{
	namespace util{
class Map_interface;

class DLL_EXPORT Map_interface : public java::lang::Object_interface
{
public:
//Public Methods
	//Destructor
	virtual ~Map_interface() { }

	virtual java::lang::Object put(const Object& p1, const Object& p2) = 0;

	virtual void clear() = 0;

	virtual bool isEmpty() = 0;

	virtual java::util::Set entrySet() = 0;

	virtual java::lang::Object get(const Object& p1) = 0;

	virtual void putAll(const Map& p1) = 0;

	virtual jint size() = 0;

	virtual java::util::Collection values() = 0;

	virtual java::lang::Object remove(const Object& p1) = 0;

	virtual java::util::Set keySet() = 0;

	virtual bool containsKey(const Object& p1) = 0;

	virtual bool containsValue(const Object& p1) = 0;

	//get method for the object name
	virtual const char* getFullName() = 0;

	//get / set methods for the Java object reference
	virtual jobject getReference() const		{ return m_ref;	}

	virtual void setReference(jobject ref)		{ m_ref = ref;	}

};

}} //Close namespace



#endif