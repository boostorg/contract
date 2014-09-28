
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n2081_add_error
// File: add_error.cpp
#include "add.hpp"

struct num
{
    int value;
    num ( int v = 0 ) : value(v) {};
};

int main ( void )
{
    num n(10), m(20);
    add(n, m); // Error: Correctly fails `add` concept requirements.
    return 0;
}
//]

