
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[mitchell02_name_list
// File: name_list.cpp
#include "name_list.hpp"
#include <algorithm>

// name_list

CONTRACT_CONSTRUCTOR_BODY(name_list, name_list) ( void ) {}

CONTRACT_DESTRUCTOR_BODY(name_list, ~name_list) ( void ) {}

int CONTRACT_MEMBER_BODY(name_list, count) ( void ) const
    { return names_.size(); }

bool CONTRACT_MEMBER_BODY(name_list, has) ( std::string const& name ) const
    { return names_.end() != std::find(names_.begin(), names_.end(), name); }

void CONTRACT_MEMBER_BODY(name_list, put) ( std::string const& name )
    { names_.push_back(name); }

// relaxed_name_list

CONTRACT_CONSTRUCTOR_BODY(relaxed_name_list, relaxed_name_list) ( void ) {}

CONTRACT_DESTRUCTOR_BODY(relaxed_name_list, ~relaxed_name_list) ( void ) {}

void CONTRACT_MEMBER_BODY(relaxed_name_list, put) ( std::string const& name )
{
    // Must use `BODY` to call base functions (to avoid infinite recursion).
    if(!has(name)) CONTRACT_MEMBER_BODY(name_list, put)(name);
}
//]

