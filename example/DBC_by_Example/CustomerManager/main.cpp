/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */
/* $Id$ */

#include "CustomerManager.hpp"

int main() {
    std::cout << "init()..." << std::endl;
    CustomerManager mgr;
    
    BasicCustomerDetails c("sci", "Leonardo Da Vinci", 
            "Florence, Italy", "Year 1452");
    std::cout << std::endl << "add()..." << std::endl;
    mgr.add(c);

    std::cout << std::endl << "setName()..." << std::endl;
    mgr.setName("sci", "Galileo Galileo");
    
    std::cout << std::endl << "nameFor()..." << std::endl;
    std::cout << mgr.nameFor("sci");

    std::cout << std::endl << "count()..." << std::endl;
    std::cout << mgr.count() << std::endl;
    
    std::cout << std::endl << "idActive()..." << std::endl;
    std::cout << mgr.idActive("sci") << std::endl;

    std::cout << std::endl << "del()..." << std::endl;
    return 0;
}

