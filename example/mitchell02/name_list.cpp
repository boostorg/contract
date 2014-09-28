
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

int name_list::CONTRACT_MEMBER_BODY(count) ( void ) const
    { return names_.size(); }

bool name_list::CONTRACT_MEMBER_BODY(has) ( std::string const& name ) const
    { return names_.end() != std::find(names_.begin(), names_.end(), name); }

void name_list::CONTRACT_MEMBER_BODY(put) ( std::string const& name )
    { names_.push_back(name); }

// relaxed_name_list

CONTRACT_CONSTRUCTOR_BODY(relaxed_name_list, relaxed_name_list) ( void ) {}

CONTRACT_DESTRUCTOR_BODY(relaxed_name_list, ~relaxed_name_list) ( void ) {}

void relaxed_name_list::CONTRACT_MEMBER_BODY(put) ( std::string const& name )
{
    // Must use `BODY` to call base functions (to avoid infinite recursion).
    if(!has(name)) name_list::CONTRACT_MEMBER_BODY(put)(name);
}
//]

