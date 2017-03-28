// operators.h: implements operators for stereaming
//////////////////////////////////////////////////////////////////////

#if !defined OPERATORS_H
	#define OPERATORS_H

#include <iostream.h>
#include "com/mintech/utils/fmi/DllExportImport.h"

namespace com{
	namespace mintech{
		namespace utils{
			namespace fmi{
				namespace builtin{
class FString;
}}}}}

using com::mintech::utils::fmi::builtin::FString;

//operators overload
DLL_EXT_API_G ostream&	operator<<(ostream& os, FString str);

DLL_EXT_API_G istream&	operator>>(istream& is, FString& str);

DLL_EXT_API_G bool		operator!=(const FString& jstring, char* str);

DLL_EXT_API_G bool		operator==(const FString& jstring, char* str);

#endif //OPERATORS_H