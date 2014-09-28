
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n2081_apply
// File: apply.cpp
#include <contract.hpp>
#include <boost/type_traits/has_equal_to.hpp>
#include <boost/concept_check.hpp>
#include <boost/detail/lightweight_test.hpp>

// Use assertion requirements to model assertion computational complexity.
#define O_1     0   // constant computational complexity O(1)
#define O_BODY  10  // same computation complexity of the body
#define COMPLEXITY_MAX O_1 // only check assertions with complexity within O(1)

CONTRACT_FUNCTION( // Invoke unary functors.
    template( typename Result, typename Argument0, typename Function )
        requires( (boost::UnaryFunction<Function, Result, Argument0>) )
    (Result) (apply) ( (Function) function, (Argument0) argument0,
            (Result&) result )
        postcondition(
            auto return_value = return,
            result == function(argument0),
                    requires O_BODY <= COMPLEXITY_MAX && 
                             boost::has_equal_to<Result>::value,
            return_value == result,
                    requires boost::has_equal_to<Result>::value
        )
) {
    return result = function(argument0);
}

CONTRACT_FUNCTION( // Overload to invoke binary functors.
    template( typename Result, typename Argument0, typename Argument1,
            typename Function )
        requires( (boost::BinaryFunction<Function, Result, Argument0,
                Argument1>) )
    (Result) (apply) ( (Function) function, (Argument0) argument0,
            (Argument1) argument1, (Result&) result )
        postcondition(
            auto return_value = return,
            result == function(argument0, argument1),
                    requires O_BODY <= COMPLEXITY_MAX && 
                             boost::has_equal_to<Result>::value,
            return_value == result,
                    requires boost::has_equal_to<Result>::value
        )
) {
    return result = function(argument0, argument1);
}

int complement ( int x ) { return -x; }
int add ( int x, int y ) { return x + y; }

int main ( void )
{
    int r = 0;
    apply(complement, 1, r);
    BOOST_TEST(r == -1);

    apply(add, 1, 2, r);
    BOOST_TEST(r == 3);
    return boost::report_errors();
}
//]

