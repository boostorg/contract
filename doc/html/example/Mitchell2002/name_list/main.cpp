// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#include "names.hpp"

int main() {
    std::string n = "Galileo";
    
    std::cout << std::endl << "constructor()" << std::endl;
    name_list nl;
    relaxed_name_list rl;

    std::cout << std::endl << "put()" << std::endl;
    rl.put(n);
    std::cout << std::endl << "put() again (allowed)" << std::endl;
    rl.put(n);
    
    std::cout << std::endl << "put()" << std::endl;
    nl.put(n);
    std::cout << std::endl << "put() again (not allowed)" << std::endl;
    nl.put(n);

    std::cout << std::endl << "destructor()" << std::endl;
    return 0;
}

