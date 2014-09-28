
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <string>

//[subcontract_pre_natural_failure
CONTRACT_CLASS(
    class (integer)
) {
    CONTRACT_CLASS_INVARIANT( void )

    CONTRACT_FUNCTION(
        public virtual void (set) ( int value )
            // No preconditions so this and all overrides can always be called.
            postcondition( get() == value )
    ) {
        value_ = value;
    }
    
    CONTRACT_FUNCTION(
        public virtual int (get) ( void ) const
    ) {
        return value_;
    }

    private: int value_;
};

CONTRACT_CLASS(
    class (natural) extends( public integer ) // Subcontract.
) {
    CONTRACT_CLASS_INVARIANT( get() >= 0 )

    CONTRACT_FUNCTION(
        public virtual void (set) ( int value )
            precondition( value >= 0 ) // NOTE: Will not fail because of base.
    ) {
        integer::CONTRACT_MEMBER_BODY(set)(value);
    }
};
//]

void throwing_handler ( contract::from const& context ) { throw; }

int main ( void )
{
    contract::set_class_invariant_broken(&throwing_handler);
    bool pass = false;
    try {
        //[subcontract_pre_natural_failure_call
        natural n;
        n.set(-123); // Error: Fails call invariants instead of preconditions.
        //]
    } catch(contract::broken& ex) {
        if(std::string(ex.assertion_code()) == std::string("get() >= 0"))
            pass = true;
    }
#ifndef CONTRACT_CONFIG_NO_CLASS_INVARIANTS
    BOOST_TEST(pass);
#endif
    return boost::report_errors();
}

