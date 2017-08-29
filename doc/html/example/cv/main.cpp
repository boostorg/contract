// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Const and volatile qualifier supports as usual but when both
// specified, const must appear before volatile.

#include <contract.hpp>
#include <iostream>

// Qualified member access works as usual:
// 1. Class invariants can access any const and const-volatile member.
// 2. Pre/postconditions of const members can access any const and
//    const-volatile member.
// 3. However, pre/postconditions of volatile members can only access
//    const-volatile members.

//[ cv_cpp

class z {

    CONTRACT_INVARIANT( ({ // const
        CONTRACT_ASSERT( check_const() && check_cv() );
    }) )

public:
    int n(int x)
    CONTRACT_FUNCTION( (class) (z)
            (public) (int) (n)( (int)(x) ) // no-cv
    (precondition) ({ // const
        CONTRACT_ASSERT( check_const() && check_cv() );
    })
    (postcondition) (result) ({ // const
        CONTRACT_ASSERT( check_const() && check_cv() );
    })
    (body) ({ // no-cv
        check_nocv(); check_const(); check_volatile(); check_cv();
        return x;
    }) )

    int c(int x) const
    CONTRACT_FUNCTION( (class) (z)
            (public) (int) (c)( (int)(x) ) (const)
    (precondition) ({ // const
        CONTRACT_ASSERT( check_const() && check_cv() );
    })
    (postcondition) (result) ({ // const
        CONTRACT_ASSERT( check_const() && check_cv() );
    })
    (body) ({ // const
        check_const(); check_cv();
        return x;
    }) )
    
    int v(int x) volatile
    CONTRACT_FUNCTION( (class) (z)
            (public) (int) (v)( (int)(x) ) (volatile)
    (precondition) ({ // const volatile
        CONTRACT_ASSERT( check_cv() );
    })
    (postcondition) (result) ({ // const volatile
        CONTRACT_ASSERT( check_cv() );
    })
    (body) ({ // volatile
        check_volatile(); check_cv();
        return x;
    }) )
    
    int cv(int x) const volatile // const appears before volatile.
    CONTRACT_FUNCTION( (class) (z)
            (public) (int) (cv)( (int)(x) ) (const) (volatile)
    (precondition) ({ // const volatile
        CONTRACT_ASSERT( check_cv() );
    })
    (postcondition) (result) ({ // const volatile
        CONTRACT_ASSERT( check_cv() );
    })
    (body) ({ // const volatile
        check_cv();
        return x;
    }) )
    
    // Used to demonstrate qualified member access constraints.
    bool check_nocv() { return true; }
    bool check_const() const { return true; }
    bool check_volatile() volatile { return true; }
    bool check_cv() const volatile { return true; }
};

//]

int main() {
    z zz;
    std::cout << zz.n(0) << std::endl;
    std::cout << zz.c(1) << std::endl;
    std::cout << zz.v(2) << std::endl;
    std::cout << zz.cv(3) << std::endl;
    return 0;
}

