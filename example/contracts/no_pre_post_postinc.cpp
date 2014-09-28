
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <boost/detail/lightweight_test.hpp>

//[no_pre_post_postinc
#include <contract.hpp>

CONTRACT_FUNCTION( // Declare free function (for programming contracts).
    int const (postinc) ( (int&) value ) // Non-fundamental types in `()`.
        // precondition:    value < std::numeric_limits<int>::max()
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

