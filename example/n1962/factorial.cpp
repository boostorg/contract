
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n1962_factorial
// File: factorial.cpp
#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>

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
        precondition(
            n >= 0, // Non-negative natural number.
            n <= 12 // Max function input.
        )
        postcondition(
            auto result = return,
            result >= 1,
            if(n < 2) ( // Select assertion.
                result == 1
            ) else (
                // Assertions automatically disabled within other assertions.
                // Therefore, this postcondition can recursively call the
                // function without causing infinite recursion.
                result == n * factorial(n - 1),
                        // This assertion introduces significant run-time
                        // overhead (same as the function body) so assertion
                        // requirements are used to selectively disable it.
                        requires O_FACTN <= COMPLEXITY_MAX
            )
        )
) {
    if(n < 2) return 1;
    else return n * factorial(n - 1);
}

int main ( void )
{
    BOOST_TEST(factorial(4) == 24);
    return boost::report_errors();
}
//]

