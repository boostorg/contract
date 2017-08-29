// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#include "myvector_nomacros.hpp"
#include <iostream>

int main() {
    std::cout << std::endl << "constructor()" << std::endl;
    myvector<double> v(3);
    
    std::cout << std::endl << "push_back()" << std::endl;
    v.push_back(1.23);
    
    std::cout << std::endl << "all_equals()" << std::endl;
    bool eq = myvector<double>::all_equals(v.begin(), v.end(), 1.23);
    std::cout << eq << std::endl; // It will be false.
    
    std::cout << std::endl << "abs_total()" << std::endl;
    double tot = abs_total(v);
    std::cout << tot << std::endl;
    
    std::cout << std::endl << "destructor()" << std::endl;
    return 0;
}

