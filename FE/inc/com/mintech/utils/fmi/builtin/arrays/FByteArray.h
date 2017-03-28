// FByteArray.h: interface for the byte array class.
//////////////////////////////////////////////////////////////////////

#if !defined FByteArray_H
	#define FByteArray_H

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
class FByteArray;


/////////////////////

class DLL_EXPORT FByteArray : public com::mintech::utils::fmi::builtin::arrays::FArray
{
public:
	//Constructors
	//////////////
	FByteArray(jbyteArray array);

public:
	//get the bytes array
	jbyte*	getArray();

	//get the bytes array
	jbyte*	getBytes();

	//get a portion of the array into a preallocated buffer (dst)
	void	getChars(int srcBegin, int srcEnd, jbyte* dst, int dstBegin);

	//set the array elements of the Java object by the 'elements' buffer
	//if 'elementsEnd' != -1, then only elementsEnd' first elements from 'elements' are taken
	void	setBytes(jbyte* elements, int elementsEnd = -1);

	//oprator overload to access a specific element in the array
	jbyte	operator[](int index);
};


}}}}}} //Close namespace

#endif //FByteArray
