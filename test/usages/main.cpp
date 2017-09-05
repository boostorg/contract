// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Test most of library usages.

#include <iostream>
#include <contract.hpp>

class c {
    
    CONTRACT_INVARIANT( (static)({
        std::cout << "inv (static)\n";
        CONTRACT_ASSERT( x >= 0 );
    })
    ({
        std::cout << "inv (dynamic)\n";
        CONTRACT_ASSERT( i_ >= 0 );
    }) )

public:

    // Constructor.
    c(int i = 0): i_(i)
    CONTRACT_CONSTRUCTOR( (class) (c)
            (public) (c)( (int)(i) )
    (precondition) ({
        std::cout << "pre c::c()\n";
    })
    (postcondition) ({
        std::cout << "post c::c()\n";
    })
    (body) ({
        std::cout << "body c::c()\n";
    }) )
    
    // Destructor (virtual).
    virtual ~c(void)
    CONTRACT_DESTRUCTOR( (class) (c)
            (public) (virtual) (c)( (void) )
    (body) ({
        std::cout << "body c::~c()\n";
    }) )

    // Non-const member function with cooyable object.
    double f(int i)
    CONTRACT_FUNCTION( (class) (copyable)(c)
            (public) (double) (f)( (int)(i) )
    (precondition) ({
        std::cout << "pre c::f()\n";
    })
    (postcondition) (result) ({
        std::cout << "post c::f()\n";
    })
    (body) ({
        std::cout << "body c::f()\n";
        return i;
    }) )
    
    // Overloaded const member function template.
    template<typename T>
    double f(T t) const
    CONTRACT_FUNCTION( (class) (c)
            (public) (template)( (typename)(T) )
            (double) (f)( (T)(t) ) (const)
    (precondition) ({
        std::cout << "pre template c::f() const\n";
    })
    (postcondition) (result) ({
        std::cout << "post template c::f() const\n";
    })
    (body) ({
        std::cout << "body template c::f() const\n";
        return t;
    }) )
    
    // Static member function.
    static double s(int i)
    CONTRACT_FUNCTION( (class) (c)
            (public) (static) (double) (s)( (int)(i) )
    (precondition) ({
        std::cout << "pre c::s()\n";
        CONTRACT_ASSERT( i > 0 );
    })
    (postcondition) (result) ({
        std::cout << "post c::s()\n";
        CONTRACT_ASSERT( x == i );
        CONTRACT_ASSERT( result == double(x) );
    })
    (body) ({
        std::cout << "body c::s()\n";
        return x = i;
    }) )
    
private:
    static int x;
    int i_;
};

template<typename T>
class t {

    CONTRACT_INVARIANT( ({}) )

public:

    double f(T i) const
    CONTRACT_FUNCTION( (class) (t)
            (public) (double) (f)( (T)(i) ) (const)
    (precondition) ({
        std::cout << "pre template c::f() const\n";
    })
    (postcondition) (result) ({
        std::cout << "post template c::f() const\n";
    })
    (body) ({
        std::cout << "body template c::f() const\n";
        return i;
    }) )
};

int c::x = 0;

// Non-member function witha copyable argument.
void a(const int&x, int& y)
CONTRACT_FUNCTION( (void) (a)( (const int&)(x) (copyable)(int&)(y) )
(precondition) ({
    std::cout << "pre a()\n";
})
(postcondition) ({
    std::cout << "post a()\n";
    std::cout << "  oldof(y) = " << CONTRACT_OLDOF(y) << std::endl;
    std::cout << "        y  = " << y << std::endl;
})
(body) ({
    std::cout << "body a()\n";
    y = x;
}) )

int main() {
    c cc;
    const c& const_cc = cc; 
    cc.f(1);
    const_cc.f(1.2); // Call const member.
    c::s(3);
    
    t<double> tt;
    tt.f(1.23);
    
    int z = -1;
    a(2, z);
    
    return 0;
};

