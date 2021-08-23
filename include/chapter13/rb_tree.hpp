#ifndef RB_TREE_H__
#define RB_TREE_H__

namespace chapter13
{
    //TODO:增加删除的代码，现在只能添加
    template <typename T>
    struct rb_treenode
    {
        T key;
        using pointer = rb_treenode *;
        pointer parent;
        pointer left;
        pointer right;
        bool red;
        rb_treenode() : key(T()), parent(nullptr), left(this), right(this), red(true) {}
        rb_treenode(T v) : key(v), red(true) {}
    };

    template <typename T>
    class rb_tree
    {
        using node = rb_treenode<T>;
        using link_type = node *;

    private:
        node *header;

        void __insert(link_type x, link_type y, T &v)
        {
            link_type z;
            if (y == header || x || v < y->key)
            {
                z = new node(v);
                y->left = z;
                if (y == header)
                {
                    header->parent = z;
                    header->right = z;
                }
                else if (y == header->left)
                    header->left = z;
            }
            else
            {
                z = new node(v);
                y->right = z;
                if (y == header->right)
                    header->right = z;
            }
            z->parent = y;
            z->left = nullptr;
            z->right = nullptr;
            __rb_tree_balance(z, header->parent);
        }

        inline void __rb_tree_balance(link_type x, link_type &root)
        {
            x->red = true;
            while (x != root && x->parent->red)
            {
                if (x->parent == x->parent->parent->left)
                {
                    link_type y = x->parent->parent->right;
                    if (y && y->red)
                    {
                        x->parent->red = false;
                        y->red = false;
                        x->parent->parent->red = true;
                        x = x->parent->parent;
                    }
                    else
                    {
                        if (x == x->parent->right)
                        {
                            x = x->parent;
                            __rb_tree_rotate_left(x, root);
                        }
                        x->parent->red = false;
                        x->parent->parent->red = true;
                        __rb_tree_rotate_right(x->parent->parent, root);
                    }
                }
                else
                {
                    link_type y = x->parent->parent->left;
                    if (y && y->red)
                    {
                        x->parent->red = false;
                        y->red = false;
                        x->parent->parent->red = true;
                        x = x->parent->parent;
                    }
                    else
                    {
                        if (x == x->parent->left)
                        {
                            x = x->parent;
                            __rb_tree_rotate_right(x, root);
                        }
                        x->parent->red = false;
                        x->parent->parent->red = true;
                        __rb_tree_rotate_left(x->parent->parent, root);
                    }
                }
            }
            root->red = false;
        }

        inline void __rb_tree_rotate_left(link_type x, link_type &root)
        {
            link_type y = x->right;
            x->right = y->left;
            if (y->left)
                y->left->parent = x;
            y->parent = x->parent;
            if (x == root)
                root = y;
            else if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y;
            y->left = x;
            x->parent = y;
        }

        inline void __rb_tree_rotate_right(link_type x, link_type &root)
        {
            link_type y = x->left;
            x->left = y->right;
            if (y->right)
                y->right->parent = x;
            y->parent = x->parent;
            if (x == root)
                root = y;
            else if (x == x->parent->right)
                x->parent->right = y;
            else
                x->parent->left = y;
            y->right = x;
            x->parent = y;
        }

    public:
        void insert_equal(T v)
        {
            link_type y = header;
            link_type x = root();
            while (x)
            {
                y = x;
                x = ((v < x->key) ? x->left : x->right);
            }
            __insert(x, y, v);
        }

        link_type &root() const { return (link_type &)header->parent; }

        rb_tree(){
            header = new node();
        }
    };
}

#endif /* RB_TREE_H__ */