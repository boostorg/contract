
// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Test auto error after pre (for free func, but same for all contracts).

#include <boost/config.hpp>

// On C++17 or later.
#if     (defined(__cplusplus) && __cplusplus >= 201703L) || \
        !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)
    #error "C++17 copy elision invalidates test so forcing expected failure"
#else

#include <boost/contract/function.hpp>

int main() {
    auto c = boost::contract::function() // Error (can't use auto).
        .precondition([] {})
    ;
    return 0;
}

#endif

