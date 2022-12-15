#ifndef __FT_STACK__
#define __FT_STACK__

#include "ft_vector.hpp"

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


private:
	container_type	_container;

public:

	explicit stack( const Container& cont = Container() ): 
	_container(cont)
	{};

	stack( const stack& other ):
	_container(other._container)
	{};

	virtual ~stack() {};

	stack& operator=( const stack& other ) {
		_container = other._container;
		return *this;
	};

	//Element access
	reference top() {
		return _container.back();
	};

	const_reference top() const {
		return _container.back();
	};

	//Capacity
	bool empty() const { return _container.empty(); };
	size_type size() const { return _container.size(); };
	
	//Modifiers
	void push( const value_type& value ) {
		_container.push_back(value);
	};

	void pop() {
		_container.pop_back();
	};

};

template< class T, class Container >
bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
	return lhs._container == rhs._container;
};
	
template< class T, class Container >
bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
	return lhs._container != rhs._container
};
	
template< class T, class Container >
bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
	return lhs._container < rhs._container;
};
	
template< class T, class Container >
bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
	return lhs._container <= rhs._container;
};
	
template< class T, class Container >
bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
	return lhs._container > rhs._container;
};
	
template< class T, class Container >
bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
	return lhs._container >= rhs._container;
};




}


#endif //__FT_STACK__
