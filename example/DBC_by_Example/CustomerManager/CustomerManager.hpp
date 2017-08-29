/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */
/* $Id$ */

#ifndef CUSTOMER_MANAGER_HPP_
#define CUSTOMER_MANAGER_HPP_

#include <dbc.hpp>
#include <iostream>
#include <string>
#include <map>

/** Bsic customer information. */
class BasicCustomerDetails {
public:
    /** Identifier type. */
    typedef std::string Id;

    /** Customer identifier. */
    Id id;
    /** Customer name. */
    std::string name;
    /** Customer address. */
    std::string address;
    /** Customer birthday. */
    std::string dateOfBirth;
    
    /** Construct basic customer information with specified initial values. */
    BasicCustomerDetails(const Id& theId = "", const std::string& theName = "",
            const std::string& theAddress = "", 
            const std::string& theDateOfBirth = ""):
            id(theId), name(theName), address(theAddress), 
            dateOfBirth(theDateOfBirth) {}
};

/** Basic customer agent. */
class Agent {};

/** Basic customer. */
class Customer: public BasicCustomerDetails {
public:
    /** Customer agent. */
    Agent managingAgent;
    /** Customer last contacted. */
    std::string lastContact;
    
    /** Construct customer with specified initial informations. */
    Customer(const BasicCustomerDetails& basic = BasicCustomerDetails()): 
            BasicCustomerDetails(basic), managingAgent(), lastContact() {}
};

/** Manage customers. */
class CustomerManager DBC_INHERIT_OBJECT(CustomerManager) {
public:
    CustomerManager(): customers_()
    DBC_CONSTRUCTOR( (public) (CustomerManager)(), {
    }, {
    }, {})

    virtual ~CustomerManager()
    DBC_DESTRUCTOR( (public) (virtual) (CustomerManager)(), {})

    // Basic Queries //

    /** Return number of customers. */
    int count() const
    DBC_MEM_FUN( (public) (int) (CustomerManager) (count)() (const), {
    }, {
    }, ;)

    /** Is there a customer with specified ID. */
    bool idActive(const Customer::Id& id) const
    DBC_MEM_FUN( (public) (bool) (CustomerManager) 
            (idActive)( (const Customer::Id&)(id) ) (const), {
    }, {
    }, ;)
    
    // Derived Queries //

    /** Return name of the customer with specified ID. */
    std::string nameFor(const Customer::Id& id) const
    DBC_MEM_FUN( (public) (std::string) (CustomerManager) 
            (nameFor)( (const Customer::Id&)(id) ) (const), {
        DBC_ASSERT(self.idActive(id), "id active");
    }, {
    }, ;) 

    // Commands //

    /** Add the specified customer. */
    void add(const BasicCustomerDetails& customer)
    DBC_MEM_FUN( (public) (void) DBC_COPYABLE(CustomerManager)
            (add)( (const BasicCustomerDetails&)(customer) ), {
        DBC_ASSERT(!self.idActive(customer.id), "id not already active");
    }, {
        DBC_ASSERT(self.now.count() == (self.old.count() + 1), 
                "count increased");
        DBC_ASSERT(self.now.idActive(customer.now.id), "id now active");
    }, ;)

    /** Set name of the customer with speficied ID. */
    void setName(const Customer::Id& id, const std::string& name) 
    DBC_MEM_FUN( (public) (void) (CustomerManager) (setName)
            ( (const Customer::Id&)(id) (const std::string&)(name) ), {
        DBC_ASSERT(self.idActive(id), "id active");
    }, {
        DBC_ASSERT(self.now.nameFor(id.now) == name.now, "name set");
    }, ;)

private:
    std::map<Customer::Id, Customer> customers_;
    
    DBC_INVARIANT(CustomerManager, {
        DBC_ASSERT(self.count() >= 0, "count never negative");
    })
};

#endif // CUSTOMER_MANAGER_HPP_

