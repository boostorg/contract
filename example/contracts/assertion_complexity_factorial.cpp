
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>

//[assertion_complexity_factorial
// Assertion requirements used to model assertion computational complexity.
#define O_1      0 // O(1) constant (default).
#define O_N      1 // O(n) linear.
#define O_NN     2 // O(n * n) quadratic.
#define O_NX     3 // O(n^x) polynomial.
#define O_FACTN  4 // O(n!) factorial.
#define O_EXPN   5 // O(e^n) exponential.
#define O_ALL   10
#define COMPLEXITY_MAX O_ALL

CONTRACT_FUNCTION(
    int (factorial) ( int n )
        precondition( n >= 0 )
        postcondition(
            auto result = return,
            result >= 1,
            if(n < 2) (
                result == 1
            ) else (
                // Assertion compiled and checked only if within complexity.
                result == n * factorial(n - 1),
                        requires O_FACTN <= COMPLEXITY_MAX
            )
        )
) {
    if(n < 2) return 1;
    else return n * factorial(n - 1);
}
//]

int main ( void )
{
    BOOST_TEST(factorial(4) == 24);
    return boost::report_errors();
}

