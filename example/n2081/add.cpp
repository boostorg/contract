
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n2081_add
// File: add.cpp
#include "add.hpp"
#include <boost/detail/lightweight_test.hpp>

int main ( void )
{
    int x = 10, y = 20;
    BOOST_TEST(add(x, y) == 30);
    return boost::report_errors();
}
//]

