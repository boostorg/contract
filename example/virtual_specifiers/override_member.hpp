
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef OVERRIDE_MEMBER_HPP_
#define OVERRIDE_MEMBER_HPP_

#include <contract.hpp>

//[override_member
CONTRACT_CLASS(
    class (x)
) {
    CONTRACT_CLASS_INVARIANT( void )

    CONTRACT_FUNCTION(
        public virtual void (f) ( void ) // Virtual so it can be overridden.
    ) {}
    
    CONTRACT_FUNCTION(
        public void (g) ( void ) // Not virtual so it cannot be overridden.
    ) {}
};

CONTRACT_CLASS(
    class (y) extends( public x )
) {
    CONTRACT_CLASS_INVARIANT( void )

    CONTRACT_FUNCTION(
        public void (f) ( void ) override // OK, overriding virtual `x::f`.
    ) {}
};
//]

#endif // #include guard


