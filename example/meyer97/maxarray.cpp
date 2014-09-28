
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[meyer97_maxarray
// File: maxarray.cpp
#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <algorithm>

CONTRACT_FUNCTION(
    int (maxarray) ( (int const* const) array, (size_t const&) size )
        precondition(
            array, // array allocated
            size >= 1 // size in range
        )
) {
    int maxnow = array[0];
    CONTRACT_LOOP( for(size_t i = 0; i < (size - 1); ++i) ) {
        // Nested loop (with variant) used to assert enclosing loop invariants.
        CONTRACT_LOOP( for(size_t j = 0; j < i; ++j) ) {
            CONTRACT_LOOP_VARIANT( const( i, j ) i - j )
            CONTRACT_BLOCK_INVARIANT( const( maxnow, array, j )
                    maxnow >= array[j] )
        }
        // -2 because starts from 0 (not 1) and already done element at 0.
        CONTRACT_LOOP_VARIANT( const( size, i ) size - i - 2 )

        maxnow = std::max(maxnow, array[i]);
    }
    return maxnow;
}

int main ( void )
{
    int a[] = {1, 5, 3};
    BOOST_TEST(maxarray(a, 3) == 5);
    return boost::report_errors();
}
//]

