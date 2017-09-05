// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#include "string.hpp"

CONTRACT_CONSTRUCTOR_BODY(String, String)(const char* q) {
    sz = strlen(q);
    p = new char[sz + 1];
    for (int i = 0; i < sz; ++i) p[i] = q[i];
    p[sz] = '\0';
}

CONTRACT_DESTRUCTOR_BODY(String, ~String)(void) { delete[] p; }

char& String::CONTRACT_BODY(operator([], at))(int i) {
    // check invariant and preconditions on entry
    return p[i]; // do work
    // check invariant on exit
}

int String::CONTRACT_BODY(size)(void) { return sz; }

