
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/detail/lightweight_test.hpp>

//[blockinv_loopvar_gcd
CONTRACT_FUNCTION(
    template( typename T )
    (T) (gcd) ( (T const&) a, (T const&) b )
        precondition(
            static_assert(boost::is_integral<T>::value, "integral type"),
            a != 0,
            b != 0
        )
        postcondition(
            auto result = return,
            result <= a,
            result <= b
        )
) {
    T x = a, y = b;
    // Block invariant assert conditions within body,
    CONTRACT_BLOCK_INVARIANT_TPL( const( x, a ) x == a, const( y, b ) y == b )

    CONTRACT_LOOP( while(x != y) ) { // Define a loop with variants (below).
        // Block invariant for loops (i.e., loop invariants).
        CONTRACT_BLOCK_INVARIANT_TPL( const( x ) x > 0, const( y ) y > 0 )
        // Loop variant checked to be non-negative and monotonically decreasing.
        CONTRACT_LOOP_VARIANT_TPL( const( x, y ) std::max(x, y) )

        if(x > y) x = x - y;
        else y = y - x;
    }

    return x;
}
//]

int main ( void )
{
    BOOST_TEST(gcd(12, 28) == 4);
    BOOST_TEST(gcd(4, 14) == 2);
    return boost::report_errors();
}

