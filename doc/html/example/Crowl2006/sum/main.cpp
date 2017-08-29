// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#include "sum.hpp"
#include <iostream>

int main() {
    double a[8] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
    
    std::cout << sum(8, a) << std::endl;

    return 0;
}

