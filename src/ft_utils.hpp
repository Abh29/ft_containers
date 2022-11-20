#ifndef __FT_UTILS__
#define __FT_UTILS__


#include <cstddef>
#include <sstream>
#include <string>
#include <iostream>
#include "ft_iterators.hpp"

namespace ft {

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
	std::basic_ostringstream<T> stream;
    stream << t;
    return (stream.str());
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
























}








#endif //__FT_UTILS__