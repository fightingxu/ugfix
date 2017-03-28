// FCharArray.h: interface for the byte array class.
//////////////////////////////////////////////////////////////////////

#if !defined FCharArray_H
	#define FCharArray_H

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
class FCharArray;


/////////////////////

class DLL_EXPORT FCharArray : public com::mintech::utils::fmi::builtin::arrays::FArray
{
public:
	//Constructors
	//////////////
	FCharArray(jcharArray array);

public:
	jchar*	getArray();

	//set the array elements of the Java object by the 'elements' buffer
	void	setElements(jchar* elements);

	//oprator overload to access a specific element in the array
	jchar	operator[](int index);
};


}}}}}} //Close namespace

#endif //FCharArray
