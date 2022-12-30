#ifndef __FT_STACK__
#define __FT_STACK__

#include "vector.hpp"

namespace ft {

template<
    class T,
    class Container = ft::vector<T>
> class stack {

public:
	typedef Container								container_type;
	typedef typename Container::value_type			value_type;
	typedef typename Container::size_type			size_type;
	typedef typename Container::reference			reference;
	typedef typename Container::const_reference		const_reference;


protected:
	container_type	c;

public:

	explicit stack( const Container& cont = Container() ): 
	c(cont)
	{};

	stack( const stack& other ):
	c(other.c)
	{};

	virtual ~stack() {};

	stack& operator=( const stack& other ) {
		c = other.c;
		return *this;
	};

	//Element access
	reference top() {
		return c.back();
	};

	const_reference top() const {
		return c.back();
	};

	//Capacity
	bool empty() const { return c.empty(); };
	size_type size() const { return c.size(); };
	
	//Modifiers
	void push( const value_type& value ) {
		c.push_back(value);
	};

	void pop() {
		c.pop_back();
	};


    template< class _T, class _Container >
    friend bool operator==( const ft::stack<_T,_Container>& lhs, const ft::stack<_T,_Container>& rhs );

    template< class _T, class _Container >
    friend bool operator!=( const ft::stack<_T,_Container>& lhs, const ft::stack<_T,_Container>& rhs );

    template< class _T, class _Container >
    friend bool operator<( const ft::stack<_T,_Container>& lhs, const ft::stack<_T,_Container>& rhs );

    template< class _T, class _Container >
    friend bool operator<=( const ft::stack<_T,_Container>& lhs, const ft::stack<_T,_Container>& rhs );

    template< class _T, class _Container >
    friend bool operator>( const ft::stack<_T,_Container>& lhs, const ft::stack<_T,_Container>& rhs );

    template< class _T, class _Container >
    friend bool operator>=( const ft::stack<_T,_Container>& lhs, const ft::stack<_T,_Container>& rhs );

};

template< class T, class Container >
bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
	return lhs.c == rhs.c;
};
	
template< class T, class Container >
bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
	return lhs.c != rhs.c;
};
	
template< class T, class Container >
bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
	return lhs.c < rhs.c;
};
	
template< class T, class Container >
bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
	return lhs.c <= rhs.c;
};
	
template< class T, class Container >
bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
	return lhs.c > rhs.c;
};
	
template< class T, class Container >
bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
	return lhs.c >= rhs.c;
};




}


#endif //__FT_STACK__
