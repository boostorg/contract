
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

//[mitchell02_subject
#ifndef SUBJECT_HPP_
#define SUBJECT_HPP_

#include "observer.hpp"
#include <boost/contract.hpp>
#include <vector>
#include <algorithm>
#include <cassert>

// Following used to selectively disable checking of more complex assertions.
#define O_1             0 // O(1): constant complexity.
#define O_N             1 // O(n): linear complexity.
#define COMPLEXITY_MAX  O_N

// Subject for observer design pattern.
class subject {
    friend class boost::contract::access;

    void invariant() const {
        #if O_N <= COMPLEXITY_MAX
            BOOST_CONTRACT_ASSERT(all_observers_valid(observers())); // Valid.
        #endif
    }

public:
    /* Creation */

    // Construct subject with no observer.
    subject() {
        // Check invariant.
        boost::contract::check c = boost::contract::constructor(this);
    }

    // Destroy subject.
    virtual ~subject() {
        // Check invariant.
        boost::contract::check c = boost::contract::destructor(this);
    }

    /* Queries */

    // If given object is attached.
    bool attached(observer const* ob) const {
        boost::contract::check c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(ob); // Not null.
            })
        ;

        return std::find(observers_.cbegin(), observers_.cend(), ob) !=
                observers_.cend();
    }

    /* Commands */

    // Attach given object as an observer.
    void attach(observer* ob) {
        boost::contract::old_ptr<std::vector<observer const*> > old_observers =
                BOOST_CONTRACT_OLDOF(observers());
        boost::contract::check c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(ob); // Not null.
                BOOST_CONTRACT_ASSERT(!attached(ob)); // Not already attached.
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(attached(ob)); // Attached.
                #if O_N <= COMPLEXITY_MAX
                    // Others not changed (frame rule).
                    BOOST_CONTRACT_ASSERT(other_observers_unchanged(
                            *old_observers, observers(), ob));
                #endif
            })
        ;

        observers_.push_back(ob);
    }

protected:
    // Contracts could have been omitted for protected/private with no pre/post.

    /* Queries */

    // All observers attached to this subject.
    std::vector<observer const*> observers() const {
        std::vector<observer const*> obs;
        for(std::vector<observer*>::const_iterator i = observers_.cbegin();
                i != observers_.cend(); ++i) {
            obs.push_back(*i);
        }
        return obs;
    }

    /* Commands */

    // Update all attached observers.
    void notify() {
        // Protected members use `function` (no inv and no subcontracting).
        boost::contract::check c = boost::contract::function()
            .postcondition([&] {
                #if O_N <= COMPLEXITY_MAX
                    // All updated.
                    BOOST_CONTRACT_ASSERT(all_observers_updated(observers()));
                #endif
            })
        ;
        
        for(std::vector<observer*>::iterator i = observers_.begin();
                i != observers_.end(); ++i) {
            // Class invariants ensure no null pointers in observers but class
            // invariants not checked for non-public functions so assert here.
            assert(*i); // Pointer not null (defensive programming).
            (*i)->update();
        }
    }

private:
    /* Contract Helpers */

    static bool all_observers_valid(std::vector<observer const*> const& obs) {
        for(std::vector<observer const*>::const_iterator i = obs.cbegin();
                i != obs.cend(); ++i) {
            if(!*i) return false;
        }
        return true;
    }

    static bool other_observers_unchanged(
        std::vector<observer const*> const& old_obs,
        std::vector<observer const*> const& new_obs,
        observer const* ob
    ) {
        // Private members use `function` (no inv and no subcontracting).
        boost::contract::check c = boost::contract::function()
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(ob); // Not null.
            })
        ;

        std::vector<observer const*> remaining = new_obs;
        std::remove(remaining.begin(), remaining.end(), ob);

        std::vector<observer const*>::const_iterator remaining_it =
                remaining.begin();
        std::vector<observer const*>::const_iterator old_it = old_obs.begin();
        while(remaining.cend() != remaining_it && old_obs.cend() != old_it) {
            if(*remaining_it != *old_it) return false;
            ++remaining_it;
            ++old_it;
        }
        return true;
    }

    static bool all_observers_updated(std::vector<observer const*> const& obs) {
        for(std::vector<observer const*>::const_iterator i = obs.cbegin();
                i != obs.cend(); ++i) {
            if(!*i) return false;
            if(!(*i)->up_to_date_with_subject()) return false;
        }
        return true;
    }

    std::vector<observer*> observers_;
};

#endif // #include guard
//]

