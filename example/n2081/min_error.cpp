
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n2081_min_error
// File: min_error.cpp
#include "min.hpp"

struct num
{
    int value;
    explicit num ( int v = 0 ) : value(v) {}
};

int main ( void )
{
    min(num(1), num(2)); // Compiler error: Fail concept requirements.
    return 0;
}
//]

