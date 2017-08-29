
#include "template_subcontracts_template.hpp"
#include <iostream>

int main() {
    derived<int> d;
    std::cout << d.f(-10) << std::endl;
    std::cout << d.f_m(-10) << std::endl;

    return 0;
}

