/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */
/* $Id$ */

#ifndef COUNTER_HPP_
#define COUNTER_HPP_

#include "../Observer/Subject.hpp"
#include <dbc.hpp>

/** Positive integer counter. */
class Counter: public Subject DBC_MULTI_INHERIT_OBJECT(Counter) {
public:
    // Creation //

    /** Construct counter with specified initial value. */
    Counter(const int& value = 10): value_(value) 
    DBC_CONSTRUCTOR( (public) (Counter)( (const int&)(value) ), {
    }, {
    }, {})

    /** Destroy counter. */
    virtual ~Counter(void)
    DBC_DESTRUCTOR( (public) (virtual) (Counter)( (void) ), {})

    // Queries //

    /** Return counter value. */
    int value(void) const
    DBC_MEM_FUN( (public) (int) (Counter) (value)( (void) ) (const), {
    }, {
    }, { 
        return value_; 
    })

    // Commands //

    /** Decrement counter's value. */
    void decrement(void)
    DBC_MEM_FUN( (public) (void) DBC_COPYABLE(Counter) (decrement)( (void) ), {
        DBC_ASSERT(self.value() >= 1, "positive value");
    }, {
        DBC_ASSERT(self.now.value() == (self.old.value() - 1),
                "decremented value");
    }, { 
        --value_;
        notify();
    })

private:
    int value_;

    DBC_INVARIANT(Counter, {})
};

#endif // COUNTER_HPP_

