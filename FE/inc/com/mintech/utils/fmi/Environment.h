// Environment.h: interface for the Environment class.
//////////////////////////////////////////////////////////////////////

#if !defined ENVIRONMENT_H
#define ENVIRONMENT_H

#include "StdAfx_Fmi.h"

#include <string>

namespace com{
	namespace mintech{
		namespace utils{
			namespace fmi{
class Environment;

class DLL_EXPORT Environment
{
public:
	// constructor
	Environment();

	// constructor
	Environment(char* classPath, char* jvmParameters);

	// constructor for reading parameters from file
	Environment(char* filePath);

	virtual ~Environment();

public:
	static JNIEnv* initJVM(char* classPath, char* jvmParameters);

	static JNIEnv* initJVMFromFile(char* filePath);

	static void	closeJVM();

	// JNI Env
	static JNIEnv* getEnv();
	// JVM Handler
	static JavaVM* getVM();
	// JVM version
	static char* getVMVersion();

	// trace control
	static void	enableTrace();
	static void	disableTrace();

	// deletion method for strings char* mode
	static void deleteJavaString(char* str);

	//Check if a Java throwable occurred
	static void checkThrowable(JNIEnv* env);

	// gbk-char-set to utf-char-set
	static bool GbkToUtf8(std::string const& str_gbk, std::string &str_utf);

	// utf-char-set to gbk-char-set
	static bool Utf8ToGbk(std::string const& str_utf, std::string &str_gbk);

// private methods
private:
	static void	initWithParameters(char* classPath, char* jvmParameters);
	static void	initFromFile(char* filePath);
	static void	close();

	static void	initializeJVM(char* classPath, char* jvmParameters);
	static int	parseParameters(char* jvmParameters, JavaVMOption options[]);

// data members
public:
	// for callback fuctions
	static FILE* fp;
	static jboolean	triedOnce;

#ifdef _FMI_TRACE
	// trace global method
	static void fmiTrace(char* str);
#endif

private:
	// this is the only JVM in this process
    static JNIEnv* m_env;
    static JavaVM* m_jvm;
	static char*   m_version;

#ifdef _FMI_TRACE
	// trace file
	static FILE* m_traceFile;
#endif

	static bool	traceIsEnabled;
};

}}}} //Close namespace

#endif //ENVIRONMENT_H