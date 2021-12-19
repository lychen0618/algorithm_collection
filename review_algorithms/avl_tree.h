#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <algorithm>

template <typename T>
struct TreeNode
{
    T val;
    TreeNode *left;
    TreeNode *right;
    int height = 1;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(T x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(T x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

template <typename T>
class avl_tree
{
private:
    /* data */
    TreeNode<T> *root = nullptr;

public:
    avl_tree(/* args */){};
    ~avl_tree(){};
    void insert(T x);
    bool delete_node(T x);
    bool contains(T x);

    TreeNode<T> *get_root()
    {
        return root;
    }

private:
    int get_height(TreeNode<T> *cur);
    void insert_aux(TreeNode<T> *&cur, T x);
    TreeNode<T> *LL(TreeNode<T> *cur);
    TreeNode<T> *LR(TreeNode<T> *cur);
    TreeNode<T> *RR(TreeNode<T> *cur);
    TreeNode<T> *RL(TreeNode<T> *cur);
};

template <typename T>
int avl_tree<T>::get_height(TreeNode<T> *cur)
{
    if (!cur)
        return 0;
    return cur->height;
    // return max(get_height(cur->left), get_height(cur->right)) + 1;
}

template <typename T>
void avl_tree<T>::insert(T x)
{
    if (!root)
    {
        root = new TreeNode<T>(x);
        return;
    }
    TreeNode<T> *head = new TreeNode<T>(-1);
    head->left = root;
    insert_aux(head->left, x);
    root = head->left;
    delete head;
}

template <typename T>
void avl_tree<T>::insert_aux(TreeNode<T> *&cur, T x)
{
    if (!cur)
    {
        cur = new TreeNode<T>(x);
        return;
    }
    if (cur->val > x)
    {
        insert_aux(cur->left, x);
        if (get_height(cur->left) - get_height(cur->right) > 1)
        {
            if (cur->left->val < x)
                cur = LR(cur);
            else
                cur = LL(cur);
        }
    }
    else if (cur->val == x)
        return;
    else
    {
        insert_aux(cur->right, x);
        if (get_height(cur->right) - get_height(cur->left) > 1)
        {
            if (cur->right->val > x)
                cur = RL(cur);
            else
                cur = RR(cur);
        }
    }
    cur->height = std::max(get_height(cur->left), get_height(cur->right)) + 1;
}

template <typename T>
TreeNode<T> *avl_tree<T>::LL(TreeNode<T> *cur)
{
    TreeNode<T> *mid = cur->left;
    cur->left = mid->right;
    mid->right = cur;
    cur->height = std::max(get_height(cur->left), get_height(cur->right)) + 1;
    mid->height = std::max(get_height(mid->left), get_height(mid->right)) + 1;
    return mid;
}

template <typename T>
TreeNode<T> *avl_tree<T>::LR(TreeNode<T> *cur)
{
    cur->left = RR(cur->left);
    return LL(cur);
}

template <typename T>
TreeNode<T> *avl_tree<T>::RR(TreeNode<T> *cur)
{
    TreeNode<T> *mid = cur->right;
    cur->right = mid->left;
    mid->left = cur;
    cur->height = std::max(get_height(cur->left), get_height(cur->right)) + 1;
    mid->height = std::max(get_height(mid->left), get_height(mid->right)) + 1;
    return mid;
}

template <typename T>
TreeNode<T> *avl_tree<T>::RL(TreeNode<T> *cur)
{
    cur->right = LL(cur->right);
    return RR(cur);
}

#endif // AVL_TREE_H