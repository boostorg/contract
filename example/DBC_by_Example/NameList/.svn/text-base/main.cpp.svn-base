/* $Id$ */

#include "names.hpp"
#include <iostream>

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

