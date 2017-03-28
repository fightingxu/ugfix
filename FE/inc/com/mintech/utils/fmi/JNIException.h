#if !defined JNIEXCEPTION_H
	#define JNIEXCEPTION_H

#include "jni.h"
#include "com/mintech/utils/fmi/JNIThrowable.h"
#include "com/mintech/utils/fmi/DllExportImport.h"
#include "StdAfx_Fmi.h"


namespace com{
	namespace mintech{
		namespace utils{
			namespace fmi{
class JNIException;

class DLL_EXPORT JNIException : public JNIThrowable
{
public:
	JNIException(char* message, char* stack);

};

}}}} //Close namespace

#endif //JNIEXCEPTION_H
