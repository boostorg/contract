// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Base class for a myvector subcontracting example.

#ifndef BOUNDABLE_HPP_
#define BOUNDABLE_HPP_

//[ boundable_cpp

#include <contract.hpp>

template<class ConstIter>
class boundable {

    CONTRACT_INVARIANT( ({
        CONTRACT_ASSERT( begin() <= end() );
    }) )

public:
    virtual ConstIter begin(void) const
    CONTRACT_FUNCTION( (class) (boundable)
            (public) (virtual) (ConstIter) (begin)( (void) ) (const)
    (body) (= 0;) )

    virtual ConstIter end(void) const = 0;
};

//]

#endif // #include guard

