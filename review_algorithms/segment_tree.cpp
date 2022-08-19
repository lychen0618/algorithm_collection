#include "segment_tree.h"

#include <cassert>
#include <climits>
#include <cmath>

int SegmentTree::build_tree(const int& pos,
                            const int& l,
                            const int& r,
                            const std::vector<int>& data) {
    if (data_.size() < (pos + 1))
        data_.resize(pos + 1);
    data_[pos].range = {l, r};
    data_[pos].val = data[l];
    if (l != r) {
        int mid = (l + r) / 2;
        data_[pos].val = std::min(build_tree(pos * 2, l, mid, data),
                                  build_tree(pos * 2 + 1, mid + 1, r, data));
    }
    return data_[pos].val;
}

SegmentTree::SegmentTree(const std::vector<int>& data) {
    assert(data.size() > 0);
    build_tree(1, 0, data.size() - 1, data);
}

void SegmentTree::move_change_down(const int& pos) {
    if (data_[pos].change != 0) {
        if (data_[pos].range.first != data_[pos].range.second) {
            data_[pos * 2].change += data_[pos].change;
            data_[pos * 2 + 1].change += data_[pos].change;
            data_[pos * 2].val += data_[pos].change;
            data_[pos * 2 + 1].val += data_[pos].change;
        }
        data_[pos].change = 0;
    }
}

int SegmentTree::query_helper(const int& left,
                              const int& right,
                              const int& pos) {
    const auto& range = data_[pos].range;
    if (left > range.second || right < range.first)
        return INT_MAX;
    if (left <= range.first && right >= range.second)
        return data_[pos].val;
    move_change_down(pos);
    int mid = (range.first + range.second) / 2;
    return std::min(
        query_helper(std::max(left, range.first), mid, 2 * pos),
        query_helper(mid + 1, std::min(right, range.second), 2 * pos + 1));
}

int SegmentTree::query(int left, int right) {
    return query_helper(left, right, 1);
}

void SegmentTree::update(const int& left,
                         const int& right,
                         const int& change,
                         const int& pos) {
    const auto& range = data_[pos].range;
    if (left > range.second || right < range.first)
        return;
    if (left <= range.first && right >= range.second) {
        data_[pos].change += change;
        data_[pos].val += change;
        return;
    }
    move_change_down(pos);
    int mid = (range.first + range.second) / 2;
    update(std::max(left, range.first), mid, change, 2 * pos);
    update(mid + 1, std::min(right, range.second), change, 2 * pos + 1);
    data_[pos].val = std::min(data_[pos * 2].val, data_[pos * 2 + 1].val);
}