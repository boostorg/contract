/* $Id$ */

#include "couriers.hpp"
#include <iostream>

int main() {
    {
        std::cout << std::endl << "Init Courier..." << std::endl;
        Courier c;
        {
            std::cout << std::endl << "Init DifferentCourier..." << std::endl;
            DifferentCourier dc;
            Package cups(3.6, "store");
            Package desk(7.2, "store");
            
            std::cout << std::endl << "Delivering some cups home "
                    << "(no base pre/post/invariant checks)..." << std::endl;
            c.deliver(cups, "home");

            std::cout << std::endl << "Delivering a desk to the office "
                    << "(base pre/post/invariant checks)..." << std::endl;
            dc.deliver(desk, "office");

            std::cout << std::endl << "Del DifferentCourier..." << std::endl;
        }
        std::cout << std::endl << "Del Courier..." << std::endl;
    }
    return 0;
}

