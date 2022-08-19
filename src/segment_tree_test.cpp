#include "segment_tree.h"

#include <cassert>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> data{2, 3, 5, -1, 8};
    SegmentTree st(data);
    assert(st.query(0, 2) == 2);
    assert(st.query(3, 3) == -1);
    assert(st.query(3, 9) == -1);
    st.update(0, 2, -1);
    assert(st.query(0, 2) == 1);
    assert(st.query(3, 3) == -1);
    assert(st.query(3, 9) == -1);
    return 0;
}