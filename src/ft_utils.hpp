#ifndef __FT_UTILS__
#define __FT_UTILS__


#include <cstddef>
#include <sstream>
#include <string>
#include <iostream>
#include "ft_iterators.hpp"

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



//distance
template<class It>
typename ft::iterator_traits<It>::difference_type 
    do_distance(It first, It last, ft::input_iterator_tag)
{
    typename ft::iterator_traits<It>::difference_type result = 0;
    while (first != last) {
        ++first;
        ++result;
    }
    return result;
}

template<class It>
typename ft::iterator_traits<It>::difference_type 
    do_distance(It first, It last, ft::random_access_iterator_tag)
{
    return last - first;
}


template<class It>
typename ft::iterator_traits<It>::difference_type 
    distance(It first, It last)
{
    return ft::do_distance(first, last, typename ft::iterator_traits<It>::iterator_category());
}



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














}








#endif //__FT_UTILS__