
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n2081_for_each
// File: for_each.cpp
#include <contract.hpp>
#include <boost/type_traits/has_equal_to.hpp>
#include <boost/concept_check.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <vector>

CONTRACT_FUNCTION(
    template( typename Iterator, typename Function )
        requires(
            boost::InputIterator<Iterator>,
            (boost::UnaryFunction<Function, void, typename
                    boost::InputIterator<Iterator>::value_type>)
        )
    (Function) (my_for_each) ( (Iterator) first, (Iterator) last,
            (Function) function )
        // precondition: range [first, last) is valid
        postcondition(
            auto result = return,
            result == function, requires boost::has_equal_to<Function>::value
        )
) {
    CONTRACT_LOOP( while(first < last) ) { // OK: Iterator is InputIterator.
        CONTRACT_LOOP_VARIANT_TPL(
                const( first, last ) std::distance(first, last) )
        function(*first); // OK: Function is UnaryFunction.
        ++first; // OK: Iterator is InputIterator.
    }
    return function;
}

int total = 0;
void add ( int i ) { total += i; }

int main ( void )
{
    std::vector<int> v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;
    my_for_each(v.begin(), v.end(), add);
    BOOST_TEST(total == 6);
    return boost::report_errors();
}
//]

