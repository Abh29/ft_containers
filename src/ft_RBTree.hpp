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
    typedef Node&                                   node_refrence;
	typedef NAllocator								node_allocator;
	typedef Allocator								value_allocator;
	typedef ft::RBIterator<Node, Compare>			iterator;
    typedef std::size_t                             size_type;
    typedef std::ptrdiff_t                          difference_type;


protected:
    node_pointer            _root;
    size_type               _size;
    node_allocator          _node_alloc;
    value_allocator         _val_alloc;
    Compare                 _comp;


public:

    Red_Black_Tree():
    _root(ft_nullptr),
    _size(),
    _node_alloc(node_allocator()),
    _val_alloc(value_allocator()),
    _comp(Compare())
    {};

    Red_Black_Tree(const Red_Black_Tree& other):
    _root(other.root),
    _size(other.size),
    _node_alloc(other._node_alloc),
    _val_alloc(other._val_alloc),
    _comp(other._comp)
    {};


    template<class Iterator>
    Red_Black_Tree(Iterator& begin, Iterator& end):
        _node_alloc(node_allocator()),
        _val_alloc(value_allocator())
    {
        insert(begin, end);
    }

    //TODO: implement this
    virtual ~Red_Black_Tree() {

    };

    //TODO: delete this
    node_pointer get_root() const {return _root; };

    Red_Black_Tree& operator=(const Red_Black_Tree& other){
        _val_alloc = other._val_alloc;
        _node_alloc = other._node_alloc;
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
        node_pointer tmp = _root;
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

    
    ft::pair<iterator, bool> insert(const value_type& value) {
        node_pointer node = _node_alloc.allocate(1);
        *node = node_type(value);
        return insert(node);
    }

    ft::pair<iterator, bool> insert(node_pointer p_node) {
        ft::pair<iterator, bool> out;
        if (p_node == ft_nullptr)
            throw std::invalid_argument("can not insert a null in the tree!");
        value_type key = p_node->data;
        if (_root == ft_nullptr){
            _root = p_node;
            _root->is_black = true;
            ++_size;
            out = ft::pair<iterator, bool>(iterator(_root), true);
        }
        else {
            //bst insert
            node_pointer tmp = _root;
            node_pointer u;

            while (true){
                if (_comp(key, tmp->data)){
                    if (tmp->left == ft_nullptr){
                        tmp->left = p_node;
                        p_node->parent = tmp;
                        if (!tmp->is_black)
                            fix_insert(p_node);
                        break;
                    } else {
                        tmp = tmp->left;
                    }
                } else if (_comp(tmp->data, key)) {
                    if (tmp->right == ft_nullptr){
                        tmp->right = p_node;
                        p_node->parent = tmp;
                        if (!tmp->is_black)
                            fix_insert(p_node);
                        break;
                    } else {
                        tmp = tmp->right;
                    }
                } else {
                    return (ft::pair<iterator, bool>(iterator(tmp), false));
                }
            }
            ++_size;
            out = out = ft::pair<iterator, bool>(iterator(p_node), true);
        }
        return out;
    };

    int height() const {return height(_root); };


private:

    int height(node_pointer node) const
    {
        node_pointer tmp = node;
        if (tmp == ft_nullptr)
            return 0;
        else {
            int lheight = height(tmp->left);
            int rheight = height(tmp->right);
            if (lheight > rheight) {
                return (lheight + 1);
            } else {
                return (rheight + 1);
            }
        }
    };


    void fix_insert(node_pointer node) {
        node_pointer tmp = node;
        node_pointer u, g;

        while (tmp != _root && !tmp->parent->is_black) {
            //  std::cout << "fix" << std::endl;
            u = uncle(tmp);
            if (!u || u->is_black) {
                // std::cout << "fix" << *tmp << std::endl;

                if (is_left_child(tmp) && is_right_child(tmp->parent)){
                    rotate_right(tmp->parent);
                    tmp =  tmp->right;
                } else if (is_right_child(tmp) && is_left_child(tmp->parent)){
                    rotate_left(tmp->parent);
                    tmp = tmp->left;
                }
                tmp->parent->is_black = true;
                tmp->parent->parent->is_black = false;

                if (is_right_child(tmp)){
                    rotate_left(tmp->parent->parent);
                }else if (is_left_child(tmp)){
                    rotate_right(tmp->parent->parent);
                }
                if (tmp->parent == _root)
                    break;
            } else {
                tmp->parent->is_black = true;
                u->is_black = true;
                tmp->parent->parent->is_black = false;
            }
            
            tmp = tmp->parent->parent;
        }
        _root->is_black = true;
    }

    void rotate_right(node_pointer& node) {
        if (node == ft_nullptr || node->left == ft_nullptr)
            return;

        node_pointer l = node->left;
        node_pointer p = node->parent;

        node->parent = l;
        node->left = l->right;
        if (node == _root)
            _root = l;
        else if (p->right == node)
            p->right = l;
        else
            p->left = l;
        l->right = node;
        l->parent = p;
    }

    void rotate_left(node_pointer& node) {
        if (node == ft_nullptr || node->right == ft_nullptr)
            return;
        node_pointer r = node->right;
        node_pointer p = node->parent;

        node->parent = r;
        node->right = r->left;
        
        if (p == ft_nullptr)
            _root = r;
        else if (p->right == node)
            p->right = r;
        else
            p->left = r;
        r->left = node;
        r->parent = p;
    }

    node_pointer uncle(node_pointer& node) {
        if (node == ft_nullptr || node->parent == ft_nullptr ||
             node->parent->parent == ft_nullptr )
            return _root; // root is the uncle of no one 
        if (node->parent->parent->right == node->parent)
            return node->parent->parent->left;
        else
            return node->parent->parent->right;
    }

    bool is_left_child(node_pointer& node) {
        // if (node == ft_nullptr || node->parent == ft_nullptr)
        //     return false;
        return (node->parent->left == node);
    }

    bool is_right_child(node_pointer& node) {
        // if (node == ft_nullptr || node->parent == ft_nullptr)
        //     return false;
        return (node->parent->right == node);
    }


};




}




#endif //__FT_RBTREE__




