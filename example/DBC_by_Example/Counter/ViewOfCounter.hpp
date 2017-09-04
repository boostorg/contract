/* $Id$ */

#ifndef VIEW_OF_COUNTER_HPP_
#define VIEW_OF_COUNTER_HPP_

#include "../Observer/Observer.hpp"
#include "Counter.hpp"

/** Show current value of associated counter. */
class ViewOfCounter: private Observer DBC_TRAILING_OBJECT(ViewOfCounter) {
public:
    // Creation //

    /** Create viewer associated to specified counter. */
    ViewOfCounter(Counter& counter): counter_(counter) {
        counter.attach(this);
        std::cout << "Counter started at " << counter_.value() << std::endl;
    }

private:
    bool upToDateWithSubject() const
    DBC_MEM_FUN( (private) (bool) (ViewOfCounter)DBC_BASE(Observer)
            (upToDateWithSubject)() (const), {
    }, {
    }, { 
        return true; 
    })

    void update()
    DBC_MEM_FUN( (public) (void) (ViewOfCounter)DBC_BASE(Observer)
            (update)(), {
    }, {
    }, {
        std::cout << "Counter changed to " << counter_.value() << std::endl;
    })

    Counter& counter_;

    DBC_INVARIANT(ViewOfCounter, {})
};

#endif // VIEW_OF_COUNTER_HPP_

