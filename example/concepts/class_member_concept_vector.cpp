
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include "class_member_concept_vector.hpp"
#include <boost/detail/lightweight_test.hpp>

int main ( void )
{
    std::vector<int> v;
    v.push_back(123);
    v.push_back(456);
    vector<int> w(v.begin(), v.end());
    vector<int>::iterator i = w.begin();
    w.insert(i, w.begin(), w.end());
    BOOST_TEST(w[0] == 123);
    BOOST_TEST(w[1] == 456);
    BOOST_TEST(w[2] == 123);
    BOOST_TEST(w[3] == 456);
    return boost::report_errors();
}

