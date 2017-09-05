// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Inline member and non-member functions supported as usual. 

#include <contract.hpp>
#include <iostream>

//[ inline_cpp

class z {

    CONTRACT_INVARIANT( ({}) )

public:
    inline void inl(int x)
    CONTRACT_FUNCTION( (class) (z)
            (public) (inline) (void) (inl)( (int)(x) )
    (body) ({
        std::cout << x << std::endl;
    }) )
};

inline void inl(int x)
CONTRACT_FUNCTION( (inline) (void) (inl)( (int)(x) )
(body) ({
    std::cout << x << std::endl;
}) )

//]

int main() {
    z zz;
    zz.inl(1);
    inl(2);
    return 0;
}

