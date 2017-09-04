/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include "String.hpp"
#include <iostream>

/** Main program. */
int main() {
    std::cout << std::endl << "init()..." << std::endl;
    String s("Galileo Galilei");

    std::cout << std::endl << "operator[](0)..." << std::endl;
    std::cout << s[0] << std::endl;

    std::cout << std::endl << "del()..." << std::endl;
    return 0;
}

