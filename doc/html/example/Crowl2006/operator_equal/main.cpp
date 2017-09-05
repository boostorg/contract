// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Recursion example (works thanks to "assertions disabled within
// assertions" policy).

#include "equal.hpp"
#include "not_equal.hpp"
#include <iostream>

struct number { double value; };

int main() {
    number n;
    n.value = 1.23;

    std::cout << (n == n) << std::endl;
    std::cout << (n != n) << std::endl;

    return 0;
}

