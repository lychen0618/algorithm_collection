#include <iostream>
#include <cassert>
#include <stack>
#include <vector>
#include "avl_tree.h"

using namespace std;

template <typename T>
void is_avl_tree(avl_tree<T> *my_avl_tree)
{
    TreeNode<T> *cur = my_avl_tree->get_root();
    stack<TreeNode<T> *> st;
    while (cur || !st.empty())
    {
        while (cur)
        {
            st.push(cur);
            cur = cur->left;
        }
        cur = st.top();
        st.pop();
        assert(std::abs(get_height(cur->left) - get_height(cur->right)) < 2);
        if (cur->right)
        {
            cur = cur->right;
            st.push(cur);
        }
        else
            cur = nullptr;
    }
}

template <typename T>
int get_height(TreeNode<T> *cur)
{
    if (!cur)
        return 0;
    return max(get_height(cur->left), get_height(cur->right)) + 1;
}

int main()
{
    avl_tree<int> *p_avl_tree1 = new avl_tree<int>();
    vector<int> input1;
    for (int i = 1; i < 1000; ++i)
        input1.push_back(i);
    random_shuffle(input1.begin(), input1.end());
    for (auto &val : input1)
        p_avl_tree1->insert(val);
    is_avl_tree(p_avl_tree1);
    return 0;
}