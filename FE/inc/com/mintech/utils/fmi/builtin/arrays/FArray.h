// FArray.h: interface for the byte array class.
//////////////////////////////////////////////////////////////////////

#if !defined FArray_H
	#define FArray_H

#include "StdAfx_Fmi.h"

#include <jni.h>


namespace com{
	namespace mintech{
		namespace utils{
			namespace fmi{
				namespace builtin{
					namespace arrays{
class FArray;


/////////////////////

class DLL_EXPORT FArray
{
public:
	//Constructors
	//////////////
	FArray();

	FArray(jarray array);

	FArray(Object array);

	//Copy constructor
	FArray(const FArray& array);

	virtual ~FArray();

public:
	int		length();

	jarray	getArray() const;

protected:
	jarray	m_array;

	int		m_length;
};


}}}}}} //Close namespace

#endif //FArray
