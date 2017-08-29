// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Test support for template class and functions.

#include <contract.hpp>
#include <iostream>

// Class template params (types and variables with default values).
template<typename N = long, N N_NUMBER = 100>
class x {

    CONTRACT_INVARIANT( (static) ({
        CONTRACT_ASSERT( N_NUMBER > 0 );
    }) )
    
public:
    // Funciton template params (types and variables -- C++ forbids 
    // default function template params).
    // Multiple template params to test commas within macro expansion.
    template<typename V, V V_DEFAULT>
    void add(V value = V_DEFAULT)
    CONTRACT_FUNCTION( (class) (x)
            (public) (template)( (typename)(V) (V)(V_DEFAULT) )
            (void) (add)( (V)(value) )
    (body) ({
        std::cout << value + N_NUMBER << std::endl;
    }) )
};

int main() {
    x<> xx;
    xx.add<int, 23>();
    return 0;
}

