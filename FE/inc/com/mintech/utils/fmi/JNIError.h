#if !defined JNIERROR_H
	#define JNIERROR_H

#include "jni.h"
#include "com/mintech/utils/fmi/JNIThrowable.h"
#include "com/mintech/utils/fmi/DllExportImport.h"
#include "StdAfx_Fmi.h"


namespace com{
	namespace mintech{
		namespace utils{
			namespace fmi{
class JNIError;

class DLL_EXPORT JNIError : public JNIThrowable
{
public:
	JNIError(char* message, char* stack);
};

}}}} //Close namespace

#endif //JNIERROR_H
