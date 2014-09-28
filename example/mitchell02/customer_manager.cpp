
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[mitchell02_customer_manager
// File: customer_manager.cpp
#include "customer_manager.hpp"
#include <utility>

CONTRACT_CONSTRUCTOR_BODY(customer_manager, customer_manager) ( void ) {}

CONTRACT_DESTRUCTOR_BODY(customer_manager, ~customer_manager) ( void ) {}

int customer_manager::CONTRACT_MEMBER_BODY(count) ( void ) const
    { return customers_.size(); }

bool customer_manager::CONTRACT_MEMBER_BODY(id_active) (
        basic_customer_details::identifier const& id) const
{
    return customers_.find(id) != customers_.end();
}

std::string const& customer_manager::CONTRACT_MEMBER_BODY(name_for) (
        basic_customer_details::identifier const& id) const
{
    // Find != end because of `id_active()` pre so no defensive programming.
    return customers_.find(id)->second.name;
}

void customer_manager::CONTRACT_MEMBER_BODY(add) (
        basic_customer_details const& details )
    { customers_.insert(std::make_pair(details.id, customer(details))); }

void customer_manager::CONTRACT_MEMBER_BODY(set_name) (
        basic_customer_details::identifier const& id,
        std::string const& name )
{
    // Find != end because of `id_active()` pre so no defensive programming.
    customers_.find(id)->second.name = name;
}
//]

