// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Struct handled exactly same as class.

#include <contract.hpp>
#include <iostream>

//[ struct_cpp

struct positive {
    const double& number;

    // Remember to always specify the access level (public, etc).
    positive(const double& n): number(n)
    CONTRACT_CONSTRUCTOR( (struct) (positive) // (struct) in sequence.
            (public) (positive)( (const double&)(n) )
    (precondition) ({
        CONTRACT_ASSERT( n > 0.0 );
    })
    (body) ({
    }) )
    
private:
    // Remember to always specify class invariants in a private section.
    CONTRACT_INVARIANT( ({
        CONTRACT_ASSERT( number > 0.0 );
    }) )
};

//]

int main() {
    positive p(1.23);
    std::cout << p.number << std::endl;
    return 0;
}

