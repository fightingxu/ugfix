// FFloatArray.h: interface for the byte array class.
//////////////////////////////////////////////////////////////////////

#if !defined FFloatArray_H
	#define FFloatArray_H

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
class FFloatArray;


/////////////////////

class DLL_EXPORT FFloatArray : public com::mintech::utils::fmi::builtin::arrays::FArray
{
public:
	//Constructors
	//////////////
	FFloatArray(jfloatArray array);

public:
	jfloat*	getArray();

	//set the array elements of the Java object by the 'elements' buffer
	void	setElements(jfloat* elements);

	//oprator overload to access a specific element in the array
	jfloat	operator[](int index);
};


}}}}}} //Close namespace

#endif //FFloatArray
