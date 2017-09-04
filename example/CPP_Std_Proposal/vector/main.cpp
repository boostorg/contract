/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include "vector.hpp"
#include <iostream>

int main() {
    std::allocator<double> al;
    
    dbc::vector<double> v0;
    std::cout << "#v0 = " << v0.size() << std::endl << std::endl;

    dbc::vector<double> v1(al);
    std::cout << "#v1 = " << v1.size() << std::endl << std::endl;
    
    dbc::vector<double> v2(5);
    std::cout << "#v2 = " << v2.size() << std::endl << std::endl;
    
    dbc::vector<double> v3(5, -1.0);
    std::cout << "#v3 = " << v3.size() << std::endl << std::endl;
    
    dbc::vector<double> v4(5, -1.0, al);
    std::cout << "#v4 = " << v4.size() << std::endl << std::endl;
    
    dbc::vector<double> v5(v4);
    std::cout << "#v5 = " << v5.size() << std::endl << std::endl;

    v5.reserve(10);
    std::cout << "v5 reserved 10 " << std::endl << std::endl;
    
    std::cout << "v5 capacity = " << v5.capacity() << std::endl << std::endl;
    
    v5.resize(15);
    std::cout << "v5 resized to 15 " << std::endl << std::endl;
    
    v5.resize(30, +1.23);
    std::cout << "v5 resized to 15 " << std::endl << std::endl;

    return 0;
}

