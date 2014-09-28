
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n1962_sum_header
// File: sum.hpp
#ifndef SUM_HPP_
#define SUM_HPP_

#include <contract.hpp>

CONTRACT_FUNCTION(
    int (sum)( int count, (int*) array )
        precondition( count % 4 == 0 )
) ; // Separate body definition from function declaration (see ".cpp" file).

#endif // #include guard
//]

