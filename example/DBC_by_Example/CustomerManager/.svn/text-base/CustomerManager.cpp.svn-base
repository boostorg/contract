/* $Id$ */

#include "CustomerManager.hpp"

int CustomerManager::DBC_BODY(count)() const { return customers_.size(); }

bool CustomerManager::DBC_BODY(idActive)(const Customer::Id& id) const 
    { return customers_.end() != customers_.find(id); }

void CustomerManager::DBC_BODY(add)(const BasicCustomerDetails& customer)
    { customers_[customer.id] = Customer(customer); }

std::string CustomerManager::DBC_BODY(nameFor)(const Customer::Id& id) const
    { return customers_.find(id)->second.name; }

void CustomerManager::DBC_BODY(setName)(const Customer::Id& id, 
        const std::string& name) {
    customers_[id].name = name; 
}

