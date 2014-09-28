
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[mitchell02_name_list_header
// File: name_list.hpp
#ifndef NAME_LIST_HPP_
#define NAME_LIST_HPP_

#include <contract.hpp>
#include <string>
#include <list>

CONTRACT_CLASS( // List of names.
    class (name_list)
) {
    CONTRACT_CLASS_INVARIANT( count() >= 0 ) // non-negative count

    CONTRACT_CONSTRUCTOR( // Create an empty list.
        public (name_list) ( void )
            postcondition( count() == 0 ) // empty list
    ) ; // Deferred body definition.

    CONTRACT_DESTRUCTOR( // Destroy list.
        public virtual (~name_list) ( void )
    ) ;

    CONTRACT_FUNCTION( // Number of names in list.
        public int (count) ( void ) const
            // postcondition: non-negative count already in class invariants
    ) ;

    CONTRACT_FUNCTION( // Is name in list?
        public bool (has) ( (std::string const&) name ) const
            postcondition(
                auto result = return,
                if(count() == 0) ( not result ) // does not have is empty
            )
    ) ;

    CONTRACT_FUNCTION( // Add name to list.
        public virtual void (put) ( (std::string const&) name )
            precondition(
                not has(name) // not already in list
            )
            postcondition(
                auto old_has_name = CONTRACT_OLDOF has(name),
                auto old_count = CONTRACT_OLDOF count(),
                // Following if-guard allows to relax subcontracts.
                if(not old_has_name) (
                    has(name), // name on list
                    count() == old_count + 1 // number of names increased
                )
            )
    ) ;

    private: std::list<std::string> names_;
};

CONTRACT_CLASS( // List of names that allows for duplicates.
    class (relaxed_name_list) extends( public name_list ) // Subcontracting.
) {
    CONTRACT_CLASS_INVARIANT( void ) // no subcontracted invariants

    // Creation.

    CONTRACT_CONSTRUCTOR( // Create an empty list.
        public (relaxed_name_list) ( void )
            postcondition( count() == 0 )
    ) ;

    CONTRACT_DESTRUCTOR( // Destroy list.
        public virtual (~relaxed_name_list) ( void )
    ) ;

    // Commands.

    CONTRACT_FUNCTION( // Add name to list.
        public void (put) ( (std::string const&) name )
            precondition( // Relax inherited precondition.
                has(name) // already in list
            )
            postcondition(
                auto old_has_name = CONTRACT_OLDOF has(name),
                auto old_count = CONTRACT_OLDOF count(),
                // Inherited postconditions not checked because of its if-guard.
                if(old_has_name) (
                    count() == old_count // unchanged if name already in list
                )
            )
    ) ;
};

#endif // #include guard
//]

