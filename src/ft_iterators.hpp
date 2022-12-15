#pragma once
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
        first = other.first;
        second = other.second;
        return *this;
    };
};

template< class T1, class T2 >
bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
    // return (lhs.first == rhs.first) && (lhs.second == rhs.second);
    return lhs.first == rhs.first;
};

template< class T1, class T2 >
bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
    return !(lhs == rhs);
};

template< class T1, class T2 >
bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
    // if (lhs.first == rhs.first)
    //     return lhs.second < rhs.second;
    // return lhs.first < rhs.second;
    return lhs.first < rhs.first;
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

    iterator() : _elm(ft::ft_nullptr) {};
    iterator(pointer elm): _elm(elm) {};
    iterator(const iterator& other) : _elm(other._elm) {};
    iterator& operator= (const iterator& other) {
        if (other == *this)
            return *this;
        _elm = other._elm;
        return *this;
    }

    virtual ~iterator() {};

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

    iterator operator++ (int) {
        iterator tmp = *this;
        ++_elm;
        return tmp;
    }

};


//random access iterator

template<class T>
struct random_access_iterator: public ft::iterator<ft::random_access_iterator_tag, T> {

public:
    typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category     iterator_category;
    typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type            value_type;
    typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type       difference_type;
    typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer               pointer;
    typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference             reference;


    random_access_iterator(): iterator<iterator_category, value_type>() {};
    random_access_iterator(pointer elm): iterator<iterator_category, value_type>(elm) {};
    random_access_iterator(const random_access_iterator& other): iterator<iterator_category, value_type>(other) {};

    random_access_iterator& operator=(const random_access_iterator &other){
        iterator<iterator_category, value_type>::operator=(other);
        return *this;
    };


    virtual ~random_access_iterator() {};

    pointer base() const { return iterator<iterator_category, value_type>::base(); };

    void swap(random_access_iterator& a, random_access_iterator& b) {
        iterator<iterator_category, value_type>::swap(a, b);
    };

    reference   operator*(void) const {
        return this->iterator<iterator_category, value_type>::operator*();
    };

    pointer     operator->(void) {
        return this->iterator<iterator_category, value_type>::operator->();
    };

    random_access_iterator& operator++() {
        this->iterator<iterator_category, value_type>::operator++();
        return *this;
    }

    random_access_iterator operator++(int) {
        random_access_iterator tmp = *this;
        operator++();
        return tmp;
    }


    random_access_iterator& operator--() {
        --(this->_elm);
        return *this;
    }

    random_access_iterator operator--(int) {
        random_access_iterator tmp = *this;
        --(this->_elm);
        return tmp;
    }

    random_access_iterator& operator+=(difference_type n) {
        this->_elm += n;
        return *this;
    }

    random_access_iterator operator+(difference_type n) const {
        return random_access_iterator(this->_elm + n);
    }

    random_access_iterator operator-(difference_type n) const {
        return random_access_iterator(this->_elm - n);
    }

    random_access_iterator& operator-=(difference_type n) {
        this->_elm -= n;
        return *this;
    }


    reference operator[](difference_type n) {
        return *(*this + n);
    }

};


template<class T>
ft::random_access_iterator<T> operator+(
    typename ft::random_access_iterator<T>::difference_type n, 
    const ft::random_access_iterator<T>& it
    ) { return it + n; };


template<class T>
typename ft::random_access_iterator<T>::difference_type 
operator-(  const ft::random_access_iterator<T> lhs,
            const ft::random_access_iterator<T> rhs) {
                return (lhs.base() - rhs.base());
            };

//TODO: change these to refrences
template<class Iterator1, class Iterator2 >
bool operator==( const ft::random_access_iterator<Iterator1>& lhs,
                 const ft::random_access_iterator<Iterator2>& rhs ) {
                    return lhs.base() == rhs.base();
                 };

template<class Iterator1, class Iterator2>
bool operator!=( const ft::random_access_iterator<Iterator1> lhs,
                 const ft::random_access_iterator<Iterator2> rhs) {
                        return !(lhs == rhs);
                    };

template<class Iterator1, class Iterator2>
bool operator<( const ft::random_access_iterator<Iterator1> lhs,
                const ft::random_access_iterator<Iterator2> rhs) {
                    return (lhs.base() < rhs.base());
                };

template<class Iterator1, class Iterator2>
bool operator<=( const ft::random_access_iterator<Iterator1> lhs,
                const ft::random_access_iterator<Iterator2> rhs) {
                    return (lhs.base() <= rhs.base());
                };

template<class Iterator1, class Iterator2>
bool operator>( const ft::random_access_iterator<Iterator1> lhs,
                const ft::random_access_iterator<Iterator2> rhs) {
                    return (lhs.base() > rhs.base());
                };

template<class Iterator1, class Iterator2>
bool operator>=( const ft::random_access_iterator<Iterator1> lhs,
                const ft::random_access_iterator<Iterator2> rhs) {
                    return (lhs.base() >= rhs.base());
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



// RedBlackTree Iterator
template<class Node, class Compare = ft::less<Node>() >
class RBIterator: public ft::iterator<ft::bidirectional_iterator_tag, Node> {

public:

    typedef typename ft::iterator<ft::bidirectional_iterator_tag, Node>::iterator_category                          iterator_category;
    typedef typename ft::iterator<ft::bidirectional_iterator_tag, Node>::value_type                                 value_type;
    typedef typename ft::iterator<ft::bidirectional_iterator_tag, Node>::difference_type                            difference_type;
    typedef typename ft::iterator<ft::bidirectional_iterator_tag, Node>::pointer                                    pointer;
    typedef typename ft::iterator<ft::bidirectional_iterator_tag, Node>::reference                                  reference;
    typedef typename ft::iterator<ft::bidirectional_iterator_tag, typename Node::value_type>::pointer               value_pointer;
    typedef typename ft::iterator<ft::bidirectional_iterator_tag, typename Node::value_type>::reference             value_reference;
    typedef Compare                                                                                                 comparator;

protected:
    comparator      _comp;

public:

    RBIterator(const pointer _elm, const comparator& comp = comparator()):
    ft::iterator<ft::bidirectional_iterator_tag, Node>(_elm),
    _comp(comp)
    {}

    RBIterator(const comparator& comp = comparator()):
    ft::iterator<ft::bidirectional_iterator_tag, Node>(),
    _comp(comp)
    {};


    RBIterator(const RBIterator& other):
    ft::iterator<ft::bidirectional_iterator_tag, Node>(other),
    _comp(other._comp)
    {};

    virtual ~RBIterator() {};

    RBIterator& operator=(const RBIterator& other) {
        this->_elm = other._elm;
        this->_comp = other._comp;
        return *this;
    };


    value_reference operator*() const {
        return this->_elm->data;
    };

    value_pointer operator->() const {
        return &(operator*());
    }

    pointer base() const {
        return ft::iterator<ft::bidirectional_iterator_tag, Node>::base();
    }

    RBIterator& operator++() {
        pointer tmp = this->_elm;
        this->_elm = ft_nullptr;

        if (tmp->right) {
            tmp = tmp->right;
            while (tmp->left)
                tmp = tmp->left;
            this->_elm = tmp;
        } else {
            // using the cast operator T()
            while (tmp->parent){
                // if (_comp(*tmp, *tmp->parent)){
                if (tmp->parent->left == tmp){
                    this->_elm = tmp->parent;
                    break;
                }
                tmp = tmp->parent;
            }
        }
        return *this;
    };


    RBIterator operator++(int) {
        RBIterator out(*this);
        operator++();
        return out;
    }

    //TODO: fix this !
    RBIterator& operator--() {
        pointer tmp = this->_elm;
        this->_elm = ft_nullptr;

        if (tmp->left) {
            tmp = tmp->left;
            while (tmp->right)
                tmp = tmp->right;
            this->_elm = tmp;
        } else {
            while (tmp->parent){
                if (_comp(*tmp->parent, *tmp)){
                    this->_elm = tmp->parent;
                    break;
                }
                tmp = tmp->parent;
            }
        }
        return *this;
    };


    RBIterator operator--(int) {
        RBIterator out(*this);
        operator--();
        return out;
    }

    bool operator==(const RBIterator& other) {
        return base() == other.base();
    }

    bool operator!=(const RBIterator& other) {
        return base() != other.base();
    }

};


template<class Node1, class Node2>
bool operator==( const ft::RBIterator<Node1>& lhs,
                const ft::RBIterator<Node2>& rhs) {
                    return (lhs.base() == rhs.base());
                };

template<class Node1, class Node2>
bool operator!=( const ft::RBIterator<Node1>& lhs,
                const ft::RBIterator<Node2>& rhs) {
                    return (lhs.base() != rhs.base());
                };









}; //ft

#endif //__FT_ITERATORs__