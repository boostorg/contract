
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n1962_sum_main
// File: sum_main.cpp
#include "sum.hpp"
#include <boost/detail/lightweight_test.hpp>

int main ( void )
{
    int a[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    BOOST_TEST(sum(8, a) == 8);
    return boost::report_errors();
}
//]

