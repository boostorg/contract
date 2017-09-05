// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#include "stack3.hpp"
#include <iostream>
#include <string>

int main() {
    std::cout << std::endl << "constructor()" << std::endl;
    stack3<std::string> s(3);

    std::cout << std::endl << "count()" << std::endl;
    std::cout << s.count() << std::endl;
    
    std::cout << std::endl << "empty()" << std::endl;
    std::cout << s.empty() << std::endl;
    
    std::cout << std::endl << "full()" << std::endl;
    std::cout << s.full() << std::endl;
    
    std::cout << std::endl << "put()" << std::endl;
    s.put("Galileo");
    
    std::cout << std::endl << "capacity()" << std::endl;
    std::cout << s.capacity() << std::endl;
    
    std::cout << std::endl << "item()" << std::endl;
    std::cout << s.item() << std::endl;
    
    std::cout << std::endl << "remove()" << std::endl;
    s.remove();

    std::cout << std::endl << "destructor()" << std::endl;
    return 0;
}

