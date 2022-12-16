#ifndef __FT_SET__
#define __FT_SET__


#include <stdexcept>
#include "ft_utils.hpp"
#include "ft_iterators.hpp"
#include "ft_RBTree.hpp"


namespace ft {

template< class Key,
    	class Compare = std::less<Key>,
    	class Allocator = std::allocator<Key>> 
		class set {


public:

	typedef Key																	key_type;
	typedef Key																	value_type;
	typedef	std::size_t															size_type;
	typedef	std::ptrdiff_t														difference_type;
	typedef	Compare																key_compare;
	typedef	Compare																value_compare;
	typedef Allocator															allocator_type;
	typedef value_type&															reference;
	typedef	const value_type&													const_reference;
	typedef typename Allocator::pointer											pointer;
	typedef typename Allocator::const_pointer									const_pointer;
	typedef	typename Red_Black_Tree<value_type, value_compare>::iterator		iterator;
	typedef typename Red_Black_Tree<const value_type, value_compare>::iterator	const_iterator;
	typedef ft::reverse_iterator<iterator>										reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>								const_reverse_iterator;


private:
	allocator_type 										_allocator;
	key_compare											_compare;
	Red_Black_Tree<value_type, value_compare> 			_c;


public:
	//constructor
	set() : 
	_allocator(),
	_compare(),
	_c(_compare)
	{};

	explicit set( const Compare& comp, const Allocator& alloc = Allocator() ) :
    _allocator(alloc),
    _compare(comp),
    _c(_compare)
    {};

	template< class InputIt >
	set( InputIt first, InputIt last,
		const Compare& comp = Compare(),
		const Allocator& alloc = Allocator() ) :
    _allocator(alloc),
    _compare(comp),
    _c(value_compare(_compare))
    {
        this->insert(first, last);
    };
	
	set( const set& other ) :
    _allocator(other._allocator),
    _compare(other._compare),
    _c(other._c)
    {};

	virtual ~set() {
		this->clear();
	};

	set& operator=( const set& other ) {
		if (this == &other)
            return (*this);
        this->clear();
		_allocator = other._allocator;
		_compare = other._compare;
        _c = other._c;
        return (*this);
	};

	allocator_type get_allocator() const {
		return _allocator;
	};

	//iterator
	iterator begin() {return _c.begin(); };
    const_iterator begin() const {return const_iterator(_c.min()); };
    iterator end() {return _c.end(); };
    const_iterator end() const {return const_iterator(ft_nullptr); };
    reverse_iterator rbegin() { return reverse_iterator(this->end()); };
    const_reverse_iterator rbegin() const {const_reverse_iterator(this->end()); };
    reverse_iterator rend() {return reverse_iterator(this->begin()); };
    const_reverse_iterator rend() const {return const_reverse_iterator(this->begin()); };

	//Capacity
    bool empty() const {return _c.empty(); };
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

	//TODO: check iterator's category
	template< class InputIt >
	void insert( InputIt first, InputIt last ) {
		while (first != last) {
            _c.insert(*first);
            ++first;
        }
	};

	void erase( iterator pos ) {
		_c.remove(*pos);
	};

	void erase( iterator first, iterator last ) {
		while (first != last) {
			_c.remove(*first);
			++first;
		}
	};

	size_type erase( const Key& key ) {
		return _c.remove(key);
	};

	void swap( set& other ) {
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
		return _c.find(key) != _c.end();
	};

	iterator find( const Key& key ) {
		return _c.find(key);
	};

	const_iterator find( const Key& key ) const {
		return const_iterator(_c.find(key).base());
	};

	ft::pair<iterator,iterator> equal_range( const Key& key ) {
		return ft::make_pair(this->lower_bound(key), this->upper_bound(key));
	};

	ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
		return ft::make_pair(this->lower_bound(key), this->upper_bound(key));
	};

	iterator lower_bound( const Key& key ) {
		iterator b = this->begin();
        iterator e = this->end();

        while (b != e) {
            if (!_compare(*b, key))
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
            if (_compare(key, *b))
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
		return value_compare();
	};

};

template< class Key, class Compare, class Alloc >
void swap( ft::set<Key,Compare,Alloc>& lhs,
           ft::set<Key,Compare,Alloc>& rhs ) {
				lhs.swap(rhs);
		   };

template< class Key, class Compare, class Alloc >
bool operator==( const ft::set<Key,Compare,Alloc>& lhs,
                 const ft::set<Key,Compare,Alloc>& rhs ) {
					if (lhs.size() != rhs.size())
                        return false;
                    return ft::equal<ft::set<Key,Compare,Alloc>::iterator, 
                            ft::set<Key,Compare,Alloc>::iterator> (
                                lhs.begin(),
                                lhs.end(),
                                rhs.begin()
                            );
				 };

template< class Key, class Compare, class Alloc >
bool operator!=( const ft::set<Key,Compare,Alloc>& lhs,
                 const ft::set<Key,Compare,Alloc>& rhs ) {
					return !(lhs == rhs);
				 };

template< class Key, class Compare, class Alloc >
bool operator<( const ft::set<Key,Compare,Alloc>& lhs,
                const ft::set<Key,Compare,Alloc>& rhs ) {
					return ft::lexicographical_compare<
                                ft::set<Key,Compare,Alloc>::iterator, 
                                ft::set<Key,Compare,Alloc>::iterator> (
                                    lhs.begin(), lhs.end(),
                                    rhs.begin(), rhs.end()
                                );
				};

template< class Key, class Compare, class Alloc >
bool operator<=( const ft::set<Key,Compare,Alloc>& lhs,
                 const ft::set<Key,Compare,Alloc>& rhs ) {
					return !(rhs < lhs);
				 };

template< class Key, class Compare, class Alloc >
bool operator>( const ft::set<Key,Compare,Alloc>& lhs,
                const ft::set<Key,Compare,Alloc>& rhs ) {
					return rhs < lhs;
				};

template< class Key, class Compare, class Alloc >
bool operator>=( const ft::set<Key,Compare,Alloc>& lhs,
                 const ft::set<Key,Compare,Alloc>& rhs ) {
					return !(lhs < rhs);
				 };






}



#endif //__FT_SET__
