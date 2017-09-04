/* $Id$ */

#ifndef COUNTER_HPP_
#define COUNTER_HPP_

#include "../Observer/Subject.hpp"
#include <dbc.hpp>

/** Positive integer counter. */
class Counter: public Subject DBC_TRAILING_OBJECT(Counter) {
public:
    // Creation //

    /** Construct counter with specified initial value. */
    Counter(const int& value = 10): value_(value) 
    DBC_CONSTRUCTOR( (public) (Counter)( (const int&)(value) ), {
    }, {
    }, {})

    /** Destroy counter. */
    virtual ~Counter()
    DBC_DESTRUCTOR( (public) (virtual) (Counter)(), {})

    // Queries //

    /** Return counter value. */
    int value() const
    DBC_MEM_FUN( (public) (int) (Counter) (value)() (const), {
    }, {
    }, { 
        return value_; 
    })

    // Commands //

    /** Decrement counter's value. */
    void decrement()
    DBC_MEM_FUN( (public) (void) DBC_COPYABLE(Counter) (decrement)(), {
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

