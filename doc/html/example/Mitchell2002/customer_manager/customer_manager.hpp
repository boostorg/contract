// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Contract example (ported from Eiffel code).

#ifndef CUSTOMER_MANAGE_HPP_
#define CUSTOMER_MANAGE_HPP_

#include <contract.hpp>
#include <string>
#include <map>

/** Basic customer information. */
class basic_customer_details {
    friend class customer_manager;

public:
    /** Identifier type. */
    typedef std::string identifier;

    /** Construct basic customer information. */
    explicit basic_customer_details(const identifier& the_id):
            id(the_id), name(), address(), birthday() {}
    
protected:
    /** Customer identifier. */
    identifier id;
    /** Customer name. */
    std::string name;
    /** Customer address. */
    std::string address;
    /** Customer date of birth. */
    std::string birthday;
};

/** Manage customers. */
class customer_manager {

    CONTRACT_INVARIANT( ({
        CONTRACT_ASSERT( count() >= 0 );
    }) )

public:
    // Construction //

    customer_manager(void): customers_()
    CONTRACT_CONSTRUCTOR( (class) (customer_manager)
            (public) (customer_manager)( (void) )
    (body) (
        ;
    ) )

    virtual ~customer_manager(void)
    CONTRACT_DESTRUCTOR( (class) (customer_manager)
            (public) (customer_manager)( (void) )
    (body) (
        ;
    ) )

    // Basic Queries //

    /** Number of customers. */
    int count(void) const
    CONTRACT_FUNCTION( (class) (customer_manager)
            (public) (int) (count)( (void) ) (const)
    (postcondition) (result) ({
        CONTRACT_ASSERT( result >= 0 );
    })
    (body) (
        ;
    ) )

    /** There is a customer with given identifier. */
    bool id_active(const basic_customer_details::identifier& id)
            const
    CONTRACT_FUNCTION( (class) (customer_manager)
            (public) (bool) (id_active)(
                    (const basic_customer_details::identifier&)(id) )
            (const)
    (body) (
        ;
    ) )

    // Derived Queries //

    /** Name of customer with given identifier. */
    const std::string& name_for(
            const basic_customer_details::identifier& id) const
    CONTRACT_FUNCTION( (class) (customer_manager)
            (public) (const std::string&) (name_for)(
                    (const basic_customer_details::identifier&)(id) )
            (const)
    (precondition) ({
        CONTRACT_ASSERT( id_active(id) );
    })
    (body) (
        ;
    ) )
    
    // Commands //

    /** Add given customer. */
    void add(const basic_customer_details& details)
    CONTRACT_FUNCTION( (class) (copyable)(customer_manager)
            (public) (void) (add)(
                    (const basic_customer_details&)(details) )
    (precondition) ({
        CONTRACT_ASSERT( !id_active(details.id) );
    })
    (postcondition) ({
        CONTRACT_ASSERT( count() ==
                (CONTRACT_OLDOF(this)->count() + 1) );
        CONTRACT_ASSERT( id_active(details.id) );
    })
    (body) (
        ;
    ) )

    /** Set name of customer with given identifier. */
    void set_name(const basic_customer_details::identifier& id,
            const std::string& name)
    CONTRACT_FUNCTION( (class) (customer_manager)
            (public) (void) (set_name)(
                    (const basic_customer_details::identifier&)(id)
                    (const std::string&)(name) )
    (precondition) ({
        CONTRACT_ASSERT( id_active(id) );
    })
    (postcondition) ({
        CONTRACT_ASSERT( name_for(id) == name );
    })
    (body) (
        ;
    ) )

private:
    /** Customer agent. */
    class agent {};

    /** Basic customer. */
    class customer: public basic_customer_details {
    public:
        /** Customer agent/ */
        agent managing_agent;
        /** Customer last contacted. */
        std::string last_contact;
        
        explicit customer(const basic_customer_details& details):
                basic_customer_details(details), managing_agent(),
                last_contact() {}
    };

    std::map<basic_customer_details::identifier, customer> customers_;
};

#endif // #include guard

