// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Show how to handle `auto` and `register` storage specifiers.

#include <contract.hpp>
#include <iostream>

//[ storage_cpp

// `auto` is not repeated in signature sequence.
double square(auto double d)
CONTRACT_FUNCTION( (double) (square)( (double)(d) ) 
(postcondition) (result) ({
    CONTRACT_ASSERT( result == (d * d) );
})
(body) ({
    auto double y = d * d;
    return y;
}) )

// `register` is not repeated in signature sequence.
int square(register int i)
CONTRACT_FUNCTION( (int) (square)( (int)(i) ) 
(postcondition) (result) ({
    CONTRACT_ASSERT( result == (i * i) );
})
(body) ({
    register int y = i * i;
    return y;
}) )

//]

int main() {
    std::cout << square(2.5) << std::endl;
    std::cout << square(2) << std::endl;
    return 0;
}

