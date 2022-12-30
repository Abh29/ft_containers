#ifndef __FT_MAP__
#define __FT_MAP__


#include <stdexcept>
#include "ft_utils.hpp"
#include "ft_iterators.hpp"
#include "ft_RBTree.hpp"


namespace ft {

template< class Key, class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<ft::pair<const Key, T> >
>
class map {

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


   
    typedef Compare                                                                     key_compare;
    typedef Allocator                                                                   allocator_type;
    typedef value_type&                                                                 reference;
    typedef const value_type&                                                           const_reference;
    typedef typename Allocator::pointer                                                 pointer;
    typedef typename Allocator::const_pointer                                           const_pointer;
    typedef typename Red_Black_Tree<value_type, value_compare>::iterator                iterator;
    typedef typename Red_Black_Tree<value_type, value_compare>::const_iterator          const_iterator;
    typedef typename Red_Black_Tree<value_type, value_compare>::reverse_iterator        reverse_iterator;
    typedef typename Red_Black_Tree<value_type, value_compare>::const_reverse_iterator  const_reverse_iterator;


private:
    allocator_type                                      _allocator;
    key_compare                                         _compare;
    Red_Black_Tree<value_type, value_compare>           _c;


public:
    //constructor
    map():
    _allocator(),
    _compare(),
    _c(value_compare(_compare))
    {};

    explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) :
    _allocator(alloc),
    _compare(comp),
    _c(value_compare(_compare))
    {};

    //TODO: check the iterator's type
    template< class InputIt >
    map(    InputIt first, InputIt last,   
            const Compare& comp = Compare(), 
            const Allocator& alloc = Allocator(),
			typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = ft_nullptr):
    _allocator(alloc),
    _compare(comp),
    _c(value_compare(_compare))
    {
        this->insert(first, last);
    };

    map(const map& other ):
    _allocator(other._allocator),
    _compare(other._compare),
    _c(other._c)
    {
        // _c = other._c;
    };

    virtual ~map() {this->clear(); };

    map& operator=( const map& other ) {
        if (this == &other)
            return (*this);
        this->clear();
        _c = other._c;
        return (*this);
    };


	allocator_type get_allocator() const {
        return _allocator;
    };

    //Element access
     T& at( const Key& key ) {
		iterator it = this->find(key);
		if (it == this->end())
			throw std::out_of_range("");
		return it->second;
	 }

	 const T& at( const Key& key ) const {
		 const_iterator it = this->find(key);
		 if (it == this->end())
			 throw std::out_of_range("");
		 return it->second;
	 };

    T& operator[]( const Key& key ) {
        iterator it = this->find(key);
        if (it == this->end()) {
			this->insert(ft::make_pair(key, T()));
			it = this->find(key);
		}
		return it->second;
    };

    //Iterator
    iterator begin() {return _c.begin(); };
    const_iterator begin() const {return _c.begin();};
    iterator end() {return _c.end(); };
    const_iterator end() const {return _c.end(); };
    reverse_iterator rbegin() { return _c.rbegin(); };
    const_reverse_iterator rbegin() const {return _c.rbegin(); };
    reverse_iterator rend() {return _c.rend(); };
    const_reverse_iterator rend() const {return _c.rend(); };

    //Capacity
    bool empty() const {return _c.is_empty(); };
    size_type size() const {return _c.size(); };
    size_type max_size() const {return _c.max_size(); };

    //Modifiers
    void clear() {_c.clear(); };

    ft::pair<iterator, bool> insert( const value_type& value ) { 
        return _c.insert(value);
    };

    iterator insert( iterator pos, const value_type& value ) {
        (void) pos;
        return _c.insert(value).first;
    };

    //TODO: check the iterator's category
    template< class InputIt >
    void insert( InputIt first, InputIt last,
    typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type* = ft_nullptr) {
		while (first != last) {
            _c.insert(*first);
            ++first;
        }
    };

    void erase( iterator pos ) {
		assert(pos != end());
        _c.remove(*pos);
    };

    void erase( iterator first, iterator last ) {
		if (first == begin() && last == end())
			clear();
		else
        	while (first != last)
            	_c.remove(*first++);
    };

    size_type erase( const Key& key ) {
        return _c.remove(ft::pair<key_type, mapped_type>(key, mapped_type()));
    };

    void swap( map& other ) {
        allocator_type  tmp_a = _allocator;
        key_compare     tmp_c = _compare;

        _c.swap(other._c);

        _allocator = other._allocator;
        _compare = other._compare;

        other._allocator = tmp_a;
        other._compare = tmp_c;
    };

    //Lookup
    size_type count( const Key& key ) const {
        return (_c.find(ft::make_pair(key, mapped_type())) != _c.end());
    };

    iterator find( const Key& key ) {
        return _c.find(ft::pair<key_type, mapped_type>(key, mapped_type()));
    };

	const_iterator find( const Key& key ) const {
        return const_iterator(this->find(key).base());
    };

    ft::pair<iterator,iterator> equal_range( const Key& key ) {
        return ft::make_pair(this->lower_bound(key), this->upper_bound(key));
    };	

    ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
        return ft::make_pair(this->lower_bound(key), this->upper_bound(key));
    };

	//TODO: check T() ?
    iterator lower_bound( const Key& key ) {
		if (empty())
			return end();
        return _c.lower_bound(ft::make_pair(key, begin()->second));
    };

    const_iterator lower_bound( const Key& key ) const {
		if (empty())
			return end();
		return _c.lower_bound(ft::make_pair(key, begin()->second));
    };

    iterator upper_bound( const Key& key ) {
		if (empty())
			return end();
       return _c.upper_bound(ft::make_pair(key, begin()->second));
    };

    const_iterator upper_bound( const Key& key ) const {
		if (empty())
			return end();
		return _c.lower_bound(ft::make_pair(key, begin()->second));
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
                    return ft::equal<typename ft::map<Key,T,Compare,Alloc>::const_iterator ,
                             typename ft::map<Key,T,Compare,Alloc>::const_iterator> (
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
							typename ft::map<Key,T,Compare,Alloc>::const_iterator ,
							typename ft::map<Key,T,Compare,Alloc>::const_iterator> (
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

namespace std {
	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs,
			   ft::map<Key,T,Compare,Alloc>& rhs ) {
		ft::swap(lhs, rhs);
	};
}




#endif //__FT_MAP__