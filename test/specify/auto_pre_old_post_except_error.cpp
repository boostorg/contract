
// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Test auto error after except (for free func, but same for all contracts).

#if defined(__cplusplus) && __cplusplus >= 201703L // On C++17 or later.
    #error "C++17 guaranteed copy elision invalidates this test so forcing test's expected complier error"
#else

#include <boost/contract/function.hpp>

int main() {
    auto c = boost::contract::function() // Error (can't use auto).
        .precondition([] {})
        .old([] {})
        .postcondition([] {})
        .except([] {})
    ;
    return 0;
}

#endif

