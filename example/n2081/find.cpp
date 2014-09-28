
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n2081_find
// File: find.cpp
#include "find.hpp"
#include <boost/detail/lightweight_test.hpp>
#include <vector>

int main ( void )
{
    std::vector<int> ints(3);
    ints[0] = 1; ints[1] = 2; ints[2] = 3;
    BOOST_TEST(*myfind(ints.begin(), ints.end(), 2) == 2);
    return boost::report_errors();
}
//]

