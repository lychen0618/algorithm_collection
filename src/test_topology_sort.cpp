#include <cassert>
#include <iostream>

#include "topology_sort.h"

int main() {
    std::vector<std::vector<int>> arr{{1, 0}, {2, 1}, {2, 0}};
    std::vector<int> expected{0, 1, 2};
    auto sorted = topologySort(3, arr);
    assert(sorted == expected);
    return 0;
}