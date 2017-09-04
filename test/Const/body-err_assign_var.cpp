/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

/** @file
 * Impl body with an error assigning mem var from const mem fun which must
 * fail at compile time (see body-ok.cpp)/
 */

#include "body.hpp"

void integer::DBC_BODY(set)(const int& i) { i_ = i; }

int integer::DBC_BODY(get)() const {
    i_ = -1; // Must fail at compile-time (assign mem var from const mem fun).
    return i_; 
}

