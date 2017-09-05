// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Loop variants and invariants (ported from Eiffel code).

#include <contract.hpp>
#include <iostream>
#include <algorithm>

/** Calculate greater common divisor of given positive integers. */
int gcd(const int& a, const int& b)
CONTRACT_FUNCTION( (int)(gcd)( (const int&)(a) (const int&)(b) )
(precondition) ({
    CONTRACT_ASSERT( a > 0 );
    CONTRACT_ASSERT( b > 0 );
})
(postcondition) (result) ({
    /** @post result is greatest common divisor of a and b */
})
(body) ({
    int x = a;
    int y = b;
    // Block invariants can apper in any code block (not just loop).
    CONTRACT_ASSERT_BLOCK_INVARIANT( x == a );
    CONTRACT_ASSERT_BLOCK_INVARIANT( y == b );
    
    // Loop variant and invariants.
    for (CONTRACT_INIT_LOOP_VARIANT; x != y; ) {
        CONTRACT_ASSERT_BLOCK_INVARIANT( x > 0 );
        CONTRACT_ASSERT_BLOCK_INVARIANT( y > 0 );
        /** @inv gcd(x, y) == gcd(a, b) */
        CONTRACT_ASSERT_LOOP_VARIANT( std::max(x, y) );

        if (x > y) x = x - y;
        else y = y - x;
    }
    
    return x;
}) )

int main() {
    int a = 12, b = 18;
    std::cout << "gcd(" << a << ", " << b << ") = "
            << gcd(a, b) << std::endl;
    
    a = 4; b = 14;
    std::cout << "gcd(" << a << ", " << b << ") = "
            << gcd(a, b) << std::endl;
    
    return 0;
}

