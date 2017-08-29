// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#include "string.hpp"
#include <iostream>

int main() {
    std::cout << std::endl << "constructor()" << std::endl;
    String s("Galileo");

    std::cout << std::endl << "operator[]" << std::endl;
    std::cout << s[0] << std::endl;

    std::cout << std::endl << "destructor()" << std::endl;
    return 0;
}

