
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n1962_sqrt
// File: sqrt.cpp
#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <cmath>

CONTRACT_FUNCTION( // Default value for `precision` parameter.
    double (mysqrt) ( double x, double precision, default(1e-6) )
        precondition( x >= 0.0 )
        postcondition(
            auto root = return, // Result value named `root`.
            fabs(root * root - x) <= precision // Equal within precision.
        )
) {
    return sqrt(x);
}

int main ( void )
{
    BOOST_TEST(fabs(mysqrt(4.0) - 2.0) <= 1e-6);
    return boost::report_errors();
}
//]

