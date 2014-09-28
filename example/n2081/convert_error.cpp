
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n2081_convert_error
// File: convert_error.cpp
#include "convert.hpp"

int main ( void )
{
    convert<int*>(10); // Error: Correctly cannot convert type.
    return 0;
}
//]

