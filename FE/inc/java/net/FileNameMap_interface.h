///////////////////////////////////////////////////////////////////////
//This header file was generated by FMI code generator.
//FMI Version: 7.6; Build: 2
//It represents the Java object 'FileNameMap_interface'.
//This file includs the necessary wrappings for the JNI calls to the Java object.


#if !defined JAVA_NET_FILENAMEMAP_INTERFACE_H
	#define JAVA_NET_FILENAMEMAP_INTERFACE_H



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

using namespace com::mintech::utils::fmi;
namespace java{
	namespace net{
class FileNameMap_interface;

class DLL_EXPORT FileNameMap_interface : public java::lang::Object_interface
{
public:
//Public Methods
	//Destructor
	virtual ~FileNameMap_interface() { }

	virtual string getContentTypeFor(const string& p1) = 0;

	//get method for the object name
	virtual const char* getFullName() = 0;

	//get / set methods for the Java object reference
	virtual jobject getReference() const		{ return m_ref;	}

	virtual void setReference(jobject ref)		{ m_ref = ref;	}

};

}} //Close namespace



#endif
