#if !defined JNITHROWABLE_H
	#define JNITHROWABLE_H

#include "jni.h"
#include "com/mintech/utils/fmi/DllExportImport.h"
#include "StdAfx_Fmi.h"

namespace com{
	namespace mintech{
		namespace utils{
			namespace fmi{
class JNIThrowable;


class DLL_EXPORT JNIThrowable : public _jthrowable
{
public:
	JNIThrowable(char* message, char* stack);

	char* getMessage();
	char* getStack();

	static char*	getThrowableStack(jthrowable throwable);
	static char*	getThrowableMessage(jthrowable throwable);

	static void		initThrowableIDs();

public:
	static jclass		exceptionCls;

private:
	static jclass		StringWriter;
	static jclass		PrintWriter;

	static jmethodID	StringWriterInit;
	static jmethodID	PrintWriterInit;
	static jmethodID	getBufferID;
	static jmethodID	toStringID;
	static jmethodID	printThrowableStackTraceID;
	static jmethodID	printThrowableMessageID;

private:
	char m_message[MAX_MSG_SIZE];
	char m_stack[MAX_MSG_SIZE];

	static char m_msgDescription[MAX_MSG_SIZE];
	static char m_stkDescription[MAX_MSG_SIZE];
};

}}}} //Close namespace

#endif //JNITHROWABLE_H
