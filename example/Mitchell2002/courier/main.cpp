// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#include "couriers.hpp"
#include <iostream>

int main() {
    std::cout << std::endl << "courier constructor" << std::endl;
    courier c;
    {
        std::cout << std::endl << "different courier constructor"
                << std::endl;
        different_courier dc;

        package cups(3.6, "store");
        package desk(7.2, "store");
        
        std::cout << std::endl << "courier delivers cups home"
                << std::endl;
        c.deliver(cups, "home");

        std::cout << std::endl << "different courier delivers desk "
                << "to office" << std::endl;
        dc.deliver(desk, "office");

        std::cout << std::endl << "different courier destructor"
                << std::endl;
    }
    std::cout << std::endl << "courier destructor" << std::endl;
    return 0;
}

