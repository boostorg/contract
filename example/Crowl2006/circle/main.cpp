// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Subcontracting (from pure virtual) example.

#include <contract.hpp>
#include <iostream>

class shape {

    CONTRACT_INVARIANT( ({}) ) // Specify invariants even if `{}`.

public:
    virtual ~shape(void) {}

    virtual int compute_area(void) const
    CONTRACT_FUNCTION( (class) (shape)
            (public) (virtual) (int) (compute_area)( (void) ) (const)
    (postcondition) (result) ({
        CONTRACT_ASSERT( result > 0 );
    })
    (body) (
        = 0; // Contract for pure virtual function.
    ) )
};

class circle: public shape {
    
    CONTRACT_INVARIANT( ({}) )

public:
    // Hard-coded radius for simplicity of this example.
    int radius(void) const { return 2; }

    virtual int compute_area(void) const
    CONTRACT_FUNCTION( (class) (circle)
            (inherit)(shape) // Subcontracting.
            (public) (virtual) (int) (compute_area)( (void) ) (const)
    (postcondition) (result) ({
        CONTRACT_ASSERT( result == PI * radius() * radius() );
    })
    (body) ({
        return PI * radius() * radius();
    }) )

private:
    static const int PI = 3; // Truncated int of 3.14...
};

int main() {
    circle c;

    std::cout << std::endl << "compute_area()" << std::endl;
    std::cout << c.compute_area() << std::endl;
    
    return 0;
}

