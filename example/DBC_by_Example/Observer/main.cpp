/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */
/* $Id$ */

#include "Subject.hpp"
#include <dbc.hpp>
#include <iostream>

/** Implementation of abstract subject. */
class ConcreteSubject: public Subject {
public:
    /** State being observed. */
    typedef int State;

    ConcreteSubject(): state_() {}

    /** Set state being observed. */
    void setState(const State& state) {
        std::cout << "Changing state to " << state << std::endl;
        state_ = state;
        notify();
    }

    /** Get state being observed. */
    State getState() const { return state_; }

private:
    State state_;
};

/** Implementation of abstract observer. */
class ConcreteObserver: public Observer {
public:
    /** Creates concrete observer. */
    ConcreteObserver(const ConcreteSubject& subject): subject_(subject),
            observedState_() {}

private:
    bool upToDateWithSubject(void) const 
    DBC_MEM_FUN( (private) (bool) (ConcreteObserver)DBC_BASE(Observer)
            (upToDateWithSubject)( (void) ) (const), {
    }, {
    }, { 
        return true; 
    })

    void update(void)
    DBC_MEM_FUN( (private) (void) (ConcreteObserver)DBC_BASE(Observer)
            (update)( (void) ), {
    }, {
    }, {
        observedState_ = subject_.getState();
        std::cout << "Observed state " << observedState_ << std::endl;
    })

    const ConcreteSubject& subject_;
    ConcreteSubject::State observedState_;
};

/** Main program. */
int main() {
    ConcreteSubject s;
    ConcreteObserver o(s);

    std::cout << std::endl << "Attaching observer " << &o << "..." 
            << std::endl;
    s.attach(&o);

    ConcreteSubject::State st = -10;
    std::cout << std::endl << "Setting state to " << st << "..." << std::endl;
    s.setState(st);
    
    st = +10;
    std::cout << std::endl << "Re-setting state to " << st << "..." 
            << std::endl;
    s.setState(st);
    
    return 0;
}

