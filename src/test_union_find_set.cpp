#include <cassert>
#include <iostream>
#include <vector>

#include "union_find_set.h"

int main() {
    UnionSet uset(5);
    assert(uset.find(3) == 3);
    assert(uset.find(1) == 1);
    uset.merge(3, 1);
    int par = uset.find(3);
    assert(par == 3 || par == 1);
    assert(uset.find(1) == par);
    assert(uset.find(0) == 0);
    assert(uset.find(2) == 2);
    assert(uset.find(4) == 4);
    return 0;
}