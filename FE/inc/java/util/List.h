///////////////////////////////////////////////////////////////////////
//This header file was generated by FMI code generator.
//FMI Version: 7.6; Build: 2
//This is the declaration of the smart pointer for class 'java.util.List



#if !defined JAVA_UTIL_LIST_H
	#define JAVA_UTIL_LIST_H


#include "java/util/List_stub.h"
#include "java/util/Collection.h"



//These incudes are needed for the methods of the Stub
#include "java/util/List_interface.h"


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
class Collection;
}} //Close namespace


using namespace com::mintech::utils::fmi;
using namespace java::util;

namespace java{
	namespace util{

class List;


class DLL_EXPORT List :  public virtual java::util::Collection{
public:
/////////////////////
//Public Stub methods

//Public methods from java.lang.object
	string toString();

//End of methods from java.lang.Object


//List Public methods
	void add(const jint p1, const Object& p2);

	bool add(const Object& p1);

	jint indexOf(const Object& p1);

	void clear();

	bool contains(const Object& p1);

	bool isEmpty();

	jint lastIndexOf(const Object& p1);

	bool addAll(const jint p1, const Collection& p2);

	bool addAll(const Collection& p1);

	java::lang::Object get(const jint p1);

	java::util::Iterator iterator();

	jint size();

	FObjectArray toArray();

	bool remove(const Object& p1);

	java::lang::Object remove(const jint p1);

	java::lang::Object set(const jint p1, const Object& p2);

	bool containsAll(const Collection& p1);

	bool removeAll(const Collection& p1);

	bool retainAll(const Collection& p1);

	java::util::List subList(const jint p1, const jint p2);

	java::util::ListIterator listIterator(const jint p1);

	java::util::ListIterator listIterator();

//End of List Public methods

//End public Stub methods

public:
////////////////////////////////
//Internal Smart Pointer methods

	//Constructor / Destructor
	List();

	//Copy constructor
	List(const List& copy);

	//Constructor with stub for returned objects (a new stub should return as a smart pointer)
	List(List_stub* stub);

	//Constructor with jobject for returned objects
	List(jobject obj);

	//Constructor with const int for handling NULL
	List(const int null);

	//Set the stub
	void setStub(List_interface* stub);

	//Get the stub
	Object_interface* getStub() const;

	//operator= for two smart pointers
	List& operator=(const List& copy);

	//operator= for NULL
	List& operator=(const int null);

	//operator== for two smart pointers
	bool operator==(List& obj);

	//operator== for NULL
	bool operator==(const int null);

	//operator!= for two smart pointers
	bool operator!=(List& obj);

	//operator!= for NULL
	bool operator!=(const int null);

	//isInstanceOf: checks if this object is an instance of the class represented by the
	//smart pointer parameter
	bool isInstanceOf(Object& checkObj);

	//isAssignableFrom: checks if this object can be safely cast from checkObj
	static bool isAssignableFrom(const Object& checkObj);

	//Casting methods
	static List castFrom_Object(const Object& base);

	static List castFrom_Collection(const Collection& base);

	static List castFrom_Iterable(const Iterable& base);
};


}} //Close namespace



#endif
