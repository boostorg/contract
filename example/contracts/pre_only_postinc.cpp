
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <limits>

//[pre_only_postinc
CONTRACT_FUNCTION(
    int const (postinc) ( (int&) value )
        precondition( value < std::numeric_limits<int>::max() ) // Precondition.
        // postcondition:   value == oldof value + 1
        //                  result == oldof value
) {
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

