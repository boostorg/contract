// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef EQUAL_HPP_
#define EQUAL_HPP_

#include "not_equal.hpp"
#include <contract.hpp>
#include <iostream>

template<typename T>
bool operator==(T l, T r)
CONTRACT_FUNCTION(
        (template)( (typename)(T) )
        (bool) (operator(==, equal)) ( (T)(l) (T)(r) )
(postcondition) (result) ({
    CONTRACT_ASSERT( result == !(l != r) );
})
(body) ({
    std::clog << "checking for equality" << std::endl;
    return l.value == r.value;
}) )

#endif // #include guard

