// FShortArray.h: interface for the byte array class.
//////////////////////////////////////////////////////////////////////

#if !defined FShortArray_H
	#define FShortArray_H

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
class FShortArray;


/////////////////////

class DLL_EXPORT FShortArray : public com::mintech::utils::fmi::builtin::arrays::FArray
{
public:
	//Constructors
	//////////////
	FShortArray(jshortArray array);

public:
	jshort*	getArray();

	//set the array elements of the Java object by the 'elements' buffer
	void	setElements(jshort* elements);

	//oprator overload to access a specific element in the array
	jshort	operator[](int index);
};


}}}}}} //Close namespace

#endif //FShortArray
