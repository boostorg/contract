/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */
/* $Id$ */

#ifndef DECREMENT_BUTTON_HPP_
#define DECREMENT_BUTTON_HPP_

#include "PushButton.hpp"
#include "Counter.hpp"
#include "../Observer/Observer.hpp"
#include <dbc.hpp>
#include <iostream>

/** Button to crement an associated counter. */
class DecrementButton: public PushButton, protected Observer 
        DBC_MULTI_INHERIT_OBJECT(DecrementButton) {
public:
    // Creation //

    /** Create button associated to specified counter. */
    DecrementButton(Counter& counter): counterRef_(counter), 
            counter_(counter)
    DBC_CONSTRUCTOR( (public) (DecrementButton)( (Counter&)(counter) ), {
    }, {
        DBC_ASSERT(
                self.now.enabled() == (self.now.counter().value() > 0),
                "enabled consistent with counter value");
    }, {
        counterRef_.attach(this);
        counter_ = counterRef_;
    })

    /** Destroy button. */
    virtual ~DecrementButton(void)
    DBC_DESTRUCTOR( (public) (virtual) (DecrementButton)( (void) ), {})

    // Commands //

    void onBnClicked(void)
    DBC_MEM_FUN( (public) (void) DBC_COPYABLE(DecrementButton)
            (onBnClicked)( (void) ), {
        DBC_ASSERT(self.enabled(), "enabled");
    }, {
        DBC_ASSERT(self.now.counter().value() 
                == (self.old.counter().value() - 1), "counter decremented");
    }, { 
        // Check this assertion within body code.
        DBC_ASSERT(enabled() == (counterRef().value() > 0),
                "enabled consistent with counter value");
        counterRef_.decrement();
        counter_ = counterRef_;
    })

protected:
    /** Return counter (by refernce). */
    const Counter& counterRef(void) const
    DBC_MEM_FUN( (protected) (const Counter&) (DecrementButton)
            (counterRef)( (void) ) (const), {
    }, {
    }, {
        return counterRef_; 
    })
    
    /** Return counter (by value). */
    const Counter& counter(void) const
    DBC_MEM_FUN( (protected) (const Counter&) (DecrementButton)
            (counter)( (void) ) (const), {
    }, {
    }, {
        return counter_; 
    })

private:
    bool upToDateWithSubject(void) const
    DBC_MEM_FUN( (private) (bool) (DecrementButton)DBC_BASE(Observer)
            (upToDateWithSubject)( (void) ) (const), {
    }, {
    }, {
        return true; 
    })

    void update(void)
    DBC_MEM_FUN( (public) (void) (DecrementButton)DBC_BASE(Observer) 
            (update)( (void) ), {
    }, {
        DBC_ASSERT(self.now.enabled() == (self.now.counterRef().value() > 0),
                "enabled consistent with counter value");
    }, {
        if (0 == counterRef_.value()) { disable(); }
        else { enable(); }
    })

    Counter& counterRef_;
    // This is needed just so the counter value is actually copied
    // by post<> in self.old to correctly evaluate the post-conditions of
    // onBnClicked. This is a complication when dealing with ref/ptr in the 
    // object state as the default copy will be shallow (I also could have
    // impl my own copy constructor and operator= to do a deep copy, but I 
    // still would have to keep both counterRef_ and the actual counter).
    Counter counter_;

    DBC_INVARIANT(DecrementButton, {})
};

#endif// DECREMENT_BUTTON_HPP_

