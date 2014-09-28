
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[meyer97_stack3
// File: stack3.cpp
#include "stack4.hpp"
#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>

CONTRACT_CLASS( // Dispenser LIFO and max capacity using error codes.
    template( typename T )
    class (stack3)
) {
    CONTRACT_CLASS_INVARIANT_TPL( void ) // no class invariant

    public: enum Error { // Error codes.
        NO_ERROR = 0,
        OVERFLOW_ERROR,
        UNDERFLOW_ERROR,
        SIZE_ERROR
    };

    // Initialization.

    // Create stack for max of n elements, if n < 0 set error (no precondition).
    CONTRACT_CONSTRUCTOR_TPL(
        public (stack3) ( (const int&) n, (const T&) none, default T() )
            postcondition(
                bool(n < 0) == (error() == SIZE_ERROR), // error if impossible
                bool(n >= 0) == !error(), // no error if possible
                if(bool(!error())) ( capacity() == n ) // created if no error
            )
            initialize( none_(none), representation_(0), error_(NO_ERROR) )
    ) {
        if(n >= 0) representation_ = stack4<T>(n);
        else error_ = SIZE_ERROR;
    }

    CONTRACT_DESTRUCTOR_TPL( // Destroy stack.
        public virtual (~stack3) ( void )
    ) {}

    // Access.

    CONTRACT_FUNCTION_TPL( // Max number of stack elements.
        public int (capacity) ( void ) const
    ) {
        return representation_.capacity();
    }

    CONTRACT_FUNCTION_TPL( // Number of stack elements.
        public int (count) ( void ) const
    ) {
        return representation_.count();
    }

    // Top element if present, otherwise set error (no precondition).
    CONTRACT_FUNCTION_TPL(
        public (const T&) (item) ( void ) const
            postcondition(
                empty() == (error() == UNDERFLOW_ERROR), // error if impossible
                bool(!empty() == !error()) // no error if possible
            )
    ) {
        if(!empty()) {
            error_ = NO_ERROR;
            return representation_.item();
        } else {
            error_ = UNDERFLOW_ERROR;
            return none_;
        }
    }

    // Status report.

    CONTRACT_FUNCTION_TPL( // Error indicator set by various operations.
        public (Error) (error) ( void ) const
    ) {
        return error_;
    }

    CONTRACT_FUNCTION_TPL( // Is stack empty?
        public bool (empty) ( void ) const
    ) {
        return representation_.empty();
    }

    CONTRACT_FUNCTION_TPL( // Is stack full?
        public bool (full) ( void ) const
    ) {
        return representation_.full();
    }

    // Element change.

    // Add x to top if capacity left, otherwise set error (no precondition).
    CONTRACT_FUNCTION_TPL(
        public void (put) ( (const T&) x )
            postcondition(
                auto old_full = CONTRACT_OLDOF full(),
                auto old_count = CONTRACT_OLDOF count(),
                old_full == (error() == OVERFLOW_ERROR), // error if impossible
                not old_full == not error(), // no error if possible
                if(not error()) (
                    not empty(), // not empty if no error
                    item() == x, // added to top is no error
                    count() == old_count + 1 // one more item if no error
                )
            )
    ) {
        if(full()) {
            error_ = OVERFLOW_ERROR;
        } else {
            representation_.put(x);
            error_ = NO_ERROR;
        }
    }

    // Remove top item if possible, otherwise set error to (no precondition).
    CONTRACT_FUNCTION_TPL(
        public void (remove) ( void )
            postcondition(
                auto old_empty = CONTRACT_OLDOF empty(),
                auto old_count = CONTRACT_OLDOF count(),
                old_empty == (error() == UNDERFLOW_ERROR), // if impossible
                not old_empty == not error(), // no error if possible
                if(not error()) (
                    not full(), // not full is no error
                    count() == old_count - 1 // one fewer item if no error
                )
            )
    ) {
        if(empty()) {
            error_ = UNDERFLOW_ERROR;
        } else {
            representation_.remove();
            error_ = NO_ERROR;
        }
    }

    private: const T none_;
    private: stack4<T> representation_;
    private: mutable Error error_; // Mutable for logic constantness.
};

int main ( void )
{
    stack3<int> s(3);
    BOOST_TEST(s.capacity() == 3);
    BOOST_TEST(s.count() == 0);
    BOOST_TEST(s.empty());
    BOOST_TEST(not s.full());
    s.put(123);
    BOOST_TEST(s.item() == 123);
    s.remove();
    BOOST_TEST(s.empty());
    return boost::report_errors();
}
//]

