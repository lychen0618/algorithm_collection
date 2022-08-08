#include <cassert>
#include <iostream>

#include "string_search.h"

int main() {
    assert(rabin_karp("acbgsd", "bg") == 2);
    assert(rabin_karp("uuuuuu", "uuu") == 0);
    assert(rabin_karp("abcdef", "fed") == 6);
    assert(kmp("acbgsd", "bg") == 2);
    assert(kmp("uuuuuu", "uuu") == 0);
    assert(kmp("abcdef", "fed") == 6);

    return 0;
}