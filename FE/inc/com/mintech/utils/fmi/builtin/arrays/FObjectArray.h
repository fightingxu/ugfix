// FObjectArray.h: interface for the byte array class.
//////////////////////////////////////////////////////////////////////

#if !defined FObjectArray_H
	#define FObjectArray_H

#include "StdAfx_Fmi.h"
#include "com/mintech/utils/fmi/builtin/arrays/FArray.h"

#include <jni.h>


namespace com{
	namespace mintech{
		namespace utils{
			namespace fmi{
				namespace builtin{
					namespace arrays{
class FArray;
}}}}}}

namespace com{
	namespace mintech{
		namespace utils{
			namespace fmi{
				namespace builtin{
					namespace arrays{
class FObjectArray;


/////////////////////

class DLL_EXPORT FObjectArray : public com::mintech::utils::fmi::builtin::arrays::FArray
{
public:
	//Constructors
	//////////////
	FObjectArray(jobjectArray array);

	FObjectArray(Object array);

	//Copy constructor
	FObjectArray(const FObjectArray& farray);
	
public:
	//oprator overload to access a specific element in the array
	jobject	operator[](int index);
};


}}}}}} //Close namespace

#endif //FObjectArray
