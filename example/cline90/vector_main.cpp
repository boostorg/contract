
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[cline90_vector_main
// File: vector_main.cpp
#include "vector.hpp"
#include <boost/detail/lightweight_test.hpp>

int main ( void )
{
    vector<int> v(3); // Also set all elements to 0.0.
    BOOST_TEST(v.size() == 3);
    v[0] = 123;
    v.resize(2);
    BOOST_TEST(v[0] == 123);
    BOOST_TEST(v.size() == 2);
    return boost::report_errors();
}
//]

