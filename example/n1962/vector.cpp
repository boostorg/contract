
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n1962_vector_main
// File: vector.cpp
#include "vector.hpp"
#include <boost/detail/lightweight_test.hpp>

int main ( void )
{
    // Run a few of the operations (could test more of them...).
    vector<char> v(3);
    BOOST_TEST(v.size() == 3);
    BOOST_TEST(boost::algorithm::all_of_equal(v, '\0'));
    const vector<char>& cv = v; // A reference so no copy.

    vector<char> w(v);
    BOOST_TEST(w == v);

    vector<char>::iterator b = v.begin();
    BOOST_TEST(*b == '\0');

    vector<char>::const_iterator cb = cv.begin();
    BOOST_TEST(*cb == '\0');

    v.insert(b, 2, 'a');
    BOOST_TEST(v[0] == 'a');
    BOOST_TEST(v[1] == 'a');

    v.push_back('b');
    BOOST_TEST(v.back() == 'b');
    return boost::report_errors();
}
//]

