// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Non-member function with separate definition.

#ifndef SUM_HPP_
#define SUM_HPP_

#include <contract.hpp>

double sum(int count, double* array)
CONTRACT_FUNCTION( (double) (sum)( (int)(count) (double*)(array) )
(precondition) ({
    CONTRACT_ASSERT( count % 4 == 0 );
})
(body) (
    ;
) )

#endif // #include guard

