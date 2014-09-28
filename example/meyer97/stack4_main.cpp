
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[meyer97_stack4_main
// File: stack4_main.cpp
#include "stack4.hpp"
#include <boost/detail/lightweight_test.hpp>

int main ( void )
{
    stack4<int> s(3);
    BOOST_TEST(s.capacity() == 3);
    BOOST_TEST(s.count() == 0);
    s.put(123);
    BOOST_TEST(not s.empty());
    BOOST_TEST(not s.full());
    BOOST_TEST(s.item() == 123);
    s.remove();
    BOOST_TEST(s.empty());
    return boost::report_errors();
}
//]

