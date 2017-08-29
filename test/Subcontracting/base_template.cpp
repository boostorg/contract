
#include "base_template.hpp"
#include <iostream>

int main() {
    base<int> b;
    std::cout << b.f(-1) << std::endl;
    std::cout << b.f_m(-1) << std::endl;

    return 0;
};

