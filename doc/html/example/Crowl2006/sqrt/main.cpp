// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#include <contract.hpp>
#include <cmath>
#include <iostream>

bool equal_within_precision(const double& x, const double& y,
        const double& precision = 1e-6) {
    return fabs(x - y) <= precision;
}

// Non-member function example.
double mysqrt(double x)
CONTRACT_FUNCTION(
        (double) (mysqrt)( (double)(x) )
(precondition) ({
    CONTRACT_ASSERT( x >= 0.0 );
})
(postcondition) (root) ({
    CONTRACT_ASSERT( equal_within_precision(root * root, x) );
})
(body) ({
    return sqrt(x);
}) )

int main() {
    std::cout << mysqrt(4.0) << std::endl;
    std::cout << std::endl;
    std::cout << mysqrt(-1.0) << std::endl;
    return 0;
}

