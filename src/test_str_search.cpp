#include <iostream>
#include <cassert>

#include "string_search.h"

int main() {
    assert(rabin_karp("acbgsd", "bg") == 2);
    assert(rabin_karp("uuuuuu", "uuu") == 0);
    assert(rabin_karp("abcdef", "fed") == 6);
    return 0;
}