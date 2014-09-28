
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n2081_transform
// File: transform.cpp

#define CONTRACT_CONFIG_FUNCTION_ARITY_MAX 5 // Support for 5 parameters.
#include <contract.hpp>

#include <boost/type_traits/has_equal_to.hpp>
#include <boost/concept_check.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <vector>
#include <algorithm>

CONTRACT_FUNCTION(
    template(
        typename Iterator1,
        typename Iterator2,
        typename ResultIterator,
        typename Function
    )
        requires(
            boost::InputIterator<Iterator1>,
            boost::InputIterator<Iterator2>,
            (boost::OutputIterator<ResultIterator, typename
                    boost::InputIterator<Iterator1>::value_type>),
            (boost::BinaryFunction<Function,
                    typename boost::InputIterator<Iterator1>::value_type,
                    typename boost::InputIterator<Iterator1>::value_type,
                    typename boost::InputIterator<Iterator2>::value_type>)
        )
    (ResultIterator) (mytransform) (
            (Iterator1) first1,
            (Iterator1) last1,
            (Iterator2) first2,
            (ResultIterator) result,
            (Function) function
        )
        // precondition: [first1, last1) is valid
        // precondition: [first2, first2 + (last1 - first1)) is valid
        // precondition: result is not an iterator within [first1 + 1, last1)
        //               or [first2 + 1, first2 + (last1 - first1))
        // precondition: [result, result + (last1 - first1)) is valid
) {
    return std::transform(first1, last1, first2, result, function);
}

int main ( void )
{
    std::vector<int> v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;
    std::vector<int> w(3);
    w[0] = 10; w[1] = 20; w[2] = 30;

    mytransform(v.begin(), v.end(), w.begin(), v.begin(), std::plus<int>());
    
    BOOST_TEST(v[0] == 11);
    BOOST_TEST(v[1] == 22);
    BOOST_TEST(v[2] == 33);
    return boost::report_errors();
}
//]

