#pragma once
#ifndef __FT_UTILS__
#define __FT_UTILS__


#include <cstddef>
#include <sstream>
#include <string>
#include <iostream>
#include <memory>
#include <stdexcept>

#define Max(a, b) (a > b ? a : b)

class RBIterator;


namespace ft {

//  void
//   __throw_bad_exception(void) __attribute__((__noreturn__));

//   // Helper for exception objects in <new>
//   void
//   __throw_bad_alloc(void) __attribute__((__noreturn__));

//   void
//   __throw_bad_array_new_length(void) __attribute__((__noreturn__));

//   // Helper for exception objects in <typeinfo>
//   void
//   __throw_bad_cast(void) __attribute__((__noreturn__));

//   void
//   __throw_bad_typeid(void) __attribute__((__noreturn__));

//   // Helpers for exception objects in <stdexcept>
//   void
//   __throw_logic_error(const char*) __attribute__((__noreturn__));

//   void
//   __throw_domain_error(const char*) __attribute__((__noreturn__));

//   void
//   __throw_invalid_argument(const char*) __attribute__((__noreturn__));

//   void
//   __throw_length_error(const char*) __attribute__((__noreturn__));

//   void
//   __throw_out_of_range(const char*) __attribute__((__noreturn__));

//   void
//   __throw_out_of_range_fmt(const char*, ...) __attribute__((__noreturn__))
//     __attribute__((__format__(__gnu_printf__, 1, 2)));

//   void
//   __throw_runtime_error(const char*) __attribute__((__noreturn__));

//   void
//   __throw_range_error(const char*) __attribute__((__noreturn__));

//   void
//   __throw_overflow_error(const char*) __attribute__((__noreturn__));

//   void
//   __throw_underflow_error(const char*) __attribute__((__noreturn__));

//   // Helpers for exception objects in <ios>
//   void
//   __throw_ios_failure(const char*) __attribute__((__noreturn__));

//   void
//   __throw_ios_failure(const char*, int) __attribute__((__noreturn__));

//   // Helpers for exception objects in <system_error>
//   void
//   __throw_system_error(int) __attribute__((__noreturn__));

//   // Helpers for exception objects in <future>
//   void
//   __throw_future_error(int) __attribute__((__noreturn__));

//   // Helpers for exception objects in <functional>
//   void
//   __throw_bad_function_call() __attribute__((__noreturn__));



// to_string
template<typename T>
std::string to_string(T t) {
	// std::basic_ostringstream<T> stream;
    // stream << t;
    // return (stream.str());
	(void) t;
	return ("");
}

//compare
template< class InputIt1, class InputIt2 >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 ) {
	while (first1 != last1) {
		if (first2 == last2)
			return false;
		if (first2 <= first1)
			return false;
		first1++;
		first2++;
	}
	if (first2 == last2)
		return false;
	return true;
};


//nullptr
static class nullptr_t
{
    public:
        template<class T>
        operator T*() const { return (0); }

        template<class C, class T>
        operator T C::*() const { return (0); }

    private:
        void operator&() const;

} ft_nullptr = {};


//equal
template< class InputIt1, class InputIt2 >
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 ) {
      for (; first1 != last1; ++first1, (void) ++first2)
	    if (!(*first1 == *first2))
	      return false;
	  return true;
};

template< class InputIt1, class InputIt2, class BinaryPredicate >
bool equal( InputIt1 first1, InputIt1 last1,
            InputIt2 first2, BinaryPredicate p ) {
                for (; first1 != last1; ++first1, (void) ++last1)
                    if (!bool(p(*first1, *first2)))
                        return false;
                return true;
            };


template<class Arg1, class Arg2, class Result> 
struct binary_function {

	typedef Arg1	first_argument_type;
	typedef Arg2	second_argument_type;
	typedef Result	result_type;

};


template< class T >
struct less {

	typedef T		first_argument_type;
	typedef T		second_argument_type;
	typedef bool	result_type;


	bool operator()( const T& lhs, const T& rhs ) const {
		return lhs < rhs;
	};

};



//Node
template< class T >
struct RBNode {

public:
	T data;
	bool is_black;
	RBNode *parent;
	RBNode *left;
	RBNode *right;

	RBNode():
	data(),
	parent(ft_nullptr),
	left(ft_nullptr),
	right(ft_nullptr),
	is_black(false)
	{};

	RBNode(	const T& value, RBNode* parent = ft_nullptr, 
			RBNode* left = ft_nullptr, RBNode* right = ft_nullptr,
			bool is_black = false):
	data(value),
	parent(parent),
	left(left),
	right(right),
	is_black(is_black) 
	{};

	RBNode(const RBNode& other):
	data(other.data),
	parent(other.parent),
	left(other.left),
	right(other.right),
	is_black(other.is_black)
	{};

	virtual ~RBNode() {};

	RBNode& operator=(const RBNode& other) {
		if (*this == other)
			return *this;
		data = other.data;
		parent = other.parent;
		left = other.left;
		right = other.right;
		is_black = other.is_black;
		return *this;
	}

};



template<class T1, class T2>
bool operator==( const ft::RBNode<T1>& lhs,
                 const ft::RBNode<T2>& rhs ) {
                    return lhs.data == rhs.data;
                 };

template<class T1, class T2>
bool operator!=( const ft::RBNode<T1>& lhs,
                 const ft::RBNode<T2>& rhs ) {
                    return lhs.data != rhs.data;
                 };

template<class T1, class T2>
bool operator<( const ft::RBNode<T1>& lhs,
                 const ft::RBNode<T2>& rhs ) {
                    return lhs.data < rhs.data;
                 };

template<class T1, class T2>
bool operator<=( const ft::RBNode<T1>& lhs,
                 const ft::RBNode<T2>& rhs ) {
                    return lhs.data <= rhs.data;
                 };

template<class T1, class T2>
bool operator>( const ft::RBNode<T1>& lhs,
                 const ft::RBNode<T2>& rhs ) {
                    return lhs.data > rhs.data;
                 };
template<class T1, class T2>
bool operator>=( const ft::RBNode<T1>& lhs,
                 const ft::RBNode<T2>& rhs ) {
                    return lhs.data >= rhs.data;
                 };








}








#endif //__FT_UTILS__is_black