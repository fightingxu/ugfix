// FString.h: interface for the special string class.
//////////////////////////////////////////////////////////////////////

#if !defined JSTRING_H
	#define JSTRING_H

#include "StdAfx_Fmi.h"
#include "com/mintech/utils/fmi/builtin/operators.h"

#include <jni.h>
#include <iostream.h>


namespace com{
	namespace mintech{
		namespace utils{
			namespace fmi{
				namespace builtin{
class FString;


/////////////////////

class DLL_EXPORT com::mintech::utils::fmi::builtin::FString
{
public:
	//Constructors
	//////////////
	FString();

	FString(char* str);

	FString(jstring str);

	//Copy constructor
	FString(FString& copy);

	#ifdef _USE_CSTRING
		FString(CString& copy);
	#endif

	virtual ~FString();

public:
	char*	getString() const;

	bool    isEmpty();

	//for << and >> overloaded operators
	ostream& print(ostream& os);

	istream& read(istream& is);

	//assignment operators
	FString	operator=(const char* str);

	FString	operator=(FString& str);

	#ifdef _USE_CSTRING
		FString	operator=(CString str);
	#endif

	//comparison operators
	bool 	operator==(const char* str);

	bool 	operator==(FString& str);

	#ifdef _USE_CSTRING
		bool 	operator==(CString str);
	#endif

	bool 	operator!=(const char* str);

	bool 	operator!=(FString& str);

	#ifdef _USE_CSTRING
		bool 	operator!=(CString str);
	#endif

	//casting oprators
	operator const char*() const;

	operator char*();

	#ifdef _USE_CSTRING
		operator CString();
	#endif


private:
	// private methods
	//retrieves the jstring as a char* - for internal use
	char*	getString(jboolean& isCopy);

	void	setString(const char* str);

private:
	jstring m_string;
};


}}}}} //Close namespace

#endif //JSTRING_H