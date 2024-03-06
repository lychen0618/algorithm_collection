#include "segment_tree.h"

#include <cassert>
#include <climits>
#include <cmath>

void SegmentTree::buildTree(int root,
                            int left,
                            int right,
                            const std::vector<int>& arr) {
    if (left == right) {
        if ((int)data_.size() <= root) {
            data_.resize(root + 1);
        }
        data_[root].val = arr[left];
        return;
    }
    int mid = (left + right) / 2;
    buildTree(root * 2 + 1, left, mid, arr);
    buildTree(root * 2 + 2, mid + 1, right, arr);
    data_[root].val =
        std::min(data_[root * 2 + 1].val, data_[root * 2 + 2].val);
}

int SegmentTree::queryHelper(int pos, int l, int r, int ql, int qr) {
    if (l > r || r < ql || l > qr) {
        return INT_MAX;  // it depends
    }
    if (l >= ql && r <= qr) {
        return data_[pos].val;
    }
    move_change_down(pos);
    int mid = (l + r) / 2;
    return std::min(queryHelper(pos * 2 + 1, l, mid, ql, qr),
                    queryHelper(pos * 2 + 2, mid + 1, r, ql, qr));
}

void SegmentTree::updateHelper(
    int pos, int l, int r, int ul, int ur, const int& val) {
    if (l > r || r < ul || l > ur) {
        return;
    }
    if (l >= ul && r <= ur) {
        data_[pos].val += val;
        data_[pos].change += val;
        return;
    }
    move_change_down(pos);
    int mid = (l + r) / 2;
    updateHelper(pos * 2 + 1, l, mid, ul, ur, val);
    updateHelper(pos * 2 + 2, mid + 1, r, ul, ur, val);
    if (l != r) {
        data_[pos].val =
            std::min(data_[pos * 2 + 1].val, data_[pos * 2 + 2].val);
    }
}

void SegmentTree::move_change_down(int pos) {
    if ((pos * 2 + 1) < (int)data_.size()) {
        data_[pos * 2 + 1].change += data_[pos].change;
        data_[pos * 2 + 2].change += data_[pos].change;
        data_[pos * 2 + 1].val += data_[pos].change;
        data_[pos * 2 + 2].val += data_[pos].change;
        data_[pos].change = 0;
    }
}
