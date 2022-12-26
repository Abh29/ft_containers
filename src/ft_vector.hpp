#ifndef __FT_VECTOR__
#define __FT_VECTOR__


#include "ft_utils.hpp"
#include "ft_iterators.hpp"
#include <string.h>


namespace ft {



template<typename T, typename Allocator = std::allocator<T> > class vector {

public:
    //Member types  
    typedef T                                               value_type;
    typedef Allocator                                       allocator_type;
    typedef std::size_t                                     size_type;
    typedef std::ptrdiff_t                                  difference_type;
    typedef value_type&                                     reference;
    typedef const value_type&                               const_reference ;
    typedef typename Allocator::pointer                     pointer;
    typedef typename Allocator::const_pointer               const_pointer;
    typedef ft::random_access_iterator<value_type>          iterator;
    typedef ft::random_access_iterator<const value_type>    const_iterator;
    typedef ft::reverse_iterator<iterator>                  reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;

private:
        allocator_type  _allocator;
        pointer         _start;
        pointer         _end;
        pointer         _capacity;

public:

    //constructor
    vector() :
    _allocator(allocator_type()),
    _start(ft_nullptr),
    _end(ft_nullptr),
    _capacity(ft_nullptr)
    {}


    explicit vector( const Allocator& alloc) :
    _allocator(alloc),
    _start(ft_nullptr),
    _end(ft_nullptr),
    _capacity(ft_nullptr)
    {}


    explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()):
    _allocator(alloc),
    _start(_allocator.allocate(count)),
    _end(_start),
    _capacity(_start + count)
    {
        if (ft::is_integral<T>::value) {
            memset_v(_start, value, count, sizeof(T));
            _end += count;
        } else
            while (_end != _capacity)
                _allocator.construct(_end++, value);
    }


    template< class InputIt >
    vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(),
            typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = ft_nullptr):
    _allocator(alloc)
    {
        difference_type diff = ft::distance(first, last);
        _start = _allocator.allocate(diff);
        _capacity = _start + diff;
        _end = _start;
//        try {
//            _insert_range(_start, first, last);
//        } catch (...){
//            _allocator.deallocate(_start, diff);
//            _end = _start = _capacity = ft_nullptr;
//            throw;
//        }
        _insert_at(_start, first, last);
        _end += diff;
    };

    vector( const vector& other ):
    _allocator(other._allocator),
    _start(_allocator.allocate(other.size())),
    _end(_start),
    _capacity(_start + other.size())
    {
//        reserve(other.size());
        memcpy(_start, other._start, other.size() * sizeof(T));
        _end += other.size();
    };

    //destructor
    ~vector(){
        this->clear();
        _allocator.deallocate(_start, this->capacity());
    };

    //operator=
    vector& operator=( const vector& other ){
        if (other == *this)
            return *this;
        clear();
        insert(begin(), other.begin(), other.end());
        return *this;
    };

    //assign
    void assign( size_type count, const T& value ) {
        clear();
		_insert_count(_start, count, value);
    };

    template< class InputIt >
    void assign( InputIt first, InputIt last,
                 typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = ft_nullptr) {
        clear();
		_insert_range(_start, first, last);
    };

    //get_allocator
    allocator_type get_allocator() const;

    //Element access 
    reference at( size_type pos ) {
        if (pos >= size())
            throw std::out_of_range(ft::to_string(pos) + std::string(" >= this->size() \
            (which is ") + ft::to_string(this->size()) + std::string(")"));
        return *(_start + pos);
    };

    const_reference at( size_type pos ) const {
        if (pos >= size())
            throw std::out_of_range(ft::to_string(pos) + std::string(" >= this->size() \
            (which is ") + ft::to_string(this->size()) + std::string(")"));
        return *(_start + pos);
    };

    reference operator[]( size_type pos ) {
        return at(pos);
    }

    const_reference operator[]( size_type pos ) const {
        return at(pos);
    }

    reference front() {return (*_start); }
    const_reference front() const {return (*_start); };
    reference back() {return *(_end - 1); };
    const_reference back() const {return *(_end - 1); };

    T* data() {
        if (this->empty())
            return ft_nullptr;
        return (_start);
    };

    const T* data() const {
        if (this->empty())
            return ft_nullptr;
        return (_start);
    };

    //iterators
    iterator begin() {return iterator(_start); };
    const_iterator begin() const {return const_iterator(_start); };
    iterator end() {return iterator(_end); };
    const_iterator end() const {return const_iterator(_end); };
    reverse_iterator rbegin() {return reverse_iterator(_end); };
    const_reverse_iterator rbegin() const {return const_reverse_iterator(_end); };
    reverse_iterator rend() {return reverse_iterator(_start); };
    const_reverse_iterator rend() const {return const_reverse_iterator(_start);};

    //Capacity
    bool empty() const {return _start == _end ? true : false; };
    size_type size() const {
        // return distance(begin(), end()); 
        return _end - _start;
        // return distance(_start, _end);
    };
    size_type max_size() const {return allocator_type().max_size(); };
    void reserve( size_type new_cap ) {
        if (new_cap <= capacity())
            return;
        if (new_cap > max_size())
            throw std::length_error("new_cap > max_size allowed");
        
        pointer p_start = _start;
        pointer p_end = _end;
        _start = _allocator.allocate( new_cap );
        _end = _start;
        _capacity = _start + new_cap;
        _insert_at(_start, p_start, p_end);
        _end += (p_end - p_start);
        _allocator.deallocate(p_start, p_end - p_start);
    };
    size_type capacity() const {return ft::distance(_start, _capacity); };

    //Modifiers
    void clear(){
        if (ft::is_integral<T>::value)
            _end = _start;
        else
            while(_end != _start)
                _allocator.destroy(&*(--_end));
    };

    iterator insert(iterator pos, const T& value) {
        return _insert_val(pos, value);
    }

    void insert(iterator pos, size_type count, const T& value) {
        _insert_count(pos, count, value);
    }

    template< class InputIt >
    void insert(iterator pos, InputIt first, InputIt last,
                typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = ft_nullptr) {
        _insert_range(pos, first, last);
    };

    iterator erase( iterator pos ) {
        return _erase_pos(pos);
    };

    iterator erase( iterator first, iterator last ) {
        return _erase_range(first, last);
    };

    void push_back( const T& value ) {
        if (_end == _capacity)
		{
					int next_capacity = (this->size() > 0) ? (int)(this->size() * 2) : 1;
					this->reserve(next_capacity);
		}
		_allocator.construct(_end, value);
        _end++;
    };

    void pop_back() {
        _pop_back<T>();
    };

    void resize( size_type count, T value = T() ) {
		_resize(count, value);
    };

    void swap( vector& other ) {
        swap(_start, other._start);
        swap(_end, other._end);
        swap(_capacity, other._capacity);
    };

private:
    const_iterator const_begin() {return _start;};

    template<typename InputIt>
    void _insert_at(pointer pos, InputIt first, InputIt last, typename ft::enable_if<ft::_is_mem_cpy<InputIt>::value, InputIt>::type* = ft_nullptr) {
        size_type n = ft::distance(first, last);
        memcpy(pos, &(*first), n * sizeof(typename ft::iterator_traits<InputIt>::value_type));
    }

    template<typename InputIt>
    void _insert_at(pointer pos, InputIt first, InputIt last, typename ft::enable_if<!ft::_is_mem_cpy<InputIt>::value, InputIt>::type* = ft_nullptr) {
        while (first != last)
            _allocator.construct(pos++, *first++);
    }

    template< class InputIt >
    void _insert_range(iterator poss, InputIt first, InputIt last,
                typename ft::enable_if<!ft::_is_mem_cpy<InputIt>::value, InputIt>::type* = ft_nullptr) {
        if (first == last)
            return;
        difference_type count = ft::distance(first, last);
        pointer p;
        pointer pos = poss.base();
        if (size() + count > max_size())
            throw std::length_error("new_size > max_size allowed");
        if (size() + count <= capacity()) {
            p = _end += count;
            while (p - count != pos) {
                *p = *(p - count - 1);
                --p;
            }
            while (last != first)
                _allocator.construct(p--, *last--);
        } else {
            p = _start;
            size_type cap = Max(size() + count, 2 * size());
            pointer n_start = _allocator.allocate(cap);
            pointer n_end = n_start;
            try {
                while (p != pos)
                    *n_end++ = *p++;
                while (first != last)
                    _allocator.construct(n_end++, *first++);
                while (p != _end)
                    *n_end++ = *p++;
                _allocator.deallocate(_start, capacity());
                _start = n_start;
                _end = n_end;
                _capacity = _start + cap;
            } catch (...) {
                _allocator.deallocate(n_start, cap);
                throw;
            }
        }
    };

    template< class InputIt >
    void _insert_range(iterator pos, InputIt first, InputIt last,
                typename ft::enable_if<ft::_is_mem_cpy<InputIt>::value, InputIt>::type* = ft_nullptr) {
        if (first == last)
            return;
        difference_type count = ft::distance(first, last);
        pointer p = pos;
        if (count == 0)
            return;
        if (size() + count > max_size())
            throw std::length_error("new_size > max_size allowed");
        if (size() + count <= capacity()) {
            memmove(p + count, p, (_end - p) * sizeof(T));
            _end += count;
            _insert_at(p, first, last);
        } else {
            size_type p_cap = capacity();
            pointer p_start = _start;
            pointer p_end = _end;
            size_type cap = Max(size() + count, 2 * size());
            _start = _allocator.allocate(cap);
            _end = _start;
            _capacity = _start + cap;
            memcpy(_end, p_start, (pos - p_start) * sizeof(T));
            _end += (pos - p_start);
            _insert_at(_end, first, last);
            _end += count;
            memcpy(_end, pos, (p_end - pos)  * sizeof(T));
            _end += (p_end - pos);
            _allocator.deallocate(p_start, p_cap);
        }
    };

    template<class U>
    iterator _insert_val(iterator pos, const U& value, typename ft::enable_if<ft::is_integral<U>::value, U>::type* = ft_nullptr) {
        pointer p = pos;
        pointer out = ft_nullptr;

        if (capacity() > size()) {
            memmove(p + 1, p, (_end - p) * sizeof(T));
            _allocator.construct(p, value);
            ++_end;
            out = p;
        } else {
            pointer p_start = _start;
            pointer p_end = _end;
            difference_type p_cap = capacity();
            size_type cap = size() == 0 ? 1 : size() * 2;
            _start = _allocator.allocate(cap);
            _end = _start;
            _capacity = _start + cap;
            memcpy(_start, p_start, (p - p_start) * sizeof(T));
            _end += (p - p_start);
            _allocator.construct(_end, value);
            out = _end;
            memcpy(_end + 1, p, (p_end - p) * sizeof(T));
            _end += p_end - p + 1;
            _allocator.deallocate(p_start, p_cap);
        }
        return iterator(out);
    }

    template<class U>
    iterator _insert_val( iterator pos, const U& value, typename ft::enable_if<!ft::is_integral<U>::value, U>::type* = ft_nullptr) {
        pointer p = ft_nullptr;
        pointer out = ft_nullptr;

        if (capacity() > size()) {
            p = _end++;
            while (p != pos.base()) {
                *p = *(p - 1);
                --p;
            }
            _allocator.construct(p, value);
            out = p;
        } else {
            pointer p_start = p = _start;
            pointer p_end = _end;
            difference_type p_cap = capacity();
            size_type cap = size() == 0 ? 1 : size() * 2;
            _start = _allocator.allocate(cap);
            _end = _start;
            _capacity = _start + cap;
            while (p != pos.base())
                *_end++ = *p++;
            out = _end;
            _allocator.construct(_end++, value);
            while (p != p_end)
                *_end++ = *p++;
            _allocator.deallocate(p_start, p_cap);
        }
        return iterator(out);
    };

    template<class U>
    void _insert_count(iterator pos, size_type count, const U& value,
    typename ft::enable_if<ft::_is_mem_cpy<U*>::value, U>::type* = ft_nullptr) {
        pointer p = pos;
        if (count == 0)
            return;
        if (size() + count > max_size())
            throw std::length_error("new_size > max_size allowed");
        if (size() + count <= capacity()) {
            memmove(p + count, p, (_end - p) * sizeof(T));
            _end += count;
            memset_v(p, value, count, sizeof(T));
        } else {
            size_type p_cap = capacity();
            size_type cap = Max(this->size() + count, 2 * this->size());
            pointer p_start = _start;
            pointer p_end = _end;
            _start = _allocator.allocate(cap);
            _end = _start;
            _capacity = _start + cap;
            memcpy(_end, p_start, (pos - p_start) * sizeof(T));
            _end += (pos - p_start);
            memset_v(_end, value, count, sizeof(T));
            _end += count;
            memcpy(_end, pos, (p_end - pos) * sizeof(T));
            _end += p_end - pos;
            _allocator.deallocate(p_start, p_cap);
        }
    }

    template<class U>
    void _insert_count(iterator pos, size_type count, const U& value,
    typename ft::enable_if<!ft::_is_mem_cpy<U*>::value, U>::type* = ft_nullptr) {
        pointer p;
        if (count == 0)
            return;
        if (size() + count > max_size())
            throw std::length_error("new_size > max_size allowed");
        if (size() + count <= capacity()) {
            p = _end += count;
            while (p - count != pos.base()) {
                *p = *(p - count);
                --p;
            }
            while (count--)
                _allocator.construct(--p, value);
        } else {
            size_type p_cap = capacity();
            size_type cap = Max(this->size() + count, 2 * this->size());
            pointer p_start = p = _start;
            pointer p_end = _end;
            _start = _allocator.allocate(cap);
            _end = _start;
            _capacity = _start + cap;
            while (p != pos.base())
                *_end++ = *p++;
            while (count--)
                _allocator.construct(_end++, value);
            while (p != p_end)
                *_end++ = *p++;
            _allocator.deallocate(p_start, p_cap);
        }
    }


    template<class U>
    iterator _erase_pos(U pos, typename ft::enable_if<!ft::is_integral<typename ft::iterator_traits<U>::value_type>::value, U>::type* = ft_nullptr) {
        pointer p = pos;
        _allocator.destroy(p);
        while (++p != _end)
            *(p - 1) = *p;
        _end--;
        return pos;
    }

    template<class U>
    iterator _erase_pos(U pos, typename ft::enable_if<ft::is_integral<typename ft::iterator_traits<U>::value_type>::value, U>::type* = ft_nullptr) {
        pointer p = pos;
        memmove(p, pos + 1, (_end - pos) * sizeof(T));
        _end--;
        return pos;
    }

    template<class U>
    iterator _erase_range(U first, U last,
                          typename ft::enable_if<!ft::is_integral<typename ft::iterator_traits<U>::value_type>::value, U>::type* = ft_nullptr) {
        size_type count = distance((pointer)first, (pointer) last);
        pointer p = first;
        while (p != last)
            _allocator.destroy(p++);
        while (p != _end) {
            *(p - count) = *p;
            ++p;
        }
        _end -= count;
        return first;
    }

    template<class U>
    iterator _erase_range(U first, U last,
                          typename ft::enable_if<ft::is_integral<typename ft::iterator_traits<U>::value_type>::value, U>::type* = ft_nullptr) {
        size_type count = distance((pointer)first, (pointer) last);
        memmove(first, last, (_end - last) * sizeof(T));
        _end -= count;
        return first;
    }

    void swap(pointer& a, pointer& b) {
        pointer p = a;
        a = b;
        b = p;
    }

    template<class _T>
    void _pop_back(typename ft::enable_if<ft::is_integral<_T>::value, _T>::type* = ft_nullptr) {
        _end--;
    }

    template<class _T>
    void _pop_back(typename ft::enable_if<!ft::is_integral<_T>::value, _T>::type* = ft_nullptr) {
        _end--;
        _allocator.destroy(_end);
    }

	template<class U>
	void _resize( size_type count, U value = U(),
				  typename ft::enable_if<ft::is_integral<U>::value, U>::type* = ft_nullptr) {
		if (count > max_size())
			throw std::length_error("new_size > max_size allowed");
		if (count > capacity())
			reserve(Max(count, 2 * size()));
		if (count < size())
			_end -= (size() - count);
		if (count > size())
			insert(_end, count - size(), value);
	};

	template<class U>
	void _resize( size_type count, U value = U(),
				 typename ft::enable_if<!ft::is_integral<U>::value, U>::type* = ft_nullptr) {
		if (count > max_size())
			throw std::length_error("new_size > max_size allowed");
		if (count > capacity())
			reserve(Max(count, 2 * size()));
		if (count > size())
			insert(this->end(), count - size(), value);
		else {
			size_type diff = size() - count;
			while (diff--)
				_allocator.destroy(_end--);
		}
	};


};

 //Non-member functions
    template< class T, class Alloc >
    bool operator==( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
        // if (lhs.size() != rhs.size())
        //     return false;
        // typename ft::vector<T>::const_iterator it1 = lhs.begin();
        // typename ft::vector<T>::const_iterator it2 = rhs.begin();

        // while (it1 != lhs.end() && it2 != rhs.end())
        //     if (*it1++ != *it2++)
        //         return false;
        // if (it1 != lhs.end() || it2 != rhs.end())
        //     return false;
        // return true;
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    };

    template< class T, class Alloc >
    bool operator!=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
        return !(lhs == rhs);
    };

    template< class T, class Alloc >
    bool operator<( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    };

    template< class T, class Alloc >
    bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
        return !(rhs < lhs);
    };

    template< class T, class Alloc >
    bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
        return rhs < lhs;
    };

    template< class T, class Alloc >
    bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
        return rhs <= lhs;
    };   

    template< class T, class Alloc >
    void swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs ) {
        lhs.swap(rhs);
    };


}





#endif //__FT_VECTOR__