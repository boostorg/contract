
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n1962_equal_header
// File: equal.hpp
#ifndef EQUAL_HPP_
#define EQUAL_HPP_

#include "equal_not.hpp"
#include <contract.hpp>

CONTRACT_FUNCTION_TPL(
    template( typename T )
    bool operator(==)(equal) ( (T const&) left, (T const&) right )
        postcondition(
            auto result = return,
            result == !(left != right)
        )
) {
    return left.value == right.value;
}

#endif // #include guard
//]

