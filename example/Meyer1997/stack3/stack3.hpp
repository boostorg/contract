// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Contracts for a stack reporting errors using error codes instead
// of asserting preconditions or invariants (ported from Eiffel code).

#ifndef STACK3_HPP_
#define STACK3_HPP_

#include "../stack4/stack4.hpp"
#include <contract.hpp>

/** Dispenser structures with a Last-In, First-Out access policy, and
 * a fixed maximum capacity. Tolerant version setting an error code
 * in case of impossible operations. */
template<typename T>
class stack3 {
    
    CONTRACT_INVARIANT( ({}) )

public:
    static const T DEFAULT_ITEM;

    /** Error codes. */
    enum Error {
        NO_ERROR = 0,
        OVERFLOW_ERROR,
        UNDERFLOW_ERROR,
        SIZE_ERROR,
    };

    // Initialization //

    /** Create stack for a maximum of n elements. If n < 0, set error
     * to SIZE_ERROR (but no precondition). */
    stack3(const int& n): representation_(0), error_(NO_ERROR)
    CONTRACT_CONSTRUCTOR( (class) (stack3)
            (public) (stack3)( (const int&)(n) )
    (postcondition) ({
        CONTRACT_ASSERT( (n < 0) == (error() == SIZE_ERROR) );
        CONTRACT_ASSERT( (n >= 0) == !error() );
        if (!error()) CONTRACT_ASSERT( capacity() == n );
    })
    (body) ({
        if (n >= 0) {
            representation_ = stack4<T>(n);
        } else {
            error_ = SIZE_ERROR;
        }
    }) )

    /** Destroy stack. */
    virtual ~stack3(void)
    CONTRACT_DESTRUCTOR( (class) (stack3)
            (public) (virtual) (stack3)( (void) )
    (body) ({
    }) )

    // Access //

    /** Maximum number of stack elements. */
    int capacity(void) const
    CONTRACT_FUNCTION( (class) (stack3)
            (public) (int) (capacity)( (void) ) (const)
    (body) ({
        return representation_.capacity();
    }) )

    /** Number of stack elements. */
    int count(void) const
    CONTRACT_FUNCTION( (class) (stack3)
            (public) (int) (count)( (void) ) (const)
    (body) ({
        return representation_.count();
    }) )

    /** Top element if present. Otherwise, return type's default
     * value and set error to UNDERFLOW_ERROR (but no precondition). */
    const T& item(void) const
    CONTRACT_FUNCTION( (class) (stack3)
            (public) (const T&) (item)( (void) ) (const)
    (postcondition) (result) ({
        // Const function so no need to user ODLOF(this)->empty().
        CONTRACT_ASSERT( empty() == (error() == UNDERFLOW_ERROR) );
        CONTRACT_ASSERT( !empty() == !error() );
    })
    (body) ({
        if (!empty()) {
            error_ = NO_ERROR;
            return representation_.item();
        } else {
            error_ = UNDERFLOW_ERROR;
            return DEFAULT_ITEM;
        }
    }) )

    // Status Report //

    /** Error indicator, set by various operators to a non-zero (not
     * NO_ERROR) value if they cannot perform their job. */
    Error error(void) const
    CONTRACT_FUNCTION( (class) (stack3)
            (public) (Error) (error)( (void) ) (const)
    (body) ({
        return error_;
    }) )

    /** Is stack has not item. */
    bool empty(void) const
    CONTRACT_FUNCTION( (class) (stack3)
            (public) (bool) (empty)( (void) ) (const)
    (body) ({
        return representation_.empty();
    }) )

    /** If stack cannot accept any more item. */
    bool full(void) const
    CONTRACT_FUNCTION( (class) (stack3)
            (public) (bool) (full)( (void) ) (const)
    (body) ({
        return representation_.full();
    }) )

    // Element Change //

    /** Add x to top if there is capacity left. Otherwise, set error
     * to OVERFLOW_ERROR (but no precondition). */
    void put(const T& x)
    CONTRACT_FUNCTION( (class) (copyable)(stack3)
            (public) (void) (put)( (const T&)(x) )
    (postcondition) ({
        CONTRACT_ASSERT( CONTRACT_OLDOF(this)->full() ==
                (error() == OVERFLOW_ERROR) );
        CONTRACT_ASSERT( !CONTRACT_OLDOF(this)->full() ==
                !error() );
        if (!error()) CONTRACT_ASSERT( !empty() );
        if (!error()) CONTRACT_ASSERT( item() == x );
        if (!error()) CONTRACT_ASSERT(
                count() == (CONTRACT_OLDOF(this)->count() + 1) );
    })
    (body) ({
        if (full()) {
            error_ = OVERFLOW_ERROR;
        } else {
            representation_.put(x);
            error_ = NO_ERROR;
        }
    }) )

    /** Remove element if present. Otherwise, set error to
     * UNDERFLOW_ERROR (but no precondition) */
    void remove(void)
    CONTRACT_FUNCTION( (class) (copyable)(stack3)
            (public) (void) (remove)( (void) )
    (postcondition) ({
        CONTRACT_ASSERT( CONTRACT_OLDOF(this)->empty() ==
                (error() == UNDERFLOW_ERROR) );
        CONTRACT_ASSERT( !CONTRACT_OLDOF(this)->empty() ==
                !error() );
        if (!error()) CONTRACT_ASSERT( !full() );
        if (!error()) CONTRACT_ASSERT(
                count() == (CONTRACT_OLDOF(this)->count() - 1) );
    })
    (body) ({
        if (empty()) {
            error_ = UNDERFLOW_ERROR;
        } else {
            representation_.remove();
            error_ = NO_ERROR;
        }
    }) )

private:
    stack4<T> representation_;
    // Mutable, changed by logically const members to report error.
    mutable Error error_;
};
    
// For simplicity, T must have default constructor.
template<typename T>
const T stack3<T>::DEFAULT_ITEM = T();

#endif // #include guard

