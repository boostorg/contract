
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[mitchell02_courier_main
// File: courier_main.cpp
#include "courier.hpp"

int main ( void )
{
    courier c;
    different_courier dc;
    package cups(3.6, "store");
    package desk(7.2, "store");
    c.deliver(cups, "home");
    dc.deliver(desk, "office");
    return 0;
}
//]

