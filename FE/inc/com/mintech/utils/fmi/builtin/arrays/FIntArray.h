// FIntArray.h: interface for the byte array class.
//////////////////////////////////////////////////////////////////////

#if !defined FIntArray_H
	#define FIntArray_H

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
class FIntArray;


/////////////////////

class DLL_EXPORT FIntArray : public com::mintech::utils::fmi::builtin::arrays::FArray
{
public:
	//Constructors
	//////////////
	FIntArray(jintArray array);

public:
	jint*	getArray();

	//set the array elements of the Java object by the 'elements' buffer
	void	setElements(jint* elements);

	//oprator overload to access a specific element in the array
	jint	operator[](int index);
};


}}}}}} //Close namespace

#endif //FIntArray
