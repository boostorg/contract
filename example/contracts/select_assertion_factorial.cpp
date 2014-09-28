
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>

//[select_assertion_factorial
CONTRACT_FUNCTION(
    int (factorial) ( int n )
        precondition( n >= 0 )
        postcondition(
            auto result = return,
            result >= 1,
            if(n == 0 or n == 1) ( // Select assertion, if-then statement.
                result == 1
            ) else ( // Select assertion, else statement (optional).
                // Assertions disabled within assertion so recursion OK.
                result == n * factorial(n - 1)
            )
        )
) {
    if(n == 0 or n == 1) return 1;
    else return n * factorial(n - 1);
}
//]

int main ( void )
{
    BOOST_TEST(factorial(4) == 24);
    return boost::report_errors();
}


