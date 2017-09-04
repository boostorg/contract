/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */
/* $Id$ */

#include "Stack3.hpp"
#include <iostream>
#include <string>

int main() {
    std::cout << std::endl << "init()..." << std::endl;
    Stack3<std::string> s(3);

    std::cout << std::endl << "count()..." << std::endl;
    std::cout << s.count() << std::endl;
    
    std::cout << std::endl << "empty()..." << std::endl;
    std::cout << s.empty() << std::endl;
    
    std::cout << std::endl << "full()..." << std::endl;
    std::cout << s.full() << std::endl;
    
    std::cout << std::endl << "put()..." << std::endl;
    s.put("Galileo Galilei");
    
    std::cout << std::endl << "capacity()..." << std::endl;
    std::cout << s.capacity() << std::endl;
    
    std::cout << std::endl << "item()..." << std::endl;
    std::cout << s.item() << std::endl;
    
    std::cout << std::endl << "remove()..." << std::endl;
    s.remove();

    std::cout << std::endl << "del()..." << std::endl;
    return 0;
}

