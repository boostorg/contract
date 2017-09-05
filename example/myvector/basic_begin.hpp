// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Base class for a myvector subcontracting example.

#ifndef BASIC_BEGIN_HPP_
#define BASIC_BEGIN_HPP_

//[ basic_begin_cpp

#include <contract.hpp>

template<class ConstIter>
class basic_begin {

    CONTRACT_INVARIANT( ({}) )

public:
    virtual ConstIter begin(void) const
    CONTRACT_FUNCTION( (class) (basic_begin)
            (public) (virtual) (ConstIter) (begin)( (void) ) (const)
    (body) ({
        return ConstIter(); // Dummy implementation (for example only).
    }) )
};

//]

#endif // #include guard

