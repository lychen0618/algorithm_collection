#pragma once
#include <utility>
#include <vector>

class SegmentTree {
private:
    struct node {
        /* data */
        std::pair<int, int> range;
        int val;
        int change;

        node() {}
        node(std::pair<int, int> r) : range(r), val(0), change(0) {}
    };

    std::vector<node> data_;

    int build_tree(const int& pos,
                   const int& l,
                   const int& r,
                   const std::vector<int>& data);

    void move_change_down(const int& pos);

    int query_helper(const int& left, const int& right, const int& pos);

public:
    SegmentTree(const std::vector<int>& data);
    ~SegmentTree() = default;

    int query(int left, int right);

    // 只考虑一个区间的元素增加或减少相同的值
    void update(const int& left,
                const int& right,
                const int& change,
                const int& pos = 1);
};
