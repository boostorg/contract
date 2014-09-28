
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[mitchell02_name_list_main
// File: name_list_main.cpp
#include "name_list.hpp"
#include <boost/detail/lightweight_test.hpp>

int main ( void )
{
    relaxed_name_list rl;
    rl.put("abc");
    BOOST_TEST(rl.has("abc"));
    rl.put("abc"); // Note: Can call `put("abc")` this gain.

    name_list nl;
    nl.put("abc");
    BOOST_TEST(nl.has("abc"));
    // Note: Cannot call `put("abc")` again.
    return boost::report_errors();
}
//]

