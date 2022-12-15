#ifndef __FT_RBTREE__
#define __FT_RBTREE__

#include "ft_utils.hpp"
#include "ft_iterators.hpp"


namespace ft {


template<	class T, class Compare = ft::less<T>,
            class Node = ft::RBNode<T>, 
			class NAllocator = std::allocator<Node>,
			class Allocator = std::allocator<T> >
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

    Red_Black_Tree(const Compare& comp = ft::less<T>()):
    _root(ft_nullptr),
    _size(),
    _node_alloc(node_allocator()),
    _val_alloc(value_allocator()),
    _comp(comp)
    {};

    Red_Black_Tree(const Red_Black_Tree& other):
    _root(ft_nullptr),
    _size(),
    _node_alloc(other._node_alloc),
    _val_alloc(other._val_alloc),
    _comp(other._comp)
    {
        insert(other.begin(), other.end());
    };


    template<class Iterator>
    Red_Black_Tree(Iterator& begin, Iterator& end):
        _node_alloc(node_allocator()),
        _val_alloc(value_allocator())
    {
        insert(begin, end);
    }

    //TODO: implement this
    virtual ~Red_Black_Tree() {
        this->clear();
    };

    //TODO: delete this
    node_pointer get_root() const {return _root; };

    size_type height() const {return height(_root); };

    Red_Black_Tree& operator=(const Red_Black_Tree& other){
        if (this == &other)
            return *this;
        _val_alloc = other._val_alloc;
        _node_alloc = other._node_alloc;
        insert(other.begin(), other.end());
        return *this;
    }

    bool is_empty() const {
        return (_root == ft_nullptr);
    };

    size_type size() const {
        return _size;
    };

    size_type max_size() const {
        return _node_alloc.max_size();
    }

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

    iterator begin() const {
        return min();
    }

    iterator end() const {
        return iterator(ft_nullptr);
    }

    ft::pair<iterator, bool> insert(const value_type& value) {
        node_pointer node = _node_alloc.allocate(1);
        _node_alloc.construct(node, value);
        ft::pair<iterator, bool> out = insert(node);
        if (!out.second)
            delete_node(node);
        return out;
    }

    ft::pair<iterator, bool> insert(node_pointer p_node) {
        ft::pair<iterator, bool> out = ft::make_pair(iterator(_comp), false);
        if (p_node == ft_nullptr)
            throw std::invalid_argument("can not insert a null in the tree!");
        value_type key = p_node->data;
        if (_root == ft_nullptr){
            _root = p_node;
            _root->is_black = true;
            ++_size;
            out = ft::pair<iterator, bool>(iterator(_root, _comp), true);
        }
        else {
            //bst insert
            node_pointer tmp = _root;

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
                    return (ft::pair<iterator, bool>(iterator(tmp, _comp), false));
                }
            }
            ++_size;
            out = out = ft::pair<iterator, bool>(iterator(p_node, _comp), true);
        }
        return out;
    };

    void insert(const iterator& begin, const iterator& end) {
        iterator b = begin;
        while (b != end) {
            insert(*b);
            ++b;
        }
    }

    size_type remove(const value_type& key) {

        if (_root == ft_nullptr)
            return 0;

        node_pointer tmp = _root;

        while (tmp) {
            if (_comp(key, tmp->data))
                tmp = tmp->left;
            else if (_comp(tmp->data, key))
                tmp = tmp->right;
            else
                return remove(tmp);
        }
        return 0;
    }

    iterator find(const value_type& key) {

        if (_root == ft_nullptr)
            return end();

        node_pointer tmp = _root;

        while (tmp) {
            if (_comp(key, tmp->data))
                tmp = tmp->left;
            else if (_comp(tmp->data, key))
                tmp = tmp->right;
            else
                return tmp;
        }
        return end();
    }

    //TODO: implement this
    void clear() {
        if (_root == ft_nullptr)
            return;
        dell_rec(_root);
        _root = ft_nullptr;
        _size = 0;
    };


    void swap(const Red_Black_Tree &other) {
        node_pointer    tmp_r = _root;
        size_type       tmp_s = _size;
        node_allocator  tmp_n = _node_alloc;
        value_allocator tmp_v = _val_alloc;
        Compare         tmp_c = _comp;


        _root = other._root;
        _size = other._size;
        _node_alloc = other._node_alloc;
        _val_alloc = other._val_alloc;
        _comp = other._comp;


        other._root = tmp_r;
        other._size = tmp_s;
        other._node_alloc = tmp_n;
        other._val_alloc = tmp_v;
        other._comp = tmp_c;
    };


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
            u = uncle(tmp);
            if (!u || u->is_black) {
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

        if (l->right)
            l->right->parent = node;
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
        
        if (r->left)
            r->left->parent = node;
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

    size_type remove2(node_pointer node) {

        node_pointer tmp = ft_nullptr;

        if (node == ft_nullptr)
            return 0;
        if (node->right == ft_nullptr) {
            tmp = node->left;
            if (node == _root) {
                _root = node->left;
                if (tmp) {
                    _root->parent = ft_nullptr;
                    _root->is_black = true;   
                }
                delete_node(node);
                --_size;
                return 1;
            } else {
                if (is_right_child(node))
                    node->parent->right = node->left;
                else
                    node->parent->left = node->left;
                if (tmp)
                    node->left->parent = node->parent;
                if (tmp && !tmp->is_black)
                    tmp->is_black = true;
                else if (node->is_black)
                    fix_delete(node); 
                delete_node(node);
                --_size;
                return 1;
            }
        }else if (node->left == ft_nullptr) {
            tmp = node->right;
            if (node == _root) {
                _root = node->right;
                if (tmp) {
                    _root->parent = ft_nullptr;
                    _root->is_black = true;   
                }
                delete_node(node);
                --_size;
                return 1;
            } else {
                if (is_right_child(node))
                    node->parent->right = node->right;
                else
                    node->parent->left = node->right;
                if (tmp)
                    node->right->parent = node->parent;
                if (node->is_black)
                    fix_delete(node);
                delete_node(node);
                --_size;
                return 1;
            }
        }else {
            tmp = node->left;
            while (tmp->right)
                tmp = tmp->right;
            _val_alloc.destroy(&node->data);
            node->data = tmp->data;
            if (is_right_child(tmp))
                tmp->parent->right = tmp->right;
            else 
                tmp->parent->left = tmp->right;
            if (tmp->left)
                tmp->left->parent = tmp->parent;
            if (tmp->is_black)
                fix_delete(tmp);
            delete_node(tmp);
        }
        return 0;
    }

    void RB_transplant(node_pointer u, node_pointer v) {
        if (u == ft_nullptr)
            return;
        if (u == _root)
            _root = v;
        else if (is_right_child(u))
            u->parent->right = v;
        else
            u->parent->left = v;
        if (v)
            v->parent = u->parent;
    }

    int remove(node_pointer node) {
        node_pointer y = node;
        node_pointer x;
        bool o_black = node->is_black;

        if (node == ft_nullptr)
            return 0;

        if (node->left == ft_nullptr) {
            x = node->right;
            RB_transplant(node, node->right);
        } else if (node->right == ft_nullptr) {
            x = node->left;
            RB_transplant(node, node->left);
        } else {
            y = node->right;
            while (y->left)
                y = y->left;
            o_black = y->is_black;
            x = y->right;
            if (y->parent == node && x)
                x->parent = y;
            else {
                RB_transplant(y, y->right);
                y->right = node->right;
                y->right->parent = y;
            }
            RB_transplant(node, y);
            y->left = node->left;
            y->left->parent = y;
            y->is_black = node->is_black;
            if (o_black)
                RB_delete_fixup(x);
            delete_node(node);
            --_size;
        }
        return 1;
    }


    void RB_delete_fixup(node_pointer node) {

        node_pointer x = node;
        node_pointer w;
        while (x != _root && x->is_black) {
            if (is_left_child(x)) {
                w = x->parent->right;
                if (w && !w->is_black) {
                    w->is_black = true;
                    x->parent->is_black = false;
                    rotate_left(x->parent);
                    w = x->parent->right;
                }
                if ((!w->left || w->left->is_black) && (!w->right || w->right->is_black)) {
                    w->is_black = false;
                    x = x->parent;
                } else {
                    if (!w->right || w->right->is_black) {
                        w->left->is_black = true;
                        w->is_black = false;
                        rotate_right(w);
                        w = x->parent->right;
                    }
                    w->is_black = x->parent->is_black;
                    x->parent->is_black = true;
                    w->right->is_black = true;
                    rotate_left(x->parent);
                    x = _root;
                }
            } else {
                w = x->parent->left;
                if (w && !w->is_black) {
                    w->is_black = true;
                    x->parent->is_black = false;
                    rotate_right(x->parent);
                    w = x->parent->left;
                }
                if ((!w->left || w->left->is_black) && (!w->right || w->right->is_black)) {
                    w->is_black = false;
                    x = x->parent;
                } else {
                    if (!w->left || w->left->is_black) {
                        w->right->is_black = true;
                        w->is_black = false;
                        rotate_right(w);
                        w = x->parent->left;
                    }
                    w->is_black = x->parent->is_black;
                    x->parent->is_black = true;
                    w->right->is_black = true;
                    rotate_right(x->parent);
                    x = _root;
                }
            }
        }
        x->is_black = true;
    };


    void dell_rec(node_pointer node) {
        if (node == ft_nullptr)
            return;
        dell_rec(node->left);
        dell_rec(node->right);
        delete_node(node);
    }

    void delete_node(node_pointer node) {
        _val_alloc.destroy(&node->data);
        _node_alloc.destroy(node);
        _node_alloc.deallocate(node, 1);
    }

};




}




#endif //__FT_RBTREE__




