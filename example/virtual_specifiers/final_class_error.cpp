
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include "final_class.hpp"
#include <contract.hpp>

//[final_class_error
CONTRACT_CLASS(
    class (y) extends( public x ) // Correctly errors because `x` is final.
) {
    CONTRACT_CLASS_INVARIANT( void )
};
//]

int main ( void ) { return 0; }

