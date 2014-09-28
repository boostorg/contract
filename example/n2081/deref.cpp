
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n2081_deref
// File: deref.cpp
#include <contract.hpp>
#include <boost/type_traits/has_equal_to.hpp>
#include <boost/concept_check.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <vector>

CONTRACT_FUNCTION(
    template( typename Iterator )
        requires(
            boost::InputIterator<Iterator>,
            boost::CopyConstructible<
                    typename boost::InputIterator<Iterator>::value_type>
        )
    (typename boost::InputIterator<Iterator>::value_type) (deref) (
            (Iterator) iterator )
        // precondition: iterator is non-singular
        postcondition(
            auto result = return,
            result == *iterator, requires boost::has_equal_to<
                    typename boost::InputIterator<Iterator>::value_type>::value
        )
) {
    return *iterator;
}

int main ( void )
{
    std::vector<int> v(1);
    v[0] = 123;
    BOOST_TEST(deref(v.begin()) == 123);
    return boost::report_errors();
}
//]

