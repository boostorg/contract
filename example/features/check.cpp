
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract.hpp>
#include <cassert>

int gcd(int const a, int const b) {
    int result;
    boost::contract::check c = boost::contract::function()
        .precondition([&] {
            BOOST_CONTRACT_ASSERT(a > 0);
            BOOST_CONTRACT_ASSERT(b > 0);
        })
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(result <= a);
            BOOST_CONTRACT_ASSERT(result <= b);
        })
    ;

    // Function body follows...

    //[check_class
    int x = a, y = b;
    boost::contract::check c1 = [&] { // Body checks with functor.
        BOOST_CONTRACT_ASSERT(x == a);
        BOOST_CONTRACT_ASSERT(y == b);
    };
    //]

    //[check_macro
    while(x != y) {
        BOOST_CONTRACT_CHECK(x > 0); // Body checks with macros (preferred).
        BOOST_CONTRACT_CHECK(y > 0);

        if(x > y) x = x - y;
        else y = y - x;
    }
    //]

    return result = x;
}

int main() {
    assert(gcd(12, 28) == 4);
    assert(gcd(4, 14) == 2);
    return 0;
}

