#pragma once
#include <cstdlib>

namespace util { 

    //左闭右开
    int randint(int l, int r){
        return rand() % (r - l + 1) + l;
    }

    int randint(int r){
        return rand() % r;
    }
}