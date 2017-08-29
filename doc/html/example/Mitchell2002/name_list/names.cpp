// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#include "names.hpp"
#include <algorithm>

// name_list //

CONTRACT_CONSTRUCTOR_BODY(name_list, name_list)(void) {}

CONTRACT_DESTRUCTOR_BODY(name_list, ~name_list)(void) {}

bool name_list::CONTRACT_BODY(has)(const std::string& name) const {
    std::clog << "base has\n";
    return names_.end() != std::find(names_.begin(), names_.end(),
            name);
}

unsigned int name_list::CONTRACT_BODY(count)(void) const {
    std::clog << "base count\n";
    return names_.size();
}

void name_list::CONTRACT_BODY(put)(const std::string& name) {
    std::clog << "base put\n";
    names_.push_back(name);
}

// relaxed_name_list //

CONTRACT_CONSTRUCTOR_BODY(relaxed_name_list, relaxed_name_list)(
        void) {}

CONTRACT_DESTRUCTOR_BODY(relaxed_name_list, ~relaxed_name_list)(
        void) {}

void relaxed_name_list::CONTRACT_BODY(put)(const std::string& name) {
    std::clog << "dervied put\n";
    if (!has(name)) {
        // Base class operations must be called via BODY macro.
        name_list::CONTRACT_BODY(put)(name);
        // name_list::put(name); // ERROR: causes infinite recursion.
    }
}

