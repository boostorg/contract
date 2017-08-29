
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include "final_member.hpp"
#include <contract.hpp>

#ifdef CONTRACT_CONFIG_NO_CLASS_INVARIANTS
#   error "virtual specifiers require appropriate contracts to be enabled"
#endif

//[final_member_error
CONTRACT_CLASS(
    class (z) extends( public y )
) {
    CONTRACT_CLASS_INVARIANT( void )

    CONTRACT_FUNCTION(
        public void (f) ( void ) // Correctly errors because `y::f` is final.
    ) {}
};
//]

int main ( void ) { return 0; }

