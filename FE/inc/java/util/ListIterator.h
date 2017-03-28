///////////////////////////////////////////////////////////////////////
//This header file was generated by FMI code generator.
//FMI Version: 7.6; Build: 2
//This is the declaration of the smart pointer for class 'java.util.ListIterator



#if !defined JAVA_UTIL_LISTITERATOR_H
	#define JAVA_UTIL_LISTITERATOR_H


#include "java/util/ListIterator_stub.h"
#include "java/util/Iterator.h"



//These incudes are needed for the methods of the Stub
#include "java/util/ListIterator_interface.h"


namespace com{
	namespace mintech{
		namespace utils{
			namespace fmi{
class JNIException;
}}}}

namespace com{
	namespace mintech{
		namespace utils{
			namespace fmi{
class FMIException;
}}}}

namespace java{
	namespace util{
class Iterator;
}} //Close namespace


using namespace com::mintech::utils::fmi;
using namespace java::util;

namespace java{
	namespace util{

class ListIterator;


class DLL_EXPORT ListIterator :  public virtual java::util::Iterator{
public:
/////////////////////
//Public Stub methods

//Public methods from java.lang.object
	string toString();

//End of methods from java.lang.Object


//ListIterator Public methods
	void add(const Object& p1);

	bool hasNext();

	java::lang::Object next();

	void remove();

	void set(const Object& p1);

	bool hasPrevious();

	jint nextIndex();

	java::lang::Object previous();

	jint previousIndex();

//End of ListIterator Public methods

//End public Stub methods

public:
////////////////////////////////
//Internal Smart Pointer methods

	//Constructor / Destructor
	ListIterator();

	//Copy constructor
	ListIterator(const ListIterator& copy);

	//Constructor with stub for returned objects (a new stub should return as a smart pointer)
	ListIterator(ListIterator_stub* stub);

	//Constructor with jobject for returned objects
	ListIterator(jobject obj);

	//Constructor with const int for handling NULL
	ListIterator(const int null);

	//Set the stub
	void setStub(ListIterator_interface* stub);

	//Get the stub
	Object_interface* getStub() const;

	//operator= for two smart pointers
	ListIterator& operator=(const ListIterator& copy);

	//operator= for NULL
	ListIterator& operator=(const int null);

	//operator== for two smart pointers
	bool operator==(ListIterator& obj);

	//operator== for NULL
	bool operator==(const int null);

	//operator!= for two smart pointers
	bool operator!=(ListIterator& obj);

	//operator!= for NULL
	bool operator!=(const int null);

	//isInstanceOf: checks if this object is an instance of the class represented by the
	//smart pointer parameter
	bool isInstanceOf(Object& checkObj);

	//isAssignableFrom: checks if this object can be safely cast from checkObj
	static bool isAssignableFrom(const Object& checkObj);

	//Casting methods
	static ListIterator castFrom_Object(const Object& base);

	static ListIterator castFrom_Iterator(const Iterator& base);
};


}} //Close namespace



#endif
