/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */
/* $Id$ */

#include "names.hpp"
#include <iostream>

/** Main program. */
int main() {
    std::cout << std::endl << "init()..." << std::endl;
    std::string n;
    NameList nl;
    RelaxedNameList rl;

    n = "Leonardo Da Vinci";
    std::cout << std::endl << "put()..." << std::endl;
    nl.put(n);

    n = "Galileo Galilei";
    std::cout << std::endl << "put()..." << std::endl;
    rl.put(n);
    std::cout << std::endl 
            << "put() again (allowed by RelaxedNameList only)..." << std::endl;
    rl.put(n);

    std::cout << std::endl << "del()..." << std::endl;
    return 0;
}

