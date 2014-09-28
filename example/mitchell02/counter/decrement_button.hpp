
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[mitchell02_decrement_button_header
// File: counter/decrement_button.hpp
#ifndef DECREMENT_BUTTON_HPP_
#define DECREMENT_BUTTON_HPP_

#include "push_button.hpp"
#include "counter.hpp"
#include "../observer/observer.hpp"
#include <contract.hpp>
#include <boost/utility.hpp>

CONTRACT_CLASS( // Button that decrements counter.
    class (decrement_button) final // Contract for final class.
        extends( public push_button, protected observer, boost::noncopyable )
) {
    CONTRACT_CLASS_INVARIANT( void ) // no invariant

    // Creation.

    CONTRACT_CONSTRUCTOR( // Create button associated with given counter.
        public explicit (decrement_button) ( (counter&) the_counter )
            postcondition(
                // enabled iff positive value
                enabled() == (the_counter.value() > 0)
            )
            initialize( counter_ref_(the_counter) )
    ) {
        counter_ref_.attach(this);
    }

    CONTRACT_DESTRUCTOR( // Destroy button.
        public (~decrement_button) ( void )
    ) {}

    // Commands.

    CONTRACT_FUNCTION(
        public void (on_bn_clicked) ( void ) override
            postcondition(
                old_value = CONTRACT_OLDOF counter_ref_.value(),
                counter_ref_.value() == old_value - 1 // counter decremented
            )
    ) {
        counter_ref_.decrement();
    }

    CONTRACT_FUNCTION(
        private bool (up_to_date_with_subject) ( void ) const override
    ) {
        return true; // For simplicity, always up-to-date.
    }

    CONTRACT_FUNCTION(
        private void (update) ( void ) override
            postcondition(
                // enabled if positive value
                enabled() == (counter_ref_.value() > 0)
            )
    ) {
        if(counter_ref_.value() == 0) disable();
        else enable();
    }

    private: counter& counter_ref_;
};

#endif // #include guard
//]

