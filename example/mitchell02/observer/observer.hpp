
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[mitchell02_observer_header
// File: observer/observer.hpp
#ifndef OBSERVER_HPP_
#define OBSERVER_HPP_

#include <contract.hpp>

CONTRACT_CLASS( // Observer.
    class (observer)
) {
    CONTRACT_CLASS_INVARIANT( void ) // no invariant

    friend class subject;

    // Creation.

    CONTRACT_CONSTRUCTOR( // Create observer.
        public (observer) ( void )
    ) {}

    CONTRACT_DESTRUCTOR( // Destroy observer.
        public virtual (~observer) ( void )
    ) {}

    // Commands.

    CONTRACT_FUNCTION( // If up to date with its subject.
        protected virtual bool (up_to_date_with_subject) ( void ) const new
    ) = 0;

    CONTRACT_FUNCTION( // Update and inform its subject.
        protected virtual void (update) ( void ) new
            postcondition( up_to_date_with_subject() ) // up-to-date
    ) = 0;
};

#endif // #include guard
//]

