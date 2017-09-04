/* $Id$ */

#include "names.hpp"
#include <algorithm>

bool NameList::DBC_BODY(has)(const std::string& name) const 
    { return names_.end() != std::find(names_.begin(), names_.end(), name); }

unsigned int NameList::DBC_BODY(count)() const { return names_.size(); }

void NameList::DBC_BODY(put)(const std::string& name) 
    { names_.push_back(name); }

void RelaxedNameList::DBC_BODY(put)(const std::string& name) { 
    if (!has(name)) {
        /** @note When invoking base class implementation of derived member 
         * function, you must use the DBC_BODY() qualifier to avoid infinite
         * contract checking recursion. In this case, "NameList::put(name);" 
         * would have caused an infinite recursion. */
        NameList::DBC_BODY(put)(name); 
    }
}

