
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n1962_block_invariant
// File: block_invariant.cpp
#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <iostream>

int main ( void )
{
    int i = 0;
    for(i = 0; i < 100; ++i)
    {
        CONTRACT_BLOCK_INVARIANT( const( i ) i >= 0 )
    }
    BOOST_TEST(i == 100);
    return boost::report_errors();
}
//]

