#if !defined FMIEXCEPTION_H
	#define FMIEXCEPTION_H

#include "jni.h"
#include "com/mintech/utils/fmi/DllExportImport.h"
#include "StdAfx_Fmi.h"

namespace com{
	namespace mintech{
		namespace utils{
			namespace fmi{
class FMIException;

class DLL_EXPORT FMIException
{
public:
	FMIException(char* message);

	char* getMessage();

	static bool	 methodNotFound();
	static bool	 dataMemberNotFound();
	static char* getMethodIdExceptionStatus();
	static char* getDataMembersExceptionStatus();

	//Check if a method id was not found in a specific class
	static void	checkMethodIdException(JNIEnv* env, const char* methodName);
	static void	checkDataMemberException(JNIEnv* env, const char* dataMemberName);

	//methods for checking methods ids
	static void	resetExceptionParams();

private:
	//The object's status for getMethodID checks
	static char m_methodsStatus[MAX_MSG_SIZE];
	//The object's status for getDataMember checks
	static char m_dataMembersStatus[MAX_MSG_SIZE];

	//this flag indicates that at least one method was not found
	static bool m_methodNotFound;
	static bool m_dataMemberNotFound;

	char m_message[MAX_MSG_SIZE];
};

}}}} //Close namespace

#endif //FMIEXCEPTION_H