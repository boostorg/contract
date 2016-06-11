
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <limits>
#include <cassert>

//[no_contracts
int inc(int& x)
    // Precondition:    x < std::numeric_limits<int>::max()
    // Postcondition:   x == oldof(x) + 1
    //                  result == oldof(x)
{
    return x++;
}
//]

int main() {
    int x = std::numeric_limits<int>::max() - 1;
    assert(inc(x) == std::numeric_limits<int>::max() - 1);
    assert(x == std::numeric_limits<int>::max());
    return 0;
}

