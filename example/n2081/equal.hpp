
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n2081_equal_header
// File: equal.hpp
#ifndef EQUAL_HPP_
#define EQUAL_HPP_

#include <contract.hpp>
#include <boost/concept_check.hpp>

CONTRACT_FUNCTION(
    template( typename T )
        requires( boost::EqualityComparable<T> )
    bool (equal) ( (T const&) left, (T const&) right )
        postcondition( auto result = return, result == (left == right) )
) {
    return left == right;
}

#endif // #include guard
//]

