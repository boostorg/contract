
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[meyer97_stack4_header
// File: stack4.hpp
#ifndef STACK4_HPP_
#define STACK4_HPP_

#include <contract.hpp>

// Specification.

CONTRACT_CLASS( // Dispenser with LIFO access policy and a fixed max capacity.
    template( typename T )
    class (stack4)
) {
    CONTRACT_CLASS_INVARIANT_TPL(
        count() >= 0, // count non negative
        count() <= capacity(), // count bounded
        empty() == (count() == 0) // empty if no elements
    )

    // Initialization.

    CONTRACT_CONSTRUCTOR_TPL( // Allocate stack for a maximum of n elements.
        public explicit (stack4) ( (const int&) n )
            precondition(
                n >= 0 // non negative capacity
            )
            postcondition(
                capacity() == n // capacity set
            )
    ) ; // Deferred body definition (see bottom).

    CONTRACT_CONSTRUCTOR_TPL( // Deep copy.
        public (stack4) ( (const stack4&) right )
            postcondition(
                capacity() == right.capacity(),
                count() == right.count()
                // all items equal right's items one by one
            )
    ) ;

    CONTRACT_FUNCTION_TPL( // Deep assignment.
        public (stack4&) operator(=)(assign) ( (const stack4&) right )
            postcondition(
                capacity() == right.capacity(),
                count() == right.count()
                // all items equal right's items one by one
            )
    ) ;

    CONTRACT_DESTRUCTOR_TPL( // Destroy this stack.
        public virtual (~stack4) ( void )
    ) ;

    // Access.

    CONTRACT_FUNCTION_TPL( // Max number of stack elements.
        public int (capacity) ( void ) const
    ) ;

    CONTRACT_FUNCTION_TPL( // Number of stack elements.
        public int (count) ( void ) const
    ) ;

    CONTRACT_FUNCTION_TPL( // Top element.
        public (const T&) (item) ( void ) const
            precondition(
                not empty() // not empty (i.e., count > 0)
            )
    ) ;

    // Status report.

    CONTRACT_FUNCTION_TPL( // Is stack empty?
        public bool (empty) ( void ) const
            postcondition(
                auto result = return,
                result == (count() == 0) // empty definition
            )
    ) ;

    CONTRACT_FUNCTION_TPL( // Is stack full?
        public bool (full) ( void ) const
            postcondition(
                auto result = return,
                result == (count() == capacity()) // full definition
            )
    ) ;

    // Element change.

    CONTRACT_FUNCTION_TPL( // Add x on top.
        public void (put) ( (const T&) x )
            precondition(
                not full() // not full
            )
            postcondition(
                auto old_count = CONTRACT_OLDOF count(),
                not empty(), // not empty
                item() == x, // added to top
                count() == old_count + 1 // one more item
            )
    ) ;

    CONTRACT_FUNCTION_TPL( // Remove top item.
        public void (remove) ( void )
            precondition(
                not empty() // not empty (i.e., count > 0)
            )
            postcondition(
                auto old_count = CONTRACT_OLDOF count(),
                not full(), // not full
                count() == old_count - 1 // one fewer item
            )
    ) ;

    private: int capacity_;
    private: int count_;
    private: T* representation_; // Using C-style array.
};
    
// Implementation.
    
template< typename T >
CONTRACT_CONSTRUCTOR_BODY(stack4<T>, stack4) ( const int& n )
{
    capacity_ = n;
    count_ = 0;
    representation_ = new T[n];
}

template< typename T >
CONTRACT_CONSTRUCTOR_BODY(stack4<T>, stack4) ( const stack4& right )
{
    capacity_ = right.capacity_;
    count_ = right.count_;
    representation_ = new T[right.capacity_];
    for(int i = 0; i < right.count_; ++i)
        representation_[i] = right.representation_[i];
}

template< typename T >
stack4<T>& stack4<T>::CONTRACT_MEMBER_BODY(operator(=)(assign)) (
        const stack4& right )
{
    delete[] representation_;
    capacity_ = right.capacity_;
    count_ = right.count_;
    representation_ = new T[right.capacity_];
    for(int i = 0; i < right.count_; ++i)
        representation_[i] = right.representation_[i];
    return *this;
}

template< typename T >
CONTRACT_DESTRUCTOR_BODY(stack4<T>, ~stack4) ( void )
{
    delete[] representation_;
}

template< typename T >
int stack4<T>::CONTRACT_MEMBER_BODY(capacity) ( void ) const
{
    return capacity_;
}

template< typename T >
int stack4<T>::CONTRACT_MEMBER_BODY(count) ( void ) const
{
    return count_;
}

template< typename T >
const T& stack4<T>::CONTRACT_MEMBER_BODY(item) ( void ) const
{
    return representation_[count() - 1];
}

template< typename T >
bool stack4<T>::CONTRACT_MEMBER_BODY(empty) ( void ) const
{
    return count() == 0;
}

template< typename T >
bool stack4<T>::CONTRACT_MEMBER_BODY(full) ( void ) const
{
    return count() == capacity();
}

template< typename T >
void stack4<T>::CONTRACT_MEMBER_BODY(put) ( const T& x )
{
    representation_[count_++] = x;
}

template< typename T >
void stack4<T>::CONTRACT_MEMBER_BODY(remove) ( void )
{
    --count_;
}

#endif // #include guard
//]


