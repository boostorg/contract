
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[mitchell02_push_button_header
// File: counter/push_button.hpp
#ifndef PUSH_BUTTON_HPP_
#define PUSH_BUTTON_HPP_

#include <contract.hpp>

CONTRACT_CLASS( // Basic button.
    class (push_button)
) {
    CONTRACT_CLASS_INVARIANT( void ) // no invariant

    // Creation.

    CONTRACT_CONSTRUCTOR( // Create an enabled button.
        public (push_button) ( void )
            postcondition( enabled() ) // enabled
            initialize( enabled_(true) )
    ) {}

    CONTRACT_DESTRUCTOR( // Destroy button.
        public virtual (~push_button) ( void )
    ) {}

    // Queries.

    CONTRACT_FUNCTION( // If button enabled.
        public bool (enabled) ( void ) const
    ) {
        return enabled_;
    }

    // Commands.

    CONTRACT_FUNCTION( // Enable this button.
        public void (enable) ( void )
            postcondition( enabled() ) // enabled
    ) {
        enabled_ = true;
    }

    CONTRACT_FUNCTION( // Disable this button.
        public void (disable) ( void )
            postcondition( not enabled() ) // disabled
    ) {
        enabled_ = false;
    }

    CONTRACT_FUNCTION( // Invoked externally when this button is clicked.
        public virtual void (on_bn_clicked) ( void ) new
            precondition( enabled() ) // enabled
    ) = 0; // Contract for pure virtual function.

    private: bool enabled_;
};

#endif // #include guard
//]

