/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

/** @file
 * Impl body correctly (see body-err.cpp).
 */

#include "body.hpp"

void integer::DBC_BODY(set)(const int& i) { i_ = i; }

int integer::DBC_BODY(get)() const { 
    int i = i_; // OK (onle read mem var from const mem fun).
    return i;
}

