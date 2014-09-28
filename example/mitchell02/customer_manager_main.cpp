
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[mitchell02_customer_manager_main
// File: customer_manager_main.cpp 
#include "customer_manager.hpp"
#include <boost/detail/lightweight_test.hpp>

int main ( void )
{
    customer_manager mgr;
    basic_customer_details d("id1");

    mgr.add(d);
    mgr.set_name("id1", "abc");
    BOOST_TEST(mgr.name_for("id1") == "abc");
    BOOST_TEST(mgr.count() == 1);
    BOOST_TEST(mgr.id_active("id1"));
    return boost::report_errors();
}
//]

