// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef VIEW_OF_COUNT_HPP_
#define VIEW_OF_COUNT_HPP_

#include "../observe/observe.hpp"
#include "counter.hpp"
#include <contract.hpp>
#include <iostream> // To view counter value on console.

/** Show current value of associated counter. */
class view_of_counter: private observer {

    CONTRACT_INVARIANT( ({}) )

public:
    // Creation //

    /** Create viewer associated with given counter. */
    view_of_counter(counter& the_counter): counter_ref_(the_counter)
    CONTRACT_CONSTRUCTOR( (class) (view_of_counter)
            (public) (view_of_counter)( (counter&)(the_counter) )
    (body) ({
        counter_ref_.attach(this);
        std::cout << std::endl << ">> Counter started at "
                << counter_ref_.value() << std::endl << std::endl;
    }) )

private:
    bool up_to_date_with_subject(void) const
    CONTRACT_FUNCTION( (class) (view_of_counter) (inherit)(observer)
            (private) (bool) (up_to_date_with_subject)( (void) ) (const)
    (body) ({
        return true; // For simplicity, always return true.
    }) )

    void update(void)
    CONTRACT_FUNCTION( (class) (view_of_counter) (inherit)(observer)
            (private) (void) (update)( (void) )
    (body) ({
        std::cout << std::endl << ">> Counter changed to "
                << counter_ref_.value() << std::endl << std::endl;
    }) )

    counter& counter_ref_;
};

#endif // #include guard

