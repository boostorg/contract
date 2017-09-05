// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#include <contract.hpp>
#include <iostream>

// Recursion example.
int factorial(int n)
CONTRACT_FUNCTION(
    (int) (factorial)( (int)(n) )
(precondition) ({
    CONTRACT_ASSERT( n >= 0 );
    CONTRACT_ASSERT( n <= 12 );
})
(postcondition) (result) ({
    CONTRACT_ASSERT( result >= 1 );

    // Assertions disabled within assertions so factorial() can be
    // recursively called also from the contract (not just the body).
    // (Of course, this adds a lot of overhead...)
    if (n < 2) { CONTRACT_ASSERT( result == 1 ); }
    else { CONTRACT_ASSERT( result == n * factorial(n - 1) ); }
})
(body) ({
    if (n < 2) return 1;
    else return n * factorial(n - 1);
}) )

int main() {
    std::cout << factorial(4) << std::endl;
    return 0;
}

