
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n2081_count
// File: count.cpp
#include <contract.hpp>
#include <boost/concept_check.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <vector>

CONTRACT_FUNCTION(
    template( typename Iterator )
        requires(
            boost::InputIterator<Iterator>,
            boost::EqualityComparable<Iterator>,
            boost::EqualityComparable<
                    typename boost::InputIterator<Iterator>::value_type>
        )
    (typename boost::InputIterator<Iterator>::difference_type) (mycount) (
            (Iterator) first, (Iterator) last,
            (typename boost::InputIterator<Iterator>::value_type const&) value )
        // precondition: range [first, last) is valid
        postcondition( auto result = return, result >= 0 )
) {
    typename boost::InputIterator<Iterator>::difference_type result = 0;
    CONTRACT_LOOP( while(first != last) ) { // OK: Iterator has `==`.
        CONTRACT_LOOP_VARIANT_TPL(
                const( first, last ) std::distance(first, last) )
        if(*first == value) // OK: Value is equality comparable.
            ++result;
        ++first; // OK: Iterator is input iterator.
    }
    return result; // OK: Input iterator difference is copy constructible.
}

int main ( void )
{
    std::vector<int> v(3);
    v[0] = -1; v[1] = 0; v[2] = -1;
    BOOST_TEST(mycount(v.begin(), v.end(), -1) == 2);
    return boost::report_errors();
}
//]

