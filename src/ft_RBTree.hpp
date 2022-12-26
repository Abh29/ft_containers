#ifndef __FT_RBTREE__
#define __FT_RBTREE__

#include "ft_utils.hpp"
#include "ft_iterators.hpp"


namespace ft {

template<   class T, class Compare = ft::less<T>,
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
    typedef ft::RBConstIterator<Node, Compare>      const_iterator;
    typedef ft::reverse_iterator<iterator>          reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;
    typedef std::size_t                             size_type;
    typedef std::ptrdiff_t                          difference_type;


protected:

    node_pointer            _root;
    size_type               _size;
    node_pointer            _nil;
    node_allocator          _node_alloc;
    value_allocator         _val_alloc;
    Compare                 _comp;


public:

    explicit Red_Black_Tree(const Compare& comp = ft::less<T>()):
    _size(),
    _node_alloc(node_allocator()),
    _val_alloc(value_allocator()),
    _comp(comp)
    {
        nil_alloc();
    };

    Red_Black_Tree(const Red_Black_Tree& other):
    _size(),
    _node_alloc(other._node_alloc),
    _val_alloc(other._val_alloc),
    _comp(other._comp)
    {
        nil_alloc();
        const_iterator b = other.begin();
        while (b != other.end()) {
            insert(*b);
            ++b;
        }
    };


    template<class Iterator>
    Red_Black_Tree(Iterator& begin, Iterator& end):
    _size(),
    _node_alloc(node_allocator()),
    _val_alloc(value_allocator())
    {
        nil_alloc();
        insert(begin, end);
    }

    virtual ~Red_Black_Tree() {
        this->clear();
        _node_alloc.deallocate(_nil, 1);
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
        return (_root == _nil);
    };

    size_type size() const {
        return _size;
    };

    size_type max_size() const {
        return _node_alloc.max_size();
    }

    //TODO: change this to O(1)
    node_pointer max() const {
        if (is_empty())
            return _nil;
        node_pointer tmp = _root;
        while (tmp->right != _nil)
            tmp = tmp->right;
        return tmp;
    };

    //TODO: change this to O(1)
    node_pointer min() const {
        if (is_empty())
            return _nil;
        node_pointer tmp = _root;
        while (tmp->left != _nil)
            tmp = tmp->left;
        return tmp;
    };

    iterator begin() { return iterator(_nil->right, _nil); };
    const_iterator begin() const { return const_iterator (_nil->right, _nil); }
    reverse_iterator rbegin() {return reverse_iterator(end()); }
    const_reverse_iterator  rbegin() const {return const_reverse_iterator(end()); }
    iterator end() { return iterator(_nil); };
    const_iterator end() const {return const_iterator (_nil); }
    reverse_iterator rend() {return reverse_iterator(begin()); }
    const_reverse_iterator rend() const {return const_reverse_iterator(begin()); }

//    TODO: change _nil
    ft::pair<iterator, bool> insert(const value_type& value) {
        node_pointer node = _node_alloc.allocate(1);
        _node_alloc.construct(node, value);
        node->parent = node->right = node->left = _nil;
        ft::pair<iterator, bool> out = insert(node);
        if (!out.second)
            delete_node(node);
        return out;
    }

    ft::pair<iterator, bool> insert(const node_pointer p_node) {
        ft::pair<iterator, bool> out = ft::make_pair(iterator(_nil), false);
        if (p_node == ft_nullptr || p_node == _nil)
            throw std::invalid_argument("can not insert a nil node into the tree!");
        value_type key = p_node->data;
        p_node->parent = p_node->right = p_node->left = _nil;
        if (_root == _nil){
            _root = p_node;
            _root->is_black = true;
            _nil->right = _nil->left = _root;
            ++_size;
            out = ft::pair<iterator, bool>(iterator(_root, _nil), true);
        }
        else {
            //bst insert
            node_pointer tmp = _root;

            while (true){
                if (_comp(key, tmp->data)){
                    if (tmp->left == _nil){
                        tmp->left = p_node;
                        p_node->parent = tmp;
                        if (_nil->right->left != _nil)
                            _nil->right = _nil->right->left;
                        if (!tmp->is_black)
                            fix_insert(p_node);
                        break;
                    } else {
                        tmp = tmp->left;
                    }
                } else if (_comp(tmp->data, key)) {
                    if (tmp->right == _nil){
                        tmp->right = p_node;
                        p_node->parent = tmp;
                        if (_nil->left->right != _nil)
                            _nil->left = _nil->left->right;
                        if (!tmp->is_black)
                            fix_insert(p_node);
                        break;
                    } else {
                        tmp = tmp->right;
                    }
                } else {
                    return (ft::pair<iterator, bool>(iterator(tmp, _nil), false));
                }
            }
            ++_size;
            out = ft::pair<iterator, bool>(iterator(p_node, _nil), true);
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

    //TODO: change _nil
    size_type remove(const value_type& key) {

        if (_root == _nil)
            return 0;

        node_pointer tmp = _root;

        while (tmp != _nil) {
            if (_comp(key, tmp->data))
                tmp = tmp->left;
            else if (_comp(tmp->data, key))
                tmp = tmp->right;
            else
                return remove(tmp);
        }

        return 0;
    }

    iterator find(const value_type& key) const {

        if (_root == _nil)
            return _nil;

        node_pointer tmp = _root;

        while (tmp != _nil) {
            if (_comp(key, tmp->data))
                tmp = tmp->left;
            else if (_comp(tmp->data, key))
                tmp = tmp->right;
            else
                return tmp;
        }
        return _nil;
    }

    //TODO: implement this
    void clear() {
        if (_root == _nil)
            return;
        dell_rec(_root);
        _nil->right = _nil->left = _nil;
        _root = _nil;
        _size = 0;
    };


    void swap(Red_Black_Tree &other) {
        node_pointer    tmp_r = _root;
        node_pointer    tmp_l = _nil;
        size_type       tmp_s = _size;
        node_allocator  tmp_n = _node_alloc;
        value_allocator tmp_v = _val_alloc;
        Compare         tmp_c = _comp;


        _root = other._root;
        _nil  = other._nil;
        _size = other._size;
        _node_alloc = other._node_alloc;
        _val_alloc = other._val_alloc;
        _comp = other._comp;


        other._root = tmp_r;
        other._nil = tmp_l;
        other._size = tmp_s;
        other._node_alloc = tmp_n;
        other._val_alloc = tmp_v;
        other._comp = tmp_c;
    };


private:

    int height(node_pointer node) const
    {
        node_pointer tmp = node;
        if (tmp == _nil)
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
        node_pointer u;

        while (tmp != _root && !tmp->parent->is_black) {
            u = uncle(tmp);
            if (u->is_black) {
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
        if (node == _nil || node->left == _nil)
            return;

        node_pointer l = node->left;
        node_pointer p = node->parent;

        node->parent = l;
        node->left = l->right;

        if (l->right != _nil)
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
        if (node == _nil || node->right == _nil)
            return;

        node_pointer r = node->right;
        node_pointer p = node->parent;

        node->parent = r;
        node->right = r->left;

        if (r->left != _nil)
            r->left->parent = node;
        if (p == _nil)
            _root = r;
        else if (p->right == node)
            p->right = r;
        else
            p->left = r;
        r->left = node;
        r->parent = p;

    }

    node_pointer uncle(node_pointer& node) {
        if (node == _nil || node->parent == _nil ||
             node->parent->parent == _nil )
            return _nil;
        if (node->parent->parent->right == node->parent)
            return node->parent->parent->left;
        else
            return node->parent->parent->right;
    }

    bool is_left_child(node_pointer& node) {
        // if (node == _nil || node->parent == _nil)
        //     return false;
        return (node->parent->left == node);
    }

    bool is_right_child(node_pointer& node) {
        // if (node == _nil || node->parent == _nil)
        //     return false;
        return (node->parent->right == node);
    }

    void RB_transplant(node_pointer u, node_pointer v) {
        if (u == ft_nullptr || u == _nil)
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

    //TODO: confirm this
    int remove(node_pointer node) {
        node_pointer y = node;
        node_pointer x;
        bool o_black = node->is_black;

        if (node == ft_nullptr || node == _nil)
            return 0;

        if (node->left == _nil) {
            x = node->right;
            RB_transplant(node, node->right);
        } else if (node->right == _nil) {
            x = node->left;
            RB_transplant(node, node->left);
        } else {
            y = node->right;
            while (y->left != _nil)
                y = y->left;
            o_black = y->is_black;
            x = y->right;
            if (y->parent == node && x != _nil)
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
        }
        if (o_black)
            RB_delete_fixup(x);
        if (_nil->right == node)
            _nil->right = min();
        if (_nil->left == node)
            _nil->left = max();
        delete_node(node);
        --_size;
        return 1;
    }


    void RB_delete_fixup(node_pointer node) {

        node_pointer x = node;
        node_pointer w;
        while (x != _root && x->is_black) {
            if (is_left_child(x)) {
                w = x->parent->right;
                if (!w->is_black) {
                    w->is_black = true;
                    x->parent->is_black = false;
                    rotate_left(x->parent);
                    w = x->parent->right;
                }
                if (w->left->is_black && w->right->is_black) {
                    w->is_black = false;
                    x = x->parent;
                } else {
                    if (w->right->is_black) {
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
                if (!w->is_black) {
                    w->is_black = true;
                    x->parent->is_black = false;
                    rotate_right(x->parent);
                    w = x->parent->left;
                }
                if (w->left->is_black && w->right->is_black) {
                    w->is_black = false;
                    x = x->parent;
                } else {
                    if (w->left->is_black) {
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
        if (node == _nil)
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

    void nil_alloc() {
        _nil = _node_alloc.allocate(1);
        _nil->right = _nil;
        _nil->left = _nil;
        _nil->parent = _nil;
        _nil->is_black = true;
        _root = _nil;
    }

};




}




#endif //__FT_RBTREE__




