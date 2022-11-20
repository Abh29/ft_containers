#ifndef __FT_VECTOR__
#define __FT_VECTOR__




#include <algorithm>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
#include "ft_utils.hpp"

#define Max(a, b) (a > b ? a : b)


namespace ft {



template<typename T, typename Allocator = std::allocator<T> > class vector {
  
    //Member types  
    typedef T                                       value_type;
    typedef Allocator                               allocator_type;
    typedef std::size_t                             size_type;
    typedef std::ptrdiff_t                          difference_type;
    typedef value_type&                             reference;
    typedef const value_type&                       const_reference ;
    typedef typename Allocator::pointer             pointer;
    typedef typename Allocator::const_pointer       const_pointer;
    typedef void*                                   iterator;       //TODO: change this to LegacyRandomAccessIterator
    typedef const void*                             const_iterator;
    typedef void*                                   reverse_iterator;
    typedef const void*                             const_reverse_iterator;

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
    _start(alloc.allocate(count)),
    _end(_start),
    _capacity(_start + count)
    {
        while (_end != _capacity)
            _allocator.construct(_allocator, _end++, value);
        
    }


    template< class InputIt >
    vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() ):
    _allocator(alloc)
    {
        difference_type diff = ft::distance(first, last);
        _start = _allocator.allocate(diff);
        _capacity = _start + diff;
        _end = _start;
        while (first != last)
            _allocator.construct(_allocator, _end++, *first++);
    };


    vector( const vector& other ):
    _allocator(other._allocator),
    _start(ft_nullptr),
    _end(ft_nullptr),
    _capacity(ft_nullptr)
    {
        insert(begin(), other.begin(), other.end());
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
    };

    //assign
    void assign( size_type count, const T& value ) {
        clear();
        if (count == 0)
            return;
        if (count > max_size())
            throw std::length_error("cannot create std::vector larger than max_size()");
        if (count <= this->capacity())
            while (count--)
                _allocator.construct(_end++, value);
        else {
            _allocator.deallocate(_start, this->capacity());
            _start = _allocator.allocate(count);
            _end = _start;
            _capacity = _start + count;
            while (count--)
                _allocator.construct(_end++, value);
        }
    };

    template< class InputIt >
    void assign( InputIt first, InputIt last ) {
        clear();
        if (first == last)
            return;
        difference_type dist = distance(first, last);
        if (dist >= max_size())
            throw std::length_error("cannot create std::vector larger than max_size()");
        if (dist <= this->capacity())
            while (first != last)
                _allocator.construct(_end++, *first++);
        else {
            _allocator.deallocate(_start, this->capacity());
            _start = _allocator.allocate(dist);
            _end = _start;
            _capacity = _start + dist;
            while (first != last)
                _allocator.construct(_end++, *first++);
        }
    };

    //get_allocator
    allocator_type get_allocator() const;

    //Element access 
    reference at( size_type pos ) {
        if (pos >= size())
            throw std::out_of_range(ft::to_string(pos) + std::string(" >= this->size() \
            (which is ") + std::string(this->size()) + std::string(")"));
        return *(_start + pos);
    };

    const_reference at( size_type pos ) const {
        if (pos >= size())
            throw std::out_of_range(ft::to_string(pos) + std::string(" >= this->size() \
            (which is ") + std::string(this->size()) + std::string(")"));
        return *(_start + pos);
    };

    reference operator[]( size_type pos ) {
        if (pos >= size())
            throw std::out_of_range(ft::to_string(pos) + std::string(" >= this->size() \
            (which is ") + std::string(this->size()) + std::string(")"));
        return at(pos);
    }

    const_reference operator[]( size_type pos ) const {
        if (pos >= size())
            throw std::out_of_range(ft::to_string(pos) + std::string(" >= this->size() \
            (which is ") + std::string(this->size()) + std::string(")"));
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
    iterator begin() {return _start; };
    const_iterator begin() const {return _start; };
    iterator end() {return _end; };
    const_iterator end() const {return _end; };
    reverse_iterator rbegin() {return reverse_iterator(_end); };
    const_reverse_iterator rbegin() const {return const_reverse_iterator(_end); };
    reverse_iterator rend() {return reverse_iterator(_start); };
    const_reverse_iterator rend() const {return const_reverse_iterator(_start);};

    //Capacity
    bool empty() const {return _start == _end ? true : false; };
    size_type size() const {return distance(begin(), end()); };
    size_type max_size() const {return allocator_type().max_size(); };
    void reserve( size_type new_cap ) {
        if (new_cap <= capacity())
            return;
        if (new_cap > max_size())
            throw std::length_error("new_cap > max_size allowed");
        
        pointer p_start = _start;
        pointer p_end = _end;
        pointer p = p_start;
        _start = _allocator.allocate( new_cap );
        _end = _start;
        _capacity = _start + new_cap;
        while (p != p_end)
            _allocator.construct(_end++, *p++);
        _allocator.deallocate(p_start, distance(p_start, p_end));
    };
    size_type capacity() const {return distance(_start, _capacity); };

    //Modifiers
    void clear(){
        while(_end-- != _start)
            _allocator.destroy(_end);
    };

    iterator insert( const_iterator pos, const T& value ) {
        pointer p;
        iterator out;
        if (capacity() > size()) {
            p = ++_end;
            while (p != pos)
                *p = *p--;
            _allocator.construct(p, value);
        } else {
            pointer p_start = p = _start;
            pointer p_end = _end;
            difference_type p_cap = capacity();
            size_type cap = size() == 0 ? 1 : size() * 2;
            _start = _allocator.allocate(cap);
            _end = _start;
            _capacity = _start + cap;
            while (p != pos)
                *_end++ = *p++;
            while (p != p_end)
                *_end++ = *p++;
            _allocator.deallocate(p_start, p_cap);
        }
        return iterator(pos);
    };

    void insert( const_iterator pos, size_type count, const T& value ) {
        pointer p;
        if (count == 0)
            return;
        if (size() + count > max_size())
            throw std::length_error("new_size > max_size allowed");
        if (size() + count <= capacity()) {
            p = _end += count;
            while (p - count != pos)
                *p = *(p-- - count);
            while (count--)
                _allocator.construct(p--, value);
        } else {
            pointer p_cap = capacity();
            pointer p_start = p = _start;
            pointer p_end = _end;
            size_type cap = Max(size() + count, 2 * size());
            _start = _allocator.allocate(cap);
            _end = _start;
            _capacity = _start + cap;
            while (p != pos)
                *_end++ = *p++;
            while (count--)
                _allocator.construct(_end++, value);
            while (p != p_end)
                *_end++ = *p++;
            _allocator.deallocate(p_start, p_cap);
        }
    };

    template< class InputIt >
    void insert( const_iterator pos, InputIt first, InputIt last ) {
        if (first == last)
            return;
        size_type count = distance(first, last);
        pointer p;
        if (size() + count > max_size())
            throw std::length_error("new_size > max_size allowed");
        if (size() + count <= capacity()) {
            p = _end += count;
            while (p - count != pos)
                *p = *(p-- - count);
            while (last != first)
                _allocator.construct(p--, *last--);
        } else {
            pointer p_cap = capacity();
            pointer p_start = p = _start;
            pointer p_end = _end;
            size_type cap = Max(size() + count, 2 * size());
            _start = _allocator.allocate(cap);
            _end = _start;
            _capacity = _start + cap;
            while (p != pos)
                *_end++ = *p++;
            while (first != last)
                _allocator.construct(_end++, *first++);
            while (p != p_end)
                *_end++ = *p++;
            _allocator.deallocate(p_start, p_cap);
        }
    };

    iterator erase( iterator pos ) {
        pointer p = pos;
        _allocator.destroy(p);
        while (p != _end)
            *p = *(p++ + 1);
        _end--;
        return pos;
    };

    iterator erase( iterator first, iterator last ) {
        size_type count = distance((pointer)first, (pointer) last);
        pointer p = first;
        while (p != last)
            _allocator.destroy(p++);
        while (p != _end)
            *(p - count) = *p++;
        return first;
    };

    void push_back( const T& value ) {insert(back(), value); };
    void pop_back() {
        _end--;
        _allocator.destroy(_end);
    };

    void resize( size_type count, T value = T() ) {
        if (count > max_size())
            throw std::length_error("new_size > max_size allowed");
        while (count > size())
            pop_back();
        while (count < size())
            insert(_end, count - size(), value);
    };

    void swap( vector& other ) {
        if (other == *this)
            return;
        pointer p = other._start;
        other._start = _start;
        _start = p;
        p = other._end;
        other._end = _end;
        _end = p;
        p = other._capacity;
        other._capacity = _capacity;
        _capacity = p;
        p = other._allocator;
        other._allocator = _allocator;
        _allocator = p;
    };

};

}

 //Non-member functions
    template< class T, class Alloc >
    bool operator==( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
        if (lhs.size() != rhs.size())
            return false;
        typename ft::vector<T>::const_iterator it1 = lhs.begin();
        typename ft::vector<T>::const_iterator it2 = rhs.begin();

        while (it1 != lhs.end() && it2 != rhs.end())
            if (*it1++ != *it2++)
                return false;
        if (it1 != lhs.end() || it2 != rhs.end())
            return false;
        return true;
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









#endif //__FT_VECTOR__