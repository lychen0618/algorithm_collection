#include <iostream>
#include "chapter13/rb_tree.hpp"
#include "util.hpp"
#include "cassert"
using namespace std;
using chapter13::rb_tree;

int path_black_count = -1;

template <typename node>
void travel_helper(node *cur, int temp_count){
    if(!cur) return;
    if(cur->red){
        assert(!cur->left || !cur->left->red);
        assert(!cur->right || !cur->right->red);
    }
    else ++temp_count;
    if(!cur->left && !cur->right){
        if(path_black_count == -1) path_black_count = temp_count;
        else assert(temp_count == path_black_count);
    }
    else{
        travel_helper(cur->left, temp_count);
        travel_helper(cur->right, temp_count);
    }
}

template <typename T>
void check_rb_tree(rb_tree<T> rbt)
{
    if(rbt.root()){
        assert(rbt.root()->red == false);
        using node = chapter13::rb_treenode<T>;
        node *root = rbt.root();
        path_black_count = -1;
        travel_helper<node>(root, 0);
    }
}

int main()
{
    rb_tree<int> int_rbt;
    for(int i = 0; i < 100; ++i){
        int_rbt.insert_equal(util::randint(0, 100));
        check_rb_tree<int>(int_rbt);
    }
    return 0;
}