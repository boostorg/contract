/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include "template_subcontracts_template.hpp"
#include <iostream>

int main() {
    derived<int> d;
    std::cout << d.f(-10) << std::endl;
    std::cout << d.f_m(-10) << std::endl;

    return 0;
}

