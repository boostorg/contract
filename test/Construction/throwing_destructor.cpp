/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include "throwing_number.hpp"

int main() {
    std::cout << std::endl;
    {
        number<int> n;
        std::cout << n.value() << std::endl;
        n.value_ptr = 0; // Will violate destructor invariant.
    } // Will call destructor.
    assert(0); // Doesn't get here as broken_destructor_invariant() terminates.

    return 0;
}

