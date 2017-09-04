/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */
/* $Id$ */

#ifndef VIEW_OF_COUNTER_HPP_
#define VIEW_OF_COUNTER_HPP_

#include "../Observer/Observer.hpp"
#include "Counter.hpp"

/** Show current value of associated counter. */
class ViewOfCounter: private Observer DBC_MULTI_INHERIT_OBJECT(ViewOfCounter) {
public:
    // Creation //

    /** Create viewer associated to specified counter. */
    ViewOfCounter(Counter& counter): counter_(counter) {
        counter.attach(this);
        std::cout << "Counter started at " << counter_.value() << std::endl;
    }

private:
    bool upToDateWithSubject(void) const
    DBC_MEM_FUN( (private) (bool) (ViewOfCounter)DBC_BASE(Observer)
            (upToDateWithSubject)( (void) ) (const), {
    }, {
    }, { 
        return true; 
    })

    void update(void)
    DBC_MEM_FUN( (public) (void) (ViewOfCounter)DBC_BASE(Observer)
            (update)( (void) ), {
    }, {
    }, {
        std::cout << "Counter changed to " << counter_.value() << std::endl;
    })

    Counter& counter_;

    DBC_INVARIANT(ViewOfCounter, {})
};

#endif // VIEW_OF_COUNTER_HPP_

