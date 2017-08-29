
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef NEW_MEMBER_HPP_
#define NEW_MEMBER_HPP_

#include <contract.hpp>

//[new_member
CONTRACT_CLASS(
    class (x)
) {
    CONTRACT_CLASS_INVARIANT( void )

    CONTRACT_FUNCTION(
        public virtual void (f) ( void ) new // OK, no base so no `f` override.
    ) {}
};

CONTRACT_CLASS(
    class (y) extends( public x )
) {
    CONTRACT_CLASS_INVARIANT( void )

    CONTRACT_FUNCTION(
        public virtual void (g) ( void ) new // OK, there is no `x::g`.
    ) {}
};
//]

#endif // #include guard

