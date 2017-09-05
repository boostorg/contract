// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#include "myvector.hpp"
#include <iostream>

int main() {
    std::cout << std::endl << "constructor()" << std::endl;
    myvector<double> v(3);
    const myvector<double>& cv = v; // A reference, no copy.
    
    std::cout << std::endl << "copy constructor()" << std::endl;
    myvector<double> w(v);
    
    std::cout << std::endl << "begin()" << std::endl;
    myvector<double>::iterator b = v.begin();
    std::cout << *b << std::endl;
    
    std::cout << std::endl << "begin() const" << std::endl;
    myvector<double>::const_iterator cb = cv.begin();
    std::cout << *cb << std::endl;
    
    std::cout << std::endl << "insert()" << std::endl;
    v.insert(b, 2, -3.21);
    
    std::cout << std::endl << "operator[]" << std::endl;
    double v0 = v[0];
    std::cout << v0 << std::endl;
    
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

