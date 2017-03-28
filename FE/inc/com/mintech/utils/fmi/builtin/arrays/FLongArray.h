// FLongArray.h: interface for the byte array class.
//////////////////////////////////////////////////////////////////////

#if !defined FLongArray_H
	#define FLongArray_H

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
class FLongArray;


/////////////////////

class DLL_EXPORT FLongArray : public com::mintech::utils::fmi::builtin::arrays::FArray
{
public:
	//Constructors
	//////////////
	FLongArray(jlongArray array);

public:
	jlong*	getArray();

	//set the array elements of the Java object by the 'elements' buffer
	void	setElements(jlong* elements);

	//oprator overload to access a specific element in the array
	jlong	operator[](int index);
};


}}}}}} //Close namespace

#endif //FLongArray
