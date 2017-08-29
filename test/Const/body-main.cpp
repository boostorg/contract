/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include "body.hpp"
#include <iostream>

int main() {
    integer i;
    i.set(-10);
    std::cout << i.get() << std::endl;

    return 0;
}

