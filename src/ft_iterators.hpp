#pragma once
#ifndef __FT_ITERATORs__
#define __FT_ITERATORs__

#include "ft_utils.hpp"
#include <cstddef>
#include <memory>


namespace ft {

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

        typedef T*                  iterator_type;
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
        template<class Itr>
        iterator(const Itr& other,
                 typename ft::enable_if<ft::is_iterator<Itr>::value, Itr>::type* = ft_nullptr):
                _elm(other) {};

        iterator& operator= (const iterator& other) {
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

        operator pointer() const { return _elm; }

    };


//random access iterator

    template<class T>
struct random_access_iterator: public ft::iterator< typename ft::iterator_traits<T*>::iterator_category, T> {

    public:

        typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category     iterator_category;
        typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type            value_type;
        typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type       difference_type;
        typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer               pointer;
        typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference             reference;


        random_access_iterator(): iterator<iterator_category, value_type>() {};
        random_access_iterator(pointer elm): iterator<iterator_category, value_type>(elm) {};
        random_access_iterator(const random_access_iterator& other): iterator<iterator_category, value_type>(other) {};
        template<class Iterator>
        random_access_iterator(const Iterator& other ,
                               typename ft::enable_if<ft::is_iterator<Iterator>::value, Iterator>::type* = ft_nullptr):
                iterator<iterator_category, value_type>(other) {
//        this->_elm = other;
        };


        random_access_iterator& operator=(const random_access_iterator &other){
            iterator<iterator_category, value_type>::operator=(other);
            return *this;
        };

        template<class Itr>
        random_access_iterator& operator=(const Itr& other) {
            this->_elm = other.base();
            return *this;
        }


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

    private:
        Iter        current;

    public:

        reverse_iterator() : current() {};
        explicit reverse_iterator( iterator_type x ): current(x) {};
        template< class U >
        reverse_iterator( const reverse_iterator<U>& other ): current(other.base()) {};

        iterator_type base() const {return current; };

        reference operator*() const {
            Iter tmp = current;
            return *(--tmp);
        };

        pointer operator->() const {
            Iter tmp = current;
            --tmp;
            return to_pointer(tmp);
        };

        reference operator[]( difference_type n ) const {
            return base()[-n-1];
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

        operator pointer() const { return current; }

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
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, Node>::pointer                                    node_pointer;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, Node>::reference                                  node_reference;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, typename Node::value_type>::pointer               pointer;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, typename Node::value_type>::reference             reference;
        typedef Compare                                                                                                 comparator;

    protected:
        node_pointer    _nil;

    public:

        RBIterator(const node_pointer _elm, const node_pointer _nil):
                ft::iterator<ft::bidirectional_iterator_tag, Node>(_elm),
                _nil(_nil)
        {}

        RBIterator(const node_pointer _nil = ft_nullptr):
                ft::iterator<ft::bidirectional_iterator_tag, Node>(_nil),
                _nil(_nil)
        {};

        RBIterator(const RBIterator& other):
                ft::iterator<ft::bidirectional_iterator_tag, Node>(other),
                _nil(other._nil)
        {};

//    template<class T, class C>
//    RBIterator(const RBIterator<T, C>& other):
//    ft::iterator<ft::bidirectional_iterator_tag, T>(other),
//    _comp(other.compare())
//    {};

        virtual ~RBIterator() {};

        RBIterator& operator=(const RBIterator& other) {
            this->_elm = other._elm;
            this->_nil= other._nil;
            return *this;
        };


        reference operator*() const {
            return this->_elm->data;
        };

        pointer operator->() const {
            return &(operator*());
        }

        node_pointer base() const {
            return ft::iterator<ft::bidirectional_iterator_tag, Node>::base();
        }

        node_pointer nil() const {
            return _nil;
        }

        RBIterator& operator++() {
            node_pointer tmp = this->_elm;
            this->_elm =  &(*_nil);

            if (!tmp)
                return *this;

            if (tmp->right != _nil) {
                tmp = tmp->right;
                while (tmp->left != _nil)
                    tmp = tmp->left;
                this->_elm = tmp;
            } else {
                // using the cast operator T()
                while (tmp->parent != _nil){
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


        RBIterator& operator--() {
            node_pointer tmp = this->_elm;
            this->_elm = _nil;

            if (!tmp)
                return *this;

            if (tmp->left != _nil) {
                tmp = tmp->left;
                while (tmp->right != _nil)
                    tmp = tmp->right;
                this->_elm = tmp;
            } else {
                while (tmp->parent != _nil){
                    if (tmp->parent->right == tmp){
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

        operator node_pointer () const {
            return base();
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



// RedBlackTree Iterator
    template<class Node, class Compare = ft::less<Node>() >
    class RBConstIterator: public ft::iterator<ft::bidirectional_iterator_tag, const Node> {

    public:

        typedef typename ft::iterator<ft::bidirectional_iterator_tag, Node>::iterator_category                          iterator_category;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, Node>::value_type                                 value_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, Node>::difference_type                            difference_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, const Node>::pointer                              node_pointer;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, const Node>::reference                            node_reference;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, typename Node::value_type const>::pointer         pointer;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, typename Node::value_type const>::reference       reference;
        typedef Compare                                                                                                 comparator;

    protected:
        node_pointer    _nil;

    public:

        RBConstIterator(const node_pointer _elm, const node_pointer _nil):
                ft::iterator<ft::bidirectional_iterator_tag, const Node>(_elm),
                _nil(_nil)
        {}

        RBConstIterator(const node_pointer _nil = ft_nullptr):
                ft::iterator<ft::bidirectional_iterator_tag, const Node>(_nil),
                _nil(_nil)
        {};

        RBConstIterator(const RBConstIterator& other):
                ft::iterator<ft::bidirectional_iterator_tag, const Node>(other),
                _nil(other._nil)
        {};

        RBConstIterator(const RBIterator<Node, Compare>& other):
                ft::iterator<ft::bidirectional_iterator_tag, const Node>(other)
        {
            _nil = const_cast<const Node*>(other.nil());
        };


        virtual ~RBConstIterator() {};

        RBConstIterator& operator=(const RBConstIterator& other) {
            this->_elm = other._elm;
            this->_nil = other._nil;
            return *this;
        };


        reference operator*() const {
            return this->_elm->data;
        };

        pointer operator->() const {
            return &(operator*());
        }

        pointer base() const {
            return  &(this->_elm->data);
        }

        node_pointer nil() const {
            return _nil;
        }


        RBConstIterator& operator++() {
            node_pointer tmp = this->_elm;
            this->_elm = _nil;

            if (tmp->right != _nil) {
                tmp = tmp->right;
                while (tmp->left != _nil)
                    tmp = tmp->left;
                this->_elm = tmp;
            } else {
                // using the cast operator T()
                while (tmp->parent != _nil){
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


        RBConstIterator operator++(int) {
            RBConstIterator out(*this);
            operator++();
            return out;
        }


        RBConstIterator& operator--() {
            node_pointer tmp = this->_elm;
            this->_elm = _nil;

            if (tmp->left != _nil) {
                tmp = tmp->left;
                while (tmp->right != _nil)
                    tmp = tmp->right;
                this->_elm = tmp;
            } else {
                while (tmp->parent != _nil){
                    if (tmp->parent->right == tmp){
                        this->_elm = tmp->parent;
                        break;
                    }
                    tmp = tmp->parent;
                }
            }
            return *this;
        };


        RBConstIterator operator--(int) {
            RBConstIterator out(*this);
            operator--();
            return out;
        }

        bool operator==(const RBConstIterator& other) {
            return base() == other.base();
        }

        bool operator!=(const RBConstIterator& other) {
            return base() != other.base();
        }

    };


    template<class Node1, class Node2>
    bool operator==( const ft::RBConstIterator<Node1>& lhs,
                     const ft::RBConstIterator<Node2>& rhs) {
        return (lhs.base() == rhs.base());
    };

    template<class Node1, class Node2>
    bool operator!=( const ft::RBConstIterator<Node1>& lhs,
                     const ft::RBConstIterator<Node2>& rhs) {
        return (lhs.base() != rhs.base());
    };





}; //ft

#endif //__FT_ITERATORs__