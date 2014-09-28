
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[meyer97_gcd
// File: gcd.cpp
#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <algorithm>

CONTRACT_FUNCTION( // Great common divisor of given positive integers.
    int (gcd) ( int a, int b )
        precondition(
            a > 0, b > 0
        )
) {
    int x = a, y = b;

    CONTRACT_LOOP( while(x != y) ) { // Loop contracted with a variant.
        // Block invariant assert loop invariant.
        CONTRACT_BLOCK_INVARIANT( const( x ) x > 0, const( y ) y > 0 )
        // Loop variant is non-negative and monotonically decreasing.
        CONTRACT_LOOP_VARIANT( const( x, y ) std::max(x, y) )

        // `x` and `y` have the same GCD as `a` and `b`.        
        
        if(x > y) x = x - y; else y = y - x;
    }
    return x;
}

int main ( void )
{
    BOOST_TEST(gcd(12, 18) == 6);
    BOOST_TEST(gcd(4, 14) == 2);
    return boost::report_errors();
}
//]

