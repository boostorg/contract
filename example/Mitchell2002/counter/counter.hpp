// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// A somewhat more complex example using the observer design pattern
// (ported from Eiffel code). Also shows how to make the library
// access a private copy constructor to support old value for
// `decrement_button` objects.

#ifndef COUNTER_HPP_
#define COUNTER_HPP_

#include "../observe/observe.hpp"
#include <contract.hpp>

/** Positive integer counter. */
class counter: public subject {

    CONTRACT_INVARIANT( ({}) )

public:
    // Creation //

    /** Construct counter. */
    counter(const int& value = 10): value_(value)
    CONTRACT_CONSTRUCTOR( (class) (counter)
            (public) (counter)( (const int&)(value) )
    (body) ({
    }) )

    /** Destroy counter. */
    virtual ~counter(void)
    CONTRACT_DESTRUCTOR( (class) (counter)
            (public) (counter)( (void) )
    (body) ({
    }) )

    // Queries //

    /** Counter current value. */
    int value(void) const
    CONTRACT_FUNCTION( (class) (counter)
            (public) (int) (value)( (void) ) (const)
    (body) ({
        return value_;
    }) )

    // Commands //

    /** Decrement counter value. */
    void decrement(void)
    CONTRACT_FUNCTION( (class) (copyable)(counter)
            (public) (void) (decrement)( (void) )
    (postcondition) ({
        CONTRACT_ASSERT( value() ==
                (CONTRACT_OLDOF(this)->value() - 1) );
    })
    (body) ({
        --value_;
        notify(); // Notifies all attached observers.
    }) )

private:
    int value_;
};

#endif // #include guard

