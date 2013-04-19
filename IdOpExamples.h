// IdOp - Custom Operator Library
//
// http://cogwheel.info/idop/
//
// Copyright (c) 2009, Matthew Orlando
//
// See IdOp.h for documentation and license

#ifndef _IDOPEXAMPLES_H_
#define _IDOPEXAMPLES_H_

#include <stdexcept>
#include <string>
#include <cassert>

namespace Examples {

	template<typename T>
	class Sum {
	public:
		T operator()(const T& left, const T& right) const
		{ return left + right; }
	};

	template<typename T>
	class Difference {
	public:
		T operator()(const T& left, const T& right) const
		{ T val = left - right; return val >= 0 ? val : -val; }
	};

	template<typename T>
	class Product {
	public:
		T operator()(const T& left, const T& right) const
		{ return left * right; }
	};

	template<typename T>
	class Quotient {
	public:
		T operator()(const T& left, const T& right) const
		{ return left / right; }
	};

	template<typename T>
	class ThrowNotEqual {
	public:
		void operator()(const T& left, const T& right) const
		{ if (left != right) throw std::runtime_error("left != right"); }
	};

	template<typename T>
	class ThrowEqual {
	public:
		void operator()(const T& left, const T& right) const
		{ if (left == right) throw std::runtime_error("left == right"); }
	};

	template<typename T>
	class AssertNotEqual {
	public:
		void operator()(const T& left, const T& right) const
		{ assert(left != right); }
	};

	template<typename T>
	class AssertEqual {
	public:
		void operator()(const T& left, const T& right) const
		{ assert(left == right); }
	};

	template<typename T>
	class Contains {
	public:
		bool operator()(const T& left, const T& right) const
		{ return std::string(left).find(right) != std::string::npos; }
	};

	template<typename T>
	class Swap {
	public:
		void operator()(T& left, T& right) const
		{ T temp = left; left = right; right = temp; }
	};

	template<typename T>
	class AddLeft {
	public:
		T& operator()(T& left, const T& right) const
		{ left += right; return left; }
	};


}



#endif