
// no #include guard

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/check.hpp>

bool no_impl(); // Test func that cannot be impl in C++ sill OK in axioms.

int main() {
    #ifdef BOOST_CONTRACT_TEST_ERROR
        BOOST_CONTRACT_CHECK_AXIOM(some-invalid-expression);
    #else
        BOOST_CONTRACT_CHECK_AXIOM(false); // Test always false, OK.
        BOOST_CONTRACT_CHECK_AXIOM(no_impl()); // Test no implementation, OK.
    #endif
    return 0;
}

