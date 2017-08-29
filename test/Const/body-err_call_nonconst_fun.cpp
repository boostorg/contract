/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

/** @file
 * Compiler error -- attempting to call non-const mem fun from const body.
 */

#include "body.hpp"

void integer::DBC_BODY(set)(const int& i) { i_ = i; }

int integer::DBC_BODY(get)() const {
    set(-1); // Must fail.
    return i_; 
}

