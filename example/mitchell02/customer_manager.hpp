
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[mitchell02_customer_manager_header
// File: customer_manager.hpp
#ifndef CUSTOMER_MANAGER_HPP_
#define CUSTOMER_MANAGER_HPP_

#include <contract.hpp>
#include <string>
#include <map>

class basic_customer_details // Basic customer information.
{
    friend class customer_manager;

    public: typedef std::string identifier;
    
    public: explicit basic_customer_details ( identifier const& an_id )
        : id(an_id), name(), address(), birthday()
    {}

    protected: identifier id; // Customer identifier.
    protected: std::string name; // Customer name.
    protected: std::string address; // Customer address.
    protected: std::string birthday; // Customer date of birth.
};

CONTRACT_CLASS( // Manage customers.
    class (customer_manager)
) {
    CONTRACT_CLASS_INVARIANT( count() >= 0 ) // non-negative count

    // Creation.

    CONTRACT_CONSTRUCTOR(
        public (customer_manager) ( void )
            // LIMITATION: Cannot use member initializes because deferring
            // body definition.
    ) ; // Deferred body definition.

    CONTRACT_DESTRUCTOR(
        public virtual (~customer_manager) ( void )
    ) ;

    // Basic queries.

    CONTRACT_FUNCTION(
        public int (count) ( void ) const
            // postcondition: non-negative count asserted by class invariants
    ) ;

    CONTRACT_FUNCTION( // There is a customer with given identifier.
        public bool (id_active) (
                (basic_customer_details::identifier const&) id ) const
    ) ;

    // Derived queries.

    CONTRACT_FUNCTION( // Name of customer with given identifier.
        public (std::string const&) (name_for) (
                (basic_customer_details::identifier const&) id ) const
            precondition( id_active(id) ) // id active
    ) ;

    // Commands.

    CONTRACT_FUNCTION( // Add given customer.
        public void (add) ( (basic_customer_details const&) details )
            precondition( not id_active(details.id) ) // id not active
            postcondition(
                auto old_count = CONTRACT_OLDOF count(),
                count() == old_count + 1, // count increased
                id_active(details.id) // id active
            )
    ) ;

    CONTRACT_FUNCTION( // Set name of customer with given identifier.
        public void (set_name) (
                (basic_customer_details::identifier const&) id,
                (std::string const&) name
            )
            precondition( id_active(id) ) // id active
            postcondition( name_for(id) == name ) // name set
    ) ;

    private: class agent {}; // Customer agent.

    private: struct customer : basic_customer_details // Basic customer.
    {
        public: agent managing_agent; // Customer agent.
        public: std::string last_contact; // Customer last contacted.

        public: explicit customer ( basic_customer_details const& details )
            : basic_customer_details(details), managing_agent(),
                    last_contact()
        {}
    };

    private: std::map<basic_customer_details::identifier, customer> customers_;
};

#endif // #include guard
//]

