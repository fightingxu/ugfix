// FDoubleArray.h: interface for the byte array class.
//////////////////////////////////////////////////////////////////////

#if !defined FDoubleArray_H
	#define FDoubleArray_H

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
class FDoubleArray;


/////////////////////

class DLL_EXPORT FDoubleArray : public com::mintech::utils::fmi::builtin::arrays::FArray
{
public:
	//Constructors
	//////////////
	FDoubleArray(jdoubleArray array);

public:
	jdouble*	getArray();

	//set the array elements of the Java object by the 'elements' buffer
	void		setElements(jdouble* elements);

	//oprator overload to access a specific element in the array
	jdouble		operator[](int index);
};


}}}}}} //Close namespace

#endif //FDoubleArray
