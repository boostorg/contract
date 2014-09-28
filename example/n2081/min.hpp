
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n2081_min_header
// File: min.hpp
#ifndef MIN_HPP_
#define MIN_HPP_

#include <contract.hpp>
#include <boost/type_traits/has_equal_to.hpp>
#include <boost/concept_check.hpp>

CONTRACT_FUNCTION(
    template( typename T ) requires( boost::LessThanComparable<T> )
    (T const&) (min) ( (T const&) x, (T const&) y )
        postcondition(
            auto result = return,
            x < y ? result == x : result == y,
                    requires boost::has_equal_to<T>::value
        )
) {
    return x < y ? x : y; // OK: T is less than comparable `<`.
}

#endif // #include guard
//]

