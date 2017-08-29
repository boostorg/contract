/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

// Makefile compiles this code with different DBC_CHECKING... #definitions.

// Always verbose logging for this test (so you can see what is checked).
#define DBC_CONFIG_LOG_LEVEL DBC_LOG_LEVEL_ALL

#include "number.hpp"
#include <iostream>

int main() {
    number<int> i(10);
    std::cout << (i / 4.321) << std::endl;

    return 0;
}

