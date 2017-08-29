// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#include "dictionary.hpp"
#include <string>
#include <iostream>

int main() {
    std::cout << std::endl << "constructor()" << std::endl;
    dictionary<std::string, int> ages;

    std::cout << std::endl << "has()" << std::endl;
    std::cout << ages.has("Galileo") << std::endl;
    
    std::cout << std::endl << "put()" << std::endl;
    ages.put("Galileo", 78);
    
    std::cout << std::endl << "value_for()" << std::endl;
    std::cout << ages.value_for("Galileo") << std::endl;
    
    std::cout << std::endl << "count()" << std::endl;
    std::cout << ages.count() << std::endl;
    
    std::cout << std::endl << "remove()" << std::endl;
    ages.remove("Galileo");
    
    std::cout << std::endl << "destructor()" << std::endl;
    return 0;
}

