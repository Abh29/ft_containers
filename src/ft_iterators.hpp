#ifndef __FT_ITERATORs__
#define __FT_ITERATORs__

#include "ft_utils.hpp"
#include <cstddef>
#include <memory>


namespace ft {


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
struct is_integral: public is_integral_helper<T> {};

//enable_if
template<bool Cond, class T = void> struct enable_if {};
template<class T> struct enable_if<true, T> { typedef T type; };

//pair
template<class T1, class T2>
struct pair {

public:

    typedef T1      first_type;
    typedef T2      second_type;

    T1              first;
    T2              second;

    pair(): first(), second() {};
    pair( const T1& x, const T2& y ): first(x), second(y) {};
    template< class U1, class U2 >
    pair( const pair<U1, U2>& p ): first(p.first), second(p.second) {};

    pair& operator=( const pair& other ){
        if (other == *this)
            return *this;
        first = other.first;
        second = other.second;
        return *this;
    };
};

template< class T1, class T2 >
bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
    return (lhs.first == rhs.first) && (lhs.second == rhs.second);
};

template< class T1, class T2 >
bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
    return !(lhs == rhs);
};

template< class T1, class T2 >
bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
    if (lhs.first == rhs.first)
        return lhs.second < rhs.second;
    return lhs.first < rhs.second;
};

template< class T1, class T2 >
bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
    return !(rhs < lhs);
};

template< class T1, class T2 >
bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
    return rhs < lhs;
};

template< class T1, class T2 >
bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
    return !(lhs < rhs);
};

template< class T1, class T2 >
ft::pair<T1, T2> make_pair( T1 t, T2 u ) {
    return ft::pair<T1, T2>(t, u);
};


//baseIterator
template<class Category, class T, class Distance = std::ptrdiff_t,
    class Pointer = T*, class Reference = T&>
struct iterator {

public:

    typedef Category            iterator_category;
    typedef T                   value_type;
    typedef Distance            difference_type;
    typedef Pointer             pointer;
    typedef Reference           reference;


protected:
    pointer                     _elm;

public:

    iterator() : _elm(ft_nullptr) {};
    iterator(pointer elm): _elm(elm) {};
    iterator(iterator<class C, class U> other) : _elm(other._elm) {};
    iterator& operator= (const iterator& other) {
        if (other == *this)
            return;
        _elm = other._elm;
        return *this;
    }

    virtual ~iterator();

    pointer base() const {return _elm; };
    void swap(iterator& a, iterator& b) {
        pointer tmp = a.base();
        a._elm = b._elm;
        b._elm = tmp;
    };

    reference operator*(void) const {return *_elm;};
    pointer operator->(void) {return &(*base()); };

    iterator& operator++ () {
        ++_elm;
        return *this;
    }

    iterator& operator++ (int) {
        pointer tmp = _elm;
        ++_elm;
        return iterator(tmp);
    }

};


//reverse iterator
template< class Iter >
class reverse_iterator {

public:
    typedef Iter                                                    iterator_type;
    typedef typename ft::iterator_traits<Iter>::iterator_category   iterator_category;
    typedef typename ft::iterator_traits<Iter>::value_type          value_type;
    typedef typename ft::iterator_traits<Iter>::difference_type     difference_type;
    typedef typename ft::iterator_traits<Iter>::pointer             pointer;
    typedef typename ft::iterator_traits<Iter>::reference           reference;

protected:
    Iter        current;

public:

    reverse_iterator() : current() {};
    explicit reverse_iterator( iterator_type x ): current(x) {};
    template< class U >
    reverse_iterator( const reverse_iterator<U>& other ): current(other.current) {};

    iterator_type base() const {return current; };

    reference operator*() const {
        Iter tmp = current;
        return *--tmp;
    };

    pointer operator->() const {
        Iter tmp = current;
        --tmp;
        return to_pointer(tmp);
    };

    reference operator[]( difference_type n ) const {
        return *(*this + n);
    };

    reverse_iterator& operator++(){
        --current;
        return *this;
    };

    reverse_iterator& operator--() {
        ++current;
        return *this;
    };

    reverse_iterator operator++( int ) {
        reverse_iterator tmp = *this;
        ++current;
        return tmp;
    };

    reverse_iterator operator--( int ) {
        reverse_iterator tmp = *this;
        ++current;
        return tmp;
    };

    reverse_iterator operator+( difference_type n ) const {
        return reverse_iterator(current - n);
    };

    reverse_iterator operator-( difference_type n ) const {
        return reverse_iterator(current + n);
    };

    reverse_iterator& operator+=( difference_type n ) {
        current -= n;
        return *this;
    }

    reverse_iterator& operator-=( difference_type n ) {
        current += n;
        return *this;
    };


 private:
    template<typename _Tp>
	static  _Tp* to_pointer(_Tp* __p) { return __p; }

    template<typename _Tp>
	static pointer to_pointer(_Tp __t) { return __t.operator->(); }

};

template< class Iterator1, class Iterator2 >
bool operator==( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs ) {
                    return lhs.base() == rhs.base();
                 };

template< class Iterator1, class Iterator2 >
bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs ) {
                    return lhs.base() != rhs.base();
                 };

template< class Iterator1, class Iterator2 >
bool operator<( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs ) {
                    return lhs.base() > rhs.base();
                 };

template< class Iterator1, class Iterator2 >
bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs ) {
                    return lhs.base() >= rhs.base();
                 };

template< class Iterator1, class Iterator2 >
bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs ) {
                    return lhs.base() < rhs.base();
                 };

template< class Iterator1, class Iterator2 >
bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs ) {
                    return lhs.base() <= rhs.base();
                 };


template< class Iter >
reverse_iterator<Iter>
     operator+( typename reverse_iterator<Iter>::difference_type n,
                const reverse_iterator<Iter>& it ) {
                    return reverse_iterator<Iter>(it.base() - n);
                };

template< class Iterator1, class Iterator2 >
typename reverse_iterator<Iterator1>::difference_type
    operator-( const reverse_iterator<Iterator1>& lhs,
               const reverse_iterator<Iterator2>& rhs ) {
                    return rhs.base() - lhs.base();
               };













}; //ft

#endif //__FT_ITERATORs__