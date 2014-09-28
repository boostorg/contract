
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[mitchell02_observer_main
// File: observer_main.cpp
#include "observer/observer.hpp"
#include "observer/subject.hpp"
#include <boost/detail/lightweight_test.hpp>
#include <contract.hpp>

int state_check; // For unit testing.

class concrete_subject : public subject // Implement an actual subject.
{
    public: typedef int state; // Some state being observed.

    public: concrete_subject ( void ) : state_() {}

    public: void set_state (state const& the_state) {
        state_ = the_state;
        BOOST_TEST(state_ == state_check);
        notify(); // Notify observers.
    }

    public: state get_state ( void ) const { return state_; }

    private: state state_;
};

CONTRACT_CLASS( // Implement of actual observer.
    class (concrete_observer) extends( public observer )
) {
    CONTRACT_CLASS_INVARIANT( void )

    CONTRACT_CONSTRUCTOR( // Create concrete observer.
        public explicit (concrete_observer) (
                (concrete_subject const&) the_subject )
            initialize( subject_(the_subject), observed_state_() )
    ) {}

    // Implement base virtual functions.

    CONTRACT_FUNCTION(
        private bool (up_to_date_with_subject) ( void ) const override final
    ) {
        return true; // For simplicity, always up-to-date.
    }

    CONTRACT_FUNCTION(
        private void (update) ( void ) override final
    ) {
        observed_state_ = subject_.get_state();
        BOOST_TEST(observed_state_ == state_check);
    }

    private: concrete_subject const& subject_;
    private: concrete_subject::state observed_state_;
};

int main ( void )
{
    concrete_subject sbj;
    concrete_observer ob(sbj);
    sbj.attach(&ob);
    sbj.set_state(state_check = 123);
    sbj.set_state(state_check = 456);
    return boost::report_errors();
}
//]

