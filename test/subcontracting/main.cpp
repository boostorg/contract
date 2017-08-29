// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Test subcontracting overridden functions with multiple inheritance.

// Multiple inheritance of a0 and b0 creates inheritance loop because
// also b0 inherits from a0. Loop is resolved using C++ virtual
// inheritance and the library works correctly (but this causes
// duplicate contract checking of a0).

// Deep inheritance from c0 which has 2 more base classes.

#include <contract.hpp>
#include <iostream>

// Base classes a.

class a0 {
    
    CONTRACT_INVARIANT( ({
        std::cout << "a0::inv()" << std::endl;
    }) )

public:
    virtual void f(int i)
    CONTRACT_FUNCTION( (class) (a0)
            (public) (virtual) (void) (f)( (int)(i) )
    (precondition) ({
        std::cout << "a0::pre()" << std::endl;
    })
    (postcondition) ({
        std::cout << "a0::post()" << std::endl;
    })
    (body) ({
        std::cout << "a0::body()" << std::endl;
    }) )
};

// Base classes b.

class b0: virtual public a0 {
    
    CONTRACT_INVARIANT( ({
        std::cout << "b0::inv()" << std::endl;
    }) )

public:
    virtual void f(int i)
    CONTRACT_FUNCTION( (class) (b0)
            (inherit)(a0)
            (public) (virtual) (void) (f)( (int)(i) )
    (precondition) ({
        std::cout << "b0::pre()" << std::endl;
    })
    (postcondition) ({
        std::cout << "b0::post()" << std::endl;
    })
    (body) ({
        std::cout << "b0::body()" << std::endl;
    }) )
};

// Base classes c.

class c2 {
    
    CONTRACT_INVARIANT( ({
        std::cout << "c2::inv()" << std::endl;
    }) )

public:
    virtual void f(int i)
    CONTRACT_FUNCTION( (class) (c2)
            (public) (virtual) (void) (f)( (int)(i) )
    (precondition) ({
        std::cout << "c2::pre()" << std::endl;
    })
    (postcondition) ({
        std::cout << "c2::post()" << std::endl;
    })
    (body) ({
        std::cout << "c2::body()" << std::endl;
    }) )
};

class c1: public c2 {
    
    CONTRACT_INVARIANT( ({
        std::cout << "c1::inv()" << std::endl;
    }) )

public:
    virtual void f(int i)
    CONTRACT_FUNCTION( (class) (c1)
            (inherit)(c2)
            (public) (virtual) (void) (f)( (int)(i) )
    (precondition) ({
        std::cout << "c1::pre()" << std::endl;
    })
    (postcondition) ({
        std::cout << "c1::post()" << std::endl;
    })
    (body) ({
        std::cout << "c1::body()" << std::endl;
    }) )
};

class c0: public c1 {
    
    CONTRACT_INVARIANT( ({
        std::cout << "c0::inv()" << std::endl;
    }) )

public:
    virtual void f(int i)
    CONTRACT_FUNCTION( (class) (c0)
            (inherit)(c1)
            (public) (virtual) (void) (f)( (int)(i) )
    (precondition) ({
        std::cout << "c0::pre()" << std::endl;
    })
    (postcondition) ({
        std::cout << "c0::post()" << std::endl;
    })
    (body) ({
        std::cout << "c0::body()" << std::endl;
    }) )
};

// Derived class x.

class x: virtual public a0, public b0, public c0 {
    
    CONTRACT_INVARIANT( ({
        std::cout << "x::inv()" << std::endl << std::endl;
    }) )

public:
    virtual void f(int i)
    CONTRACT_FUNCTION( (class) (x)
            // Subcontract from 3 base classes (multiple inheritance).
            (inherit)(a0) (inherit)(b0) (inherit)(c0)
            (public) (virtual) (void) (f)( (int)(i) )
    (precondition) ({
        std::cout << "x::pre()" << std::endl << std::endl;
    })
    (postcondition) ({
        std::cout << "x::post()" << std::endl << std::endl;
    })
    (body) ({
        std::cout << std::endl << "x::body()" << std::endl << std::endl;
    }) )
};

int main() {
    x xx;
    xx.f(1);
    return 0;
}
