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
    typedef Compare                                                                 key_compare;
    typedef Allocator                                                               allocator_type;
    typedef value_type&                                                             reference;
    typedef const value_type&                                                       const_reference;
    typedef typename Allocator::pointer                                             pointer;
    typedef typename Allocator::const_pointer                                       const_pointer;
    typedef typename Red_Black_Tree<value_type>::iterator            iterator;
    typedef typename Red_Black_Tree<const value_type>::iterator      const_iterator;
    typedef ft::reverse_iterator<iterator>                                          reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>                                    const_reverse_iterator;     


private:
    allocator_type  _allocator;
    key_compare     _compare;
    pointer         _root;


    class value_compare {

        public:
            typedef bool                result_type;
            typedef value_type          first_argument_type;
            typedef value_type          second_argument_type;

        protected:
            Compare                     comp;

            value_compare( Compare c ): comp(c) {};
    
        public:
            bool operator()( const value_type& lhs, const value_type& rhs ) const {
                return comp(lhs.first, rhs.first);
            };
	
    };

public:
    //constructor
    map();
    explicit map( const Compare& comp, const Allocator& alloc = Allocator() );
    template< class InputIt >
    map(    InputIt first, InputIt last,   
            const Compare& comp = Compare(), 
            const Allocator& alloc = Allocator() );
    map( const map& other );
    ~map();

    map& operator=( const map& other );
	allocator_type get_allocator() const;

    //Element access
    T& at( const Key& key );
	const T& at( const Key& key ) const;
    T& operator[]( const Key& key );

    //Iterator
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;

    //Capacity
    bool empty() const;
    size_type size() const;
    size_type max_size() const;

    //Modifiers
    void clear();
    std::pair<iterator, bool> insert( const value_type& value );
    iterator insert( iterator pos, const value_type& value );
    template< class InputIt >
    void insert( InputIt first, InputIt last );
    void erase( iterator pos );
    void erase( iterator first, iterator last );
    size_type erase( const Key& key );
    void swap( map& other );

    //Lookup
    size_type count( const Key& key ) const;
    iterator find( const Key& key );
	const_iterator find( const Key& key ) const;
    std::pair<iterator,iterator> equal_range( const Key& key );	
    std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;
    iterator lower_bound( const Key& key );
    const_iterator lower_bound( const Key& key ) const;
    iterator upper_bound( const Key& key );
    const_iterator upper_bound( const Key& key ) const;

    //Observers
    key_compare key_comp() const;
	value_compare value_comp() const;



};

template< class Key, class T, class Compare, class Alloc >
void swap( ft::map<Key,T,Compare,Alloc>& lhs,
           ft::map<Key,T,Compare,Alloc>& rhs );

template< class Key, class T, class Compare, class Alloc >
bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs );
	
template< class Key, class T, class Compare, class Alloc >
bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs );

template< class Key, class T, class Compare, class Alloc >
bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
                const ft::map<Key,T,Compare,Alloc>& rhs );

template< class Key, class T, class Compare, class Alloc >
bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs );

template< class Key, class T, class Compare, class Alloc >
bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
                const ft::map<Key,T,Compare,Alloc>& rhs );

template< class Key, class T, class Compare, class Alloc >
bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs );











}




#endif //__FT_MAP__