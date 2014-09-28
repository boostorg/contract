
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n1962_equal_main
// File: equal_main.cpp
#include "equal.hpp"
#include "equal_not.hpp"
#include <boost/detail/lightweight_test.hpp>

struct number { int value; };

int main ( void )
{
    number n;
    n.value = 123;

    BOOST_TEST((n == n) == true);
    BOOST_TEST((n != n) == false);
    return boost::report_errors();
}
//]

