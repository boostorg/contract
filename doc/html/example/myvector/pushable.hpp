// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Base class for a myvector subcontracting example.

#ifndef PUSHABLE_HPP_
#define PUSHABLE_HPP_

//[ pushable_cpp

#include <contract.hpp>

template<typename T>
class pushable {

    CONTRACT_INVARIANT( ({}) )

public:
    // Contract for pure virtual function.
    virtual void push_back(const T& element)
    CONTRACT_FUNCTION(
            (class) (pushable)
            (public) (virtual) (void) (push_back)( (const T&)(element) )
    (postcondition) ({
        CONTRACT_ASSERT( back() == element );
    })
    (body) (= 0;) ) // Pure virtual body.

    virtual const T& back() const = 0;
};

//]

#endif // #include guard


