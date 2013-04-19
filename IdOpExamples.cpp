// IdOp - Custom Operator Library
//
// http://cogwheel.info/idop/
//
// Copyright (c) 2009, Matthew Orlando
//
// See IdOp.h for documentation and license

#include <iostream>
#include "IdOp.h"
#include "IdOpExamples.h"

// simple interface for single-use identifiers ("middle parts")
IDOP_CREATE_RIGHT_HANDED(^, __, -, Examples::Quotient)				//   x ^__- y <=> x / y
IDOP_CREATE_LEFT_HANDED_RET(|, o, |, Examples::AssertEqual, void)  //   x |o| y <=> assert(x == y)

// You can even do something that isn't completely frivolous

IDOP_CREATE_LEFT_HANDED_RET(<, _contains_, >, Examples::Contains, bool)
#define contains <_contains_>										//    x contains y <=> string(x).find(y)


// advanced interface for building many operators from the same identifier
IDOP_CREATE( _ ,
	IDOP_LEFT_HANDED( - ,
		IDOP_OPERATION(^, Examples::Sum)							// x -_^ y <=> x + y
	)
	IDOP_LEFT_HANDED( > ,
		IDOP_OPERATION(>, Examples::Difference)						// x >_> y <=> abs(x - y)
		IDOP_OPERATION_RET(<, Examples::ThrowNotEqual, void)		// x >_< y <=> if (x != y) throw
	)
	IDOP_RIGHT_HANDED( - ,
		IDOP_OPERATION_RET(^, Examples::AssertNotEqual, void)		//  x ^_- y <=> assert(x != y)
		IDOP_OPERATION(|, Examples::Product)						//  x |_- y <=> x * y
	)
)




int main()
{
	using namespace std;

	cout << (50 ^__- 7.0) << endl;
	cout << "Doing tie fighter assertion...\n";
	(3*5) |o| (5*3);

	const int foo = 42, bar = 69;

	cout << "foo -_^ bar == " << (foo -_^ bar) << endl;
	cout << "foo >_> bar == " << (foo >_> bar) << endl;

	try {
		foo >_< bar;
		cout << "foo >_< bar succeeded";
	} catch (std::runtime_error ex) {
		cout << "foo >_< bar failed as expected. Message: " << ex.what() << endl;
	}

	cout << "Doing foo ^_- bar assertion...\n";
	foo ^_- bar;

	cout << "foo |_- bar == " << (foo |_- bar) << endl;

	const char* s1 = "Hello, World!";
	cout << "True or false: \"Hello, World!\" contains \"Hello\"? " << boolalpha << (s1 contains "Hello") << endl;

	return 0;
}