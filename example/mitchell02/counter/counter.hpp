
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[mitchell02_counter_header
// File: counter/counter.hpp
#ifndef COUNTER_HPP_
#define COUNTER_HPP_

#include "../observer/subject.hpp"
#include <contract.hpp>

CONTRACT_CLASS( // Positive integer counter.
    class (counter) extends( public subject )
) {
    CONTRACT_CLASS_INVARIANT( void ) // no invariants

    // Creation.

    CONTRACT_CONSTRUCTOR( // Construct counter with specified value.
        public explicit (counter) ( int const a_value, default 10 )
            postcondition( value() == a_value ) // value set
            initialize( value_(a_value) )
    ) {}

    CONTRACT_DESTRUCTOR( // Destroy counter.
        public virtual (~counter) ( void )
    ) {}

    // Queries.

    CONTRACT_FUNCTION( // Current counter value.
        public int (value) ( void ) const
    ) {
        return value_;
    }

    // Commands.

    CONTRACT_FUNCTION( // Decrement counter value.
        public void (decrement) ( void )
            postcondition(
                auto old_value = CONTRACT_OLDOF value(),
                value() == old_value - 1 // decremented
            )
    ) {
        --value_;
        notify(); // Notifies all attached observers.
    }

    private: int value_;
};

#endif // #include guard
//]

