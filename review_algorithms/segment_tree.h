#pragma once
#include <utility>
#include <vector>

class SegmentTree {
private:
    struct TreeNode {
        int val;
        int change;
        TreeNode() : val(0), change(0) {}
        TreeNode(const int& val) : val(val), change(0) {}
    };

    std::vector<TreeNode> data_;

    const int n_;

    void buildTree(int root, int left, int right, const std::vector<int>& arr);

    int queryHelper(int pos, int l, int r, int ql, int qr);

    void updateHelper(int pos, int l, int r, int ul, int ur, const int& val);

    void move_change_down(int pos);

public:
    SegmentTree(const std::vector<int>& arr) : n_(arr.size()) {
        buildTree(0, 0, n_ - 1, arr);
    }
    ~SegmentTree() = default;

    int query(int left, int right) {
        return queryHelper(0, 0, n_ - 1, left, right);
    }

    void update(const int& val, int left, int right) {
        updateHelper(0, 0, n_ - 1, left, right, val);
    }
};
