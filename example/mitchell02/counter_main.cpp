
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[mitchell02_counter_main
// File: counter_main.cpp
#include "counter/counter.hpp"
#include "counter/decrement_button.hpp"
#include "observer/observer.hpp"
#include <boost/detail/lightweight_test.hpp>

int counter_check;

CONTRACT_CLASS( // Show current value of associated counter.
    class (view_of_counter) extends( private observer )
) {
    CONTRACT_CLASS_INVARIANT( void ) // no invariant

    // Creation.

    CONTRACT_CONSTRUCTOR( // Create viewer associated with given counter.
        public explicit (view_of_counter) ( (counter&) the_counter )
            initialize( counter_ref_(the_counter) )
    ) {
        counter_ref_.attach(this);
        BOOST_TEST(counter_ref_.value() == counter_check);
    }

    CONTRACT_DESTRUCTOR( // Destroy viewer.
        public virtual (~view_of_counter) ( void )
    ) {}

    CONTRACT_FUNCTION(
        private bool (up_to_date_with_subject) ( void ) const override final
    ) {
        return true; // For simplicity, always up-to-date.
    }

    CONTRACT_FUNCTION(
        private void (update) ( void ) override final // Contract final func.
    ) {
        BOOST_TEST(counter_ref_.value() == counter_check);
    }

    private: counter& counter_ref_;
};

int main ( void )
{
    counter count(counter_check = 1);
    view_of_counter view(count);
    decrement_button decrement(count);
    BOOST_TEST(decrement.enabled());
    
    counter_check--;
    decrement.on_bn_clicked();
    BOOST_TEST(not decrement.enabled());
    return boost::report_errors();
}
//]

