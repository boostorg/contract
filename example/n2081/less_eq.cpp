
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n2081_less_eq
// File: less_eq.cpp
#include <contract.hpp>
#include <boost/concept_check.hpp>
#include <boost/detail/lightweight_test.hpp>

CONTRACT_FUNCTION(
    template( typename T )
        requires(
            boost::EqualityComparable<T>,
            boost::LessThanComparable<T>
        )
    bool (less_eq) ( (T) left, (T) right )
        postcondition(
            auto result = return,
            result == (left < right || left == right)
        )
) {
    return left < right || left == right;
}

int main ( void )
{
    BOOST_TEST(less_eq(1, 2) == true);
    BOOST_TEST(less_eq(2, 1) == false);
    return boost::report_errors();
}
//]

