/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include "Stack.hpp"
#include <string>
#include <iostream>

/** Main program. */
int main() {
    std::cout << std::endl << "init()..." << std::endl;
    Stack<std::string> s;

    std::cout << std::endl << "count()..." << std::endl;
    std::cout << "Stack has " << s.count() << " elements." << std::endl;
    
    std::cout << std::endl << "put()..." << std::endl;
    s.put("Galileo Galilei");
    
    std::cout << std::endl << "itemAt()..." << std::endl;
    std::cout << s.itemAt(1) << std::endl;
    
    std::cout << std::endl << "item()..." << std::endl;
    std::cout << s.item() << std::endl;
    
    std::cout << std::endl << "remove()..." << std::endl;
    s.remove();
    
    std::cout << std::endl << "isEmpty()..." << std::endl;
    std::cout << s.isEmpty() << std::endl;

    std::cout << std::endl << "del()..." << std::endl;

    return 0;
}

