#pragma once
#ifndef __FT_UTILS__
#define __FT_UTILS__


#include <cstddef>
#include <sstream>
#include <string>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string.h>
#include <cassert>

#define Max(a, b) (a > b ? a : b)

#ifndef char16_t
#define char16_t	unsigned short
#endif

#ifndef char32_t
#define char32_t	unsigned int
#endif


class RBIterator;


namespace ft {
/*

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
*/


// to_string
    template<typename T>
    std::string to_string(T t) {
        // std::basic_ostringstream<T> stream;
        // stream << t;
        // return (stream.str());
        (void) t;
        return ("");
    }


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


//iterator_traits
    struct input_iterator_tag { };
    struct output_iterator_tag { };
    struct forward_iterator_tag : public input_iterator_tag { };
    struct bidirectional_iterator_tag : public forward_iterator_tag { };
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };


    template< class Iter >
    struct iterator_traits {
        typedef typename 	Iter::difference_type 		difference_type;
        typedef typename 	Iter::value_type 			value_type;
        typedef typename 	Iter::pointer 				pointer;
        typedef typename 	Iter::reference 			reference;
        typedef typename 	Iter::iterator_category		iterator_category;
    };

    template< class T >
    struct iterator_traits<T*> {
        typedef ptrdiff_t								difference_type;
        typedef T										value_type;
        typedef T*										pointer;
        typedef T&										reference;
        typedef	ft::random_access_iterator_tag			iterator_category;
    };

    template< class T >
    struct iterator_traits<const T*> {
        typedef ptrdiff_t								difference_type;
        typedef T										value_type;
        typedef T*										pointer;
        typedef T&										reference;
        typedef	ft::random_access_iterator_tag			iterator_category;
    };


// remove_cv
    template< class T > struct remove_cv                   { typedef T type; };
    template< class T > struct remove_cv<const T>          { typedef T type; };
    template< class T > struct remove_cv<volatile T>       { typedef T type; };
    template< class T > struct remove_cv<const volatile T> { typedef T type; };

// remove_const
    template< class T > struct remove_const                { typedef T type; };
    template< class T > struct remove_const<const T>       { typedef T type; };

// remove_volatile
    template< class T > struct remove_volatile             { typedef T type; };
    template< class T > struct remove_volatile<volatile T> { typedef T type; };


//integral constant
    template<typename T, T _v>
    struct integral_constant
    {
        static const T                      value = _v;
        typedef T                           value_type;
        typedef integral_constant<T, _v>    type;
        operator value_type() const { return value; };
    };

    template<bool _v>
    struct bool_constant : integral_constant<bool, _v> {};
    typedef bool_constant<true>::type true_type;
    typedef bool_constant<false>::type false_type;

//is_integral
    template<typename>
    struct is_integral_helper: public false_type{};
    template<>
    struct is_integral_helper<bool>: public true_type{};
    template<>
    struct is_integral_helper<char>: public true_type{};
    template<>
    struct is_integral_helper<signed char>: public true_type{};
    template<>
    struct is_integral_helper<unsigned char>: public true_type{};
    template<>
    struct is_integral_helper<wchar_t>: public true_type{};
    template<>
    struct is_integral_helper<short>: public true_type{};
    template<>
    struct is_integral_helper<unsigned short>: public true_type{};
    template<>
    struct is_integral_helper<int>: public true_type{};
    template<>
    struct is_integral_helper<unsigned int>: public true_type{};
    template<>
    struct is_integral_helper<long>: public true_type{};
    template<>
    struct is_integral_helper<unsigned long>: public true_type{};
    template<>
    struct is_integral_helper<long long>: public true_type{};
    template<>
    struct is_integral_helper<unsigned long long>: public true_type{};

    template<typename T>
struct is_integral: public is_integral_helper<typename ft::remove_const<T>::type> {};


//enable_if
    template<bool Cond, class T = void> struct enable_if {};
    template<class T> struct enable_if<true, T> { typedef T type; };

//is_same
    template<class T, class U>
    struct is_same : ft::false_type {};

    template<class T>
    struct is_same<T, T> : ft::true_type {};

//is_floating_point
template< class T >
struct is_floating_point : ft::integral_constant< bool,
                ft::is_same<float, typename ft::remove_cv<T>::type>::value  ||
                ft::is_same<double, typename ft::remove_cv<T>::type>::value  ||
                ft::is_same<long double, typename ft::remove_cv<T>::type>::value> {};

//is_arithmetic
template< class T >
struct is_arithmetic : ft::integral_constant<bool,
        ft::is_integral<T>::value || ft::is_floating_point<T>::value>
        {};

// is_signed
template<typename T,bool = ft::is_arithmetic<T>::value>
struct is_signed : ft::integral_constant<bool, T(-1) < T(0)> {};

template<typename T>
struct is_signed<T,false> : ft::false_type {};


//is_iterator
    template<typename T, typename = void>
    struct is_iterator : ft::false_type {};

    template<typename T>
    struct is_iterator<T, typename ft::enable_if<!ft::is_same<typename ft::iterator_traits<T>::value_type, void>::value>::type>:
            ft::true_type {};

//_is_random_access_iterator
    template< typename Itr>
    struct _is_random_access_iterator : public ft::integral_constant<bool,
            ft::is_same<typename ft::iterator_traits<Itr>::iterator_category, std::random_access_iterator_tag>::value ||
            ft::is_same<typename ft::iterator_traits<Itr>::iterator_category, ft::random_access_iterator_tag>::value
    >{};

//is_mem_comparable
    template<typename Itr>
    struct _is_mem_comp : ft::integral_constant< bool,
            ft::_is_random_access_iterator<Itr>::value &&
            ft::is_integral<typename ft::iterator_traits<Itr>::value_type>::value &&
            !ft::is_signed<typename ft::iterator_traits<Itr>::value_type>::value >{};

//is_mem_copyable
    template<typename Itr>
    struct _is_mem_cpy : ft::integral_constant<bool,
            ft::_is_random_access_iterator<Itr>::value &&
            ft::is_integral<typename ft::iterator_traits<Itr>::value_type>:: value> {};

//lexicographical_compare
template<class InputIt1, class InputIt2, class Compare>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                 InputIt2 first2, InputIt2 last2, Compare comp)
    {
        while ((first1 != last1) && (first2 != last2)) {
            if (comp(*first1, *first2))
                return true;
            else if (comp(*first2, *first1))
                return false;
            ++first1;
            (void) ++first2;
        }
        return (first1 == last1) && (first2 != last2);
    }

//for non_mem_comparable
    template< class InputIt1, class InputIt2 >
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2,
    typename ft::enable_if<(!ft::_is_mem_comp<InputIt1>::value || !ft::_is_mem_comp<InputIt2>::value), InputIt1>::type* = ft_nullptr) {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
        {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }
        return (first1 == last1) && (first2 != last2);
    };


//for mem_comparable
    template< class InputIt1, class InputIt2 >
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2,
    typename ft::enable_if<(ft::_is_mem_comp<InputIt1>::value && ft::_is_mem_comp<InputIt2>::value), InputIt1>::type* = ft_nullptr) {
        if (last1 - first1 > last2 - first2)
            return memcmp(first1.base(), first2.base(), (last2.base() - first2.base()) * sizeof(typename ft::iterator_traits<InputIt2>::value_type)) < 0;
        else {
            return memcmp(first1.base(), first2.base(), (last1.base() - first1.base()) * sizeof(typename ft::iterator_traits<InputIt1>::value_type)) < 0;
        }
    };


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




    //distance
    template<class It>
    typename ft::iterator_traits<It>::difference_type
    do_distance(It first, It last, typename ft::enable_if<!ft::_is_random_access_iterator<It>::value, It>::type* = ft_nullptr)
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
    do_distance(It first, It last, typename ft::enable_if<ft::_is_random_access_iterator<It>::value, It>::type* = ft_nullptr)
    {
        return last - first;
    }


    template<class It>
    typename ft::iterator_traits<It>::difference_type
    distance(It first, It last)
    {
        return ft::do_distance(first, last);
    }



    template< class T >
    struct less {

        typedef T		first_argument_type;
        typedef T		second_argument_type;
        typedef bool	result_type;


        bool operator()( const T& lhs, const T& rhs ) const {
            return lhs < rhs;
        };

    };

    enum color {black = true, red = false};

//Node
    template< class T >
    struct RBNode {
    public:

        typedef T			value_type;
        typedef T&			refrence;
        typedef T*			pointer;

        T data;
        RBNode *parent;
        RBNode *left;
        RBNode *right;
        bool is_black;

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

        ~RBNode() {};

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

        bool operator==(const RBNode& other) {
            return (data == other.data);
        }

        operator T() const {return data;}

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


//memset_v
    template< typename T>
    union u256_t {
        T       value;
        char    bytes[256];

        u256_t(T &v){
            assert(sizeof(T) <= 256);
            memset(bytes, 0, 256);
            memcpy(&value, &v, sizeof(v));
        };

        u256_t(const T &v){
            assert(sizeof(T) <= 256);
            memset(bytes, 0, 256);
            memcpy(&value, &v, sizeof(v));
        };

        bool is_constant() const {
            unsigned char i = 0;
            while (i < sizeof(T))
                if (bytes[i++] != bytes[0])
                    return false;
            return true;
        }
    };

    template< typename T>
    union u256i_t {
        T       value;
        unsigned char    bytes[256];

        u256i_t(T &v) : value(v){};

        bool is_constant() const {
            unsigned char i = 0;
            while (i < sizeof(T))
                if (bytes[i++] != bytes[0])
                    return false;
            return true;
        }
    };


    template<typename T>
    void* memset_v(void* dest, const T val, size_t n, size_t size) {
        if (!dest || !n)
            return NULL;
        u256_t<T> u(val);
        unsigned char *d = (unsigned char*) dest;
        if (u.is_constant())
            return memset(dest, u.bytes[0], n * size);

        memcpy(d, u.bytes, size);

        unsigned char* end = d + size;
        int i = 1;
        char b = 0;

        while(n>>(b+1)){

            if (n & 1<<(b)){
                memcpy(end, d, i * size);
                end += i * size;
            }
            memcpy(end, d, i * size);
            end += i * size;

            i *= 2;
            ++b;
        }
        return dest;
    }



}



#endif //__FT_UTILS__is_black