
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Test missing contract guard gives run-time error.

struct err {};
#define BOOST_CONTRACT_ON_MISSING_GUARD { throw err(); }

#include <boost/contract/function.hpp>
#include <boost/contract/guard.hpp>
#include <boost/detail/lightweight_test.hpp>

int main() {
    boost::contract::guard c = boost::contract::function() // Test this is OK.
        .precondition([] {})
        .old([] {})
        .postcondition([] {})
    ;

    try {
        boost::contract::function() // Test no `guard c = ...` errors.
            .precondition([] {})
            .old([] {})
            .postcondition([] {})
        ;
        #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_INVARIANTS)
            BOOST_TEST(false); // Error, must throw.
        #endif
    } catch(err const&) {
        // OK, threw as expected.
    } catch(...) {
        BOOST_TEST(false); // Error, unexpected throw.
    }
    return boost::report_errors();
}

