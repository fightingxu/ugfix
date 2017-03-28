#if !defined STDAFX_FMI_H
#define STDAFX_FMI_H

#ifdef WIN32
	#if !defined FMI_I64TOA
		#define FMI_I64TOA //to avoid redefinition
		#define I64TOA(p, buffer) _i64toa(p, buffer, 10)
	#endif
	#if !defined WINVER
		#define WINVER 0x0400
	#endif
#else
	#include "string.h"
	#include "stdlib.h"

	#define I64TOA(p, buffer) _lltostr(p, buffer)
#endif

#define MAX_MSG_SIZE 10000

#if !defined JNITHROWABLE_H
	#if !defined FMIEXCEPTION_H
		#include "com/mintech/utils/fmi/JNIThrowable.h"
		#include "com/mintech/utils/fmi/Environment.h"

		#include "java/lang/Class.h"
		#include "java/lang/Object.h"
	#endif
#endif

//Get the JNIEnv pointer
#define GET_ENV() \
	JNIEnv* env = NULL; \
	jint retval = Environment::getVM()->GetEnv((void**)&env, JNI_VERSION_1_4); \
	if (retval != JNI_OK) { \
		Environment::getVM()->AttachCurrentThread((void**)&env, NULL); \
	}

#endif //STDAFX_FMI_H