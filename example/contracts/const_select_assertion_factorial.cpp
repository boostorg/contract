
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>

//[const_select_assertion_factorial
int n = 0;

CONTRACT_FUNCTION(
    int (factorial) ( void )
        precondition( const( n ) n >= 0 )
        postcondition(
            auto result = return,
            if(const( n ) n == -1 or n == 0) ( // Constant-correct if-condition.
                result == 1
            ) else (
                result >= 1
            )
        )
) {
    int m = n;
    if(m == 0 or m == 1) {
        return 1;
    } else {
        --n;
        return m * factorial();
    }
}
//]

int main ( void )
{
    n = 4;
    BOOST_TEST(factorial() == 24);
    return boost::report_errors();
}

