#ifndef __FT_MAP__
#define __FT_MAP__


#include <stdexcept>
#include "ft_utils.hpp"
#include "ft_iterators.hpp"
#include "ft_RBTree.hpp"


namespace ft {


template< class Key, class T,
    class Compare = ft::less<Key>,
    class Allocator = std::allocator<ft::pair<const Key, T> >
> class map {

public:

    typedef Key                                                                     key_type;
    typedef T                                                                       mapped_type;
    typedef typename ft::pair<const Key, T>                                         value_type;
    typedef std::size_t                                                             size_type;
    typedef std::ptrdiff_t                                                          difference_type;


     class value_compare {

        friend class map<Key, T, Compare, Allocator>;

        public:
            typedef bool                result_type;
            typedef value_type          first_argument_type;
            typedef value_type          second_argument_type;

        protected:
            Compare                     comp;
            
        public:
        
            value_compare( Compare c  = Compare()): comp(c) {};
            
            bool operator()( const value_type& lhs, const value_type& rhs ) const {
                return comp(lhs.first, rhs.first);
            };
	
    };


   
    typedef Compare                                                                 key_compare;
    typedef Allocator                                                               allocator_type;
    typedef value_type&                                                             reference;
    typedef const value_type&                                                       const_reference;
    typedef typename Allocator::pointer                                             pointer;
    typedef typename Allocator::const_pointer                                       const_pointer;
    typedef typename Red_Black_Tree<value_type, value_compare>::iterator            iterator;
    typedef typename Red_Black_Tree<const value_type, value_compare>::iterator      const_iterator;
    typedef ft::reverse_iterator<iterator>                                          reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>                                    const_reverse_iterator;     


private:
    allocator_type                              _allocator;
    key_compare                                 _compare;
    Red_Black_Tree<value_type, value_compare>         _RBT;


public:
    //constructor
    map():
    _allocator(),
    _compare(),
    _RBT(value_compare(_compare))
    {};

    explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) :
    _allocator(alloc),
    _compare(comp),
    _RBT()
    {};

    //TODO: check the iterator's type
    template< class InputIt >
    map(    InputIt first, InputIt last,   
            const Compare& comp = Compare(), 
            const Allocator& alloc = Allocator() ):
    _allocator(alloc),
    _compare(comp),
    _RBT()
    {
        this->insert(first, last);
    };

    map( const map& other ):
    _allocator(other._allocator),
    _compare(other._compare),
    _RBT(other._RBT)
    {};

    virtual ~map() {this->clear(); };

    map& operator=( const map& other ) {
        if (this == &other)
            return (*this);
        this->clear();
        this->insert(other.begin(), other.end());
        return (*this);
    };


	allocator_type get_allocator() const {
        return _allocator;
    };

    //Element access
    // T& at( const Key& key );
	// const T& at( const Key& key ) const;

    T& operator[]( const Key& key ) {
        iterator it = this->find(key);

        if (it == this->end())
            this->insert(ft::make_pair(key, T()));
        it = this->find(key);
        return it->second;
    };

    //Iterator
    iterator begin() {return _RBT.begin(); };
    const_iterator begin() const {return const_iterator(_RBT.min()); };
    iterator end() {return _RBT.end(); };
    const_iterator end() const {return const_iterator(ft_nullptr); };
    reverse_iterator rbegin() { return reverse_iterator(this->end()); };
    const_reverse_iterator rbegin() const {const_reverse_iterator(this->end()); };
    reverse_iterator rend() {return reverse_iterator(this->begin()); };
    const_reverse_iterator rend() const {return const_reverse_iterator(this->begin()); };

    //Capacity
    bool empty() const {return _RBT.empty(); };
    size_type size() const {return _RBT.size(); };
    size_type max_size() const {return _RBT.max_size(); };

    //Modifiers
    void clear() {_RBT.clear(); };

    ft::pair<iterator, bool> insert( const value_type& value ) { 
        return _RBT.insert(value);
    };

    iterator insert( iterator pos, const value_type& value ) {
        (void) pos;
        return _RBT.insert(value).first;
    };

    //TODO: check the iterator's category
    template< class InputIt >
    void insert( InputIt first, InputIt last ) {
        while (first != last)
            _RBT.insert(*first++);
    };

    void erase( iterator pos ) {
        _RBT.remove(*pos);
    };

    void erase( iterator first, iterator last ) {
        while (first != last)
            _RBT.remove(*first++);
    };

    size_type erase( const Key& key ) {
        return _RBT.remove(ft::pair<key_type, mapped_type>(key, mapped_type()));
    };

    void swap( map& other ) {
        allocator_type  tmp_a = _allocator;
        key_compare     tmp_c = _compare;

        _RBT.swap(other._RBT);

        _allocator = other._allocator;
        _compare = other._compare;

        other._allocator = tmp_a;
        other._compare = tmp_c;
    };

    //Lookup
    size_type count( const Key& key ) const {
        return _RBT.find(ft::pair<key_type, mapped_type>(key, mapped_type())) != _RBT.end();
    };

    iterator find( const Key& key ) {
        return _RBT.find(ft::pair<key_type, mapped_type>(key, mapped_type()));
    };

	const_iterator find( const Key& key ) const {
        return const_iterator(this->find(key).base());
    };

    ft::pair<iterator,iterator> equal_range( const Key& key ) {
        return make_pair(this->lower_bound(key), this->upper_bound(key));
    };	

    ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
        return make_pair(this->lower_bound(key), this->upper_bound(key));
    };

    iterator lower_bound( const Key& key ) {
        iterator b = this->begin();
        iterator e = this->end();

        while (b != e) {
            if (!_compare(b->first, key))
                break;
            ++b;
        }
        return b;
    };

    const_iterator lower_bound( const Key& key ) const {
        return const_iterator(this->lower_bound(key).base());
    };

    iterator upper_bound( const Key& key ) {
        iterator b = this->begin();
        iterator e = this->end();

        while (b != e) {
            if (_compare(key, b->first))
                break;
            ++b;
        }
        return b;
    };

    const_iterator upper_bound( const Key& key ) const {
        return const_iterator(this->upper_bound(key).base());
    };

    //Observers
    key_compare key_comp() const {
        return key_compare();
    };

	value_compare value_comp() const {
        return value_compare(key_compare());
    };



};

template< class Key, class T, class Compare, class Alloc >
void swap( ft::map<Key,T,Compare,Alloc>& lhs,
           ft::map<Key,T,Compare,Alloc>& rhs ) {
                lhs.swap(rhs);
           };

template< class Key, class T, class Compare, class Alloc >
bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs ) {
                    if (lhs.size() != rhs.size())
                        return false;
                    return ft::equal<ft::map<Key,T,Compare,Alloc>::iterator, 
                            ft::map<Key,T,Compare,Alloc>::iterator> (
                                lhs.begin(),
                                lhs.end(),
                                rhs.begin()
                            );
                 };
	
template< class Key, class T, class Compare, class Alloc >
bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs ) {
                    return !(lhs == rhs);
                 };

template< class Key, class T, class Compare, class Alloc >
bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
                const ft::map<Key,T,Compare,Alloc>& rhs ) {
                    return ft::lexicographical_compare<
                                ft::map<Key,T,Compare,Alloc>::iterator, 
                                ft::map<Key,T,Compare,Alloc>::iterator> (
                                    lhs.begin(), lhs.end(),
                                    rhs.begin(), rhs.end()
                                );
                };

template< class Key, class T, class Compare, class Alloc >
bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs ) {
                    return !(rhs < lhs);
                 };

template< class Key, class T, class Compare, class Alloc >
bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
                const ft::map<Key,T,Compare,Alloc>& rhs ) {
                    return rhs < lhs;
                };

template< class Key, class T, class Compare, class Alloc >
bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs ) {
                    return !(lhs < rhs);
                 };


}




#endif //__FT_MAP__