// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#include "observe.hpp"
#include <contract.hpp>
#include <iostream>

/** Implement an actual subject. */
class concrete_subject: public subject {
public:
    /** State being observed. */
    typedef int state;

    concrete_subject(): state_() {}

    /** Set state being observed. */
    void set_state(const state& the_state) {
        std::cout << "Changing state to " << the_state << std::endl;
        state_ = the_state;
        notify(); // Notify observers.
    }

    /** Get state being observed. */
    state get_state() const { return state_; }

private:
    state state_;
};

/** Implement of actual observer. */
class concrete_observer: public observer {
public:
    /** Create concrete observer. */
    concrete_observer(const concrete_subject& the_subject):
            subject_(the_subject), observed_state_() {}

private:
    bool up_to_date_with_subject(void) const 
    CONTRACT_FUNCTION( (class) (concrete_observer) (inherit)(observer)
            (private) (bool) (up_to_date_with_subject)( (void) )
            (const)
    (body) ({
        return true; // For simplicity, always true.
    }) )

    void update(void)
    CONTRACT_FUNCTION( (class) (concrete_observer) (inherit)(observer)
            (private) (void) (update)( (void) )
    (body) ({
        observed_state_ = subject_.get_state();
        std::cout << "Observed state " << observed_state_
                << std::endl;
    }) )

    const concrete_subject& subject_;
    concrete_subject::state observed_state_;
};

int main() {
    std::cout << std::endl << "Constructing objects" << std::endl;
    concrete_subject sbj;
    concrete_observer ob(sbj);

    std::cout << std::endl << "Attaching observer " << &ob
            << std::endl;
    sbj.attach(&ob);

    concrete_subject::state st = -10;
    std::cout << std::endl << "Setting state to " << st << std::endl;
    sbj.set_state(st);
    
    st = +10;
    std::cout << std::endl << "Re-setting state to " << st << std::endl;
    sbj.set_state(st);

    std::cout << std::endl << "Destructing objects" << std::endl;
    return 0;
}

