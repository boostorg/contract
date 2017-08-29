
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef FINAL_MEMBER_HPP_
#define FINAL_MEMBER_HPP_

#include <contract.hpp>

//[final_member
CONTRACT_CLASS(
    class (x)
) {
    CONTRACT_CLASS_INVARIANT( void )

    CONTRACT_FUNCTION(
        public virtual void (f) ( void )
    ) {}
};

CONTRACT_CLASS(
    class (y) extends( public x )
) {
    CONTRACT_CLASS_INVARIANT( void )

    CONTRACT_FUNCTION(
        public void (f) ( void ) final // Final member function.
    ) {}
};
//]

#endif // #include guard

