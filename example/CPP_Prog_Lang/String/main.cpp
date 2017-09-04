
#include "String.hpp"
#include <iostream>

int main() {
    std::cout << std::endl << "init()..." << std::endl;
    String s("Galileo Galilei");

    std::cout << std::endl << "operator[](0)..." << std::endl;
    std::cout << s[0] << std::endl;

    std::cout << std::endl << "del()..." << std::endl;
    return 0;
}

