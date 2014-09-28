
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <boost/detail/lightweight_test.hpp>

//[no_contract_postinc
int const postinc ( int& value )
    // precondition:    value < std::numeric_limits<int>::max()
    // postcondition:   value == oldof value + 1
    //                  result == oldof valule
{
    return value++;
}
//]

int main ( void )
{
    int value = 1;
    BOOST_TEST(postinc(value) == 1);
    BOOST_TEST(value == 2);
    return boost::report_errors();
}

