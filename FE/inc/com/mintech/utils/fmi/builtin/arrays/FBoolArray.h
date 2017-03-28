// FBoolArray.h: interface for the byte array class.
//////////////////////////////////////////////////////////////////////

#if !defined FBoolArray_H
	#define FBoolArray_H

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
class FBoolArray;


/////////////////////

class DLL_EXPORT FBoolArray : public com::mintech::utils::fmi::builtin::arrays::FArray
{
public:
	//Constructors
	//////////////
	FBoolArray(jbooleanArray array);

public:
	jboolean*	getArray();

	//set the array elements of the Java object by the 'elements' buffer
	void		setElements(jboolean* elements);

	//oprator overload to access a specific element in the array
	jboolean	operator[](int index);
};


}}}}}} //Close namespace

#endif //FBoolArray
