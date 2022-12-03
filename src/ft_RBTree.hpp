#ifndef __FT_RBTREE__
#define __FT_RBTREE__

#include "ft_utils.hpp"
#include "ft_iterators.hpp"


namespace ft {


template<	class T, class Node = ft::RBNode<T>, 
			class NAllocator = std::allocator<Node>,
			class Allocator = std::allocator<T>,
			class Compare = ft::less<T> >
class Red_Black_Tree {


public:

	typedef T										value_type;
	typedef Node									node_type;
	typedef Node*									node_pointer;
	typedef NAllocator								node_allocator;
	typedef Allocator								value_allocator;
	typedef ft::RBIterator<Node, Compare>			iterator;
    typedef std::size_t                             size_type;
    typedef std::ptrdiff_t                          difference_type;


protected:
    node_pointer            _root;
    size_type               _size;

public:

    Red_Black_Tree():
    _root(ft_nullptr),
    _size()
    {};

    Red_Black_Tree(const Red_Black_Tree& other):
    _root(other.root),
    _size(other.size)
    {};


    template<class Iterator>
    Red_Black_Tree(Iterator& begin, Iterator& end) {
        insert(begin, end);
    }


    virtual ~Red_Black_Tree() {};


    Red_Black_Tree& operator=(const Red_Black_Tree& other){
        insert(other.begin(), other.end());
    }

    bool is_empty() const {
        return (_root == ft_nullptr);
    };

    size_type size() const {
        return _size;
    };

    node_pointer max() const {
        if (is_empty())
            return ft_nullptr;
        node_pointer tmp = _root;
        while (tmp->right)
            tmp = tmp->right;
        return tmp;
    };

    node_pointer min() const {
        if (is_empty())
            return ft_nullptr;
        node_pointer tmp;
        while (tmp->left)
            tmp = tmp->left;
        return tmp;
    };

    iterator begin() {
        return min();
    };

    iterator end() {
        return ft::RBIterator<Node, Compare>(ft_nullptr);
    };



};

}




#endif //__FT_RBTREE__




