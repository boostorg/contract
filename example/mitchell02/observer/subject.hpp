
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[mitchell02_subject_header
// File: observer/subject.hpp
#ifndef SUBJECT_HPP_
#define SUBJECT_HPP_

#include "observer.hpp"
#include <contract.hpp>
#include <list>
#include <algorithm>

// Assertion requirements used to model assertion computational complexity.
#define O_1 0   // O(1) constant (default)
#define O_N 1   // O(n) linear
#define COMPLEXITY_MAX O_1

CONTRACT_CLASS( // Subject for observer design pattern.
    class (subject)
) {
    CONTRACT_CLASS_INVARIANT(
        all_observers_valid(observers()), // observes valid
                requires O_N <= COMPLEXITY_MAX
    )

    // Creation.

    CONTRACT_CONSTRUCTOR( // Construct subject with no observer.
        public (subject) ( void )
    ) {}

    CONTRACT_DESTRUCTOR( // Destroy subject.
        public virtual (~subject) ( void )
    ) {}

    // Queries.

    CONTRACT_FUNCTION( // If given observer is attached.
        public bool (attached) ( (observer const* const) obs ) const
            precondition( obs ) // not null
    ) {
        return std::find(observers_.begin(), observers_.end(), obs) !=
                observers_.end();
    }

    // Commands.

    CONTRACT_FUNCTION( // Remember given object as an observer.
        public void (attach) ( (observer* const) obs )
            precondition(
                obs, // not null
                not attached(obs) // not already attached
            )
            postcondition(
                auto old_observers = CONTRACT_OLDOF observers(),
                attached(obs), // attached
                other_observers_unchanged(old_observers, observers(), obs),
                        // others not changed (frame rule)
                        requires O_N <= COMPLEXITY_MAX
            )
    ) {
        observers_.push_back(obs);
    }

    // Queries.

    CONTRACT_FUNCTION( // All observers attached to this subject.
        protected (std::list<observer const*>) (observers) ( void ) const
    ) {
        // Create list of pointers to const observers.
        std::list<const observer*> obs;
        for(std::list<observer*>::const_iterator
                i = observers_.begin(); i != observers_.end(); ++i) {
            obs.push_back(*i);
        }
        return obs;
    }

    // Commands.

    CONTRACT_FUNCTION( // Update all attached observers.
        protected void (notify) ( void )
            postcondition( all_observers_updated(observers()) ) // all updated
    ) {
        for(std::list<observer*>::iterator
                i = observers_.begin(); i != observers_.end(); ++i) {
            // Class invariant ensures no null pointers in observers but
            // class invariants not checked for non-public members so check.
            CONTRACT_BLOCK_INVARIANT( const( i ) 0 != *i ) // pointer not null
            (*i)->update();
        }
    }

    // Contract helpers.

    CONTRACT_FUNCTION(
        private static bool (all_observers_valid) (
                (std::list<observer const*> const&) observers )
    ) {
        for(std::list<observer const*>::const_iterator
                i = observers.begin(); i != observers.end(); ++i) {
            if(!(*i)) return false;
        }
        return true;
    }
            
    CONTRACT_FUNCTION(
        private bool (other_observers_unchanged) (
                (std::list<observer const*> const&) old,
                (std::list<observer const*> const&) now,
                (observer const*) obs
            ) const
            precondition( obs ) // not null
    ) {
        std::list<observer const*> remaining = now;
        std::remove(remaining.begin(), remaining.end(), obs);

        std::list<observer const*>::const_iterator 
                remaining_it = remaining.begin();
        std::list<observer const*>::const_iterator old_it = old.begin();
        while(remaining.end() != remaining_it && old.end() != old_it) {
            if(*remaining_it != *old_it) return false;
            ++remaining_it;
            ++old_it;
        }
        return true;
    }

    CONTRACT_FUNCTION(
        private bool (all_observers_updated) (
                (std::list<observer const*> const&) observers ) const
    ) {
        for(std::list<observer const*>::const_iterator
                i = observers.begin(); i != observers.end(); ++i) {
            if(!(*i)) return false;
            if(!(*i)->up_to_date_with_subject()) return false;
        }
        return true;
    }
    
    private: std::list<observer*> observers_;
};

#endif // #include guard
//]

