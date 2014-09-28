
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n1962_equal_not_header
// File: equal_not.hpp
#ifndef EQUAL_NOT_HPP_
#define EQUAL_NOT_HPP_

#include "equal.hpp"
#include <contract.hpp>

CONTRACT_FUNCTION_TPL(
    template( typename T )
    bool operator(!=)(not_equal) ( (T const&) left, (T const&) right )
        postcondition(
            auto result = return,
            result == !(left == right)
        )
) {
    return left.value != right.value;
}

#endif // #include guard
//]

