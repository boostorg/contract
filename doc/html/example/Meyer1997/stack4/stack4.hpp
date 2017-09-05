// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Contracts for a stack (ported from Eiffel code).

#ifndef STACK4_HPP_
#define STACK4_HPP_

#include <contract.hpp>

// Specification //

/** Dispenser structures with a Last-In, First-Out access policy,
 * and a fixed maximum capacity. */
template<typename T>
class stack4 {

    CONTRACT_INVARIANT( ({
        CONTRACT_ASSERT_MSG( representation_, "array allocated" );
        CONTRACT_ASSERT( count() >= 0 );
        CONTRACT_ASSERT( count() <= capacity() );
        CONTRACT_ASSERT( empty() == (count() == 0) );
        if (count() > 0) CONTRACT_ASSERT_MSG(
                representation_[count() - 1] == item(),
                "if positive, item at top" );
    }) )

public:
    // Initialization //

    /** Create stack for a maximum of n elements. */
    stack4(const int& n): capacity_(0), count_(0), representation_()
    CONTRACT_CONSTRUCTOR( (class) (stack4)
            (public) (stack4)( (const int&)(n) )
    (precondition) ({
        CONTRACT_ASSERT( n >= 0 );
    })
    (postcondition) ({
        CONTRACT_ASSERT( capacity() == n );
        CONTRACT_ASSERT( empty() );
    })
    (body) (
        ;
    ) )

    /** Deep copy. */
    stack4(const stack4& other): capacity_(other.capacity_),
            count_(other.count_),
            representation_(new T[other.capacity_])
    CONTRACT_CONSTRUCTOR( (class) (stack4)
            (public) (stack4)( (const stack4&)(other) )
    (body) (
        ;
    ) )
    
    /** Deep assignment. */
    stack4& operator=(const stack4& other)
    CONTRACT_FUNCTION( (class) (stack4)
            (public) (stack4&) (operator(=, assign))(
                    (const stack4&)(other) )
    (body) (
        ;
    ) )

    /** Destroy this stack. */
    virtual ~stack4(void)
    CONTRACT_DESTRUCTOR( (class) (stack4)
            (public) (virtual) (stack4)( (void) )
    (body) (
        ;
    ) )

    // Access //

    /** Maximum number of stack elements. */
    int capacity(void) const
    CONTRACT_FUNCTION( (class) (stack4)
            (public) (int) (capacity)( (void) ) (const)
    (body) (
        ;
    ) )

    /** Number of stack elements. */
    int count(void) const
    CONTRACT_FUNCTION( (class) (stack4)
            (public) (int) (count)( (void) ) (const)
    (body) (
        ;
    ) )

    /** Top element. */
    const T& item(void) const
    CONTRACT_FUNCTION( (class) (stack4)
            (public) (const T&) (item)( (void) ) (const)
    (body) (
        ;
    ) )

    // Status Report //

    /** If stack is empty. */
    bool empty(void) const
    CONTRACT_FUNCTION( (class) (stack4)
            (public) (bool) (empty)( (void) ) (const)
    (postcondition) (result) ({
        CONTRACT_ASSERT( result == (count() == 0) );
    })
    (body) (
        ;
    ) )

    /** If stack is full. */
    bool full(void) const
    CONTRACT_FUNCTION( (class) (stack4)
            (public) (bool) (full)( (void) ) (const)
    (postcondition) (result) ({
        CONTRACT_ASSERT( result == (count() == capacity()) );
    })
    (body) (
        ;
    ) )

    // Element Change //

    /** Add x on top. */
    void put(const T& x)
    CONTRACT_FUNCTION( (class) (copyable)(stack4)
            (public) (void) (put)( (const T&)(x) )
    (precondition) ({
        CONTRACT_ASSERT( !full() );
    })
    (postcondition) ({
        CONTRACT_ASSERT( !empty() );
        CONTRACT_ASSERT_MSG( item() == x, "added to top" );
        CONTRACT_ASSERT( count() ==
                (CONTRACT_OLDOF(this)->count() + 1) );
        CONTRACT_ASSERT_MSG( representation_[count() - 1] == x,
                "at top array entry" );
    })
    (body) (
        ;
    ) )

    /** Remove top item. */
    void remove(void)
    CONTRACT_FUNCTION( (class) (copyable)(stack4)
            (public) (void) (remove)( (void) )
    (precondition) ({
        CONTRACT_ASSERT( !empty() );
    })
    (postcondition) ({
        CONTRACT_ASSERT( !full() );
        CONTRACT_ASSERT( count() ==
                (CONTRACT_OLDOF(this)->count() - 1) );
    })
    (body) (
        ;
    ) )

private:
    int capacity_;
    int count_;
    T* representation_; // C-style array.
};

// Implementation //

template<typename T>
CONTRACT_CONSTRUCTOR_BODY(stack4<T>, stack4)(const int& n) {
    capacity_ = n;
    representation_ = new T[n];
}

template<typename T>
CONTRACT_CONSTRUCTOR_BODY(stack4<T>, stack4)(const stack4& other) {
    for (int i = 0; i < other.count_; ++i) {
        representation_[i] = other.representation_[i];
    }
}

template<typename T>
stack4<T>& stack4<T>::CONTRACT_BODY(operator(=, assign))(
        const stack4& other) {
    delete[] representation_;
    capacity_ = other.capacity_;
    count_ = other.count_;
    representation_ = new T[other.capacity_];
    for (int i = 0; i < other.count_; ++i) {
        representation_[i] = other.representation_[i];
    }
    return *this;
}

template<typename T>
CONTRACT_DESTRUCTOR_BODY(stack4<T>, ~stack4)(void)
    { delete[] representation_; }

template<typename T>
int stack4<T>::CONTRACT_BODY(capacity)(void) const
    { return capacity_;  }

template<typename T>
int stack4<T>::CONTRACT_BODY(count)(void) const { return count_; }

template<typename T>
const T& stack4<T>::CONTRACT_BODY(item)(void) const
    { return representation_[count() - 1]; }

template<typename T>
bool stack4<T>::CONTRACT_BODY(empty)(void) const
    { return count() == 0; }

template<typename T>
bool stack4<T>::CONTRACT_BODY(full)(void) const
    { return count() == capacity(); }

template<typename T>
void stack4<T>::CONTRACT_BODY(put)(const T& x)
    { representation_[count_++] = x; }

template<typename T>
void stack4<T>::CONTRACT_BODY(remove)(void) { --count_; }

#endif // #include guard

