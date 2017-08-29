/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */
/* $Id$ */

#include "Dictionary.hpp"
#include <string>
#include <iostream>

int main() {
    std::cout << std::endl << "init()..." << std::endl;
    Dictionary<std::string, int> ages;

    std::cout << std::endl << "has()..." << std::endl;
    std::cout << ages.has("Galileo Galilei") << std::endl;
    
    std::cout << std::endl << "put()..." << std::endl;
    ages.put("Galileo Galilei", 400);
    
    std::cout << std::endl << "valueFor()..." << std::endl;
    std::cout << ages.valueFor("Galileo Galilei") << std::endl;
    
    std::cout << std::endl << "count()..." << std::endl;
    std::cout << ages.count() << std::endl;
    
    std::cout << std::endl << "remove()..." << std::endl;
    ages.remove("Galileo Galilei");
    
    std::cout << std::endl << "del()..." << std::endl;
    return 0;
}

