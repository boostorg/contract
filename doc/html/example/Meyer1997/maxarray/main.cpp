// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Loop variants and invariants (ported from Eiffel code).

#include <contract.hpp>
#include <algorithm>
#include <iostream>

int maxarray(const int* array, const size_t& size)
CONTRACT_FUNCTION( (int) (maxarray)( (const int*)(array)
        (const size_t&)(size) )
(precondition) ({
    CONTRACT_ASSERT( size >= 1 );
})
(body) ({
    size_t i = 0;
    int result = array[i];

    CONTRACT_INIT_LOOP_VARIANT;
    while (i < (size - 1)) {
        for (size_t j = 0; j < i; ++j)
            CONTRACT_ASSERT_BLOCK_INVARIANT( result >= array[j] );
        // -2 because start from 0 and already done element at 0.
        CONTRACT_ASSERT_LOOP_VARIANT( size - i - 2 );

        ++i;
        result = std::max(result, array[i]);
    }
    
    return result;
}) )

int main() {
    int a[] = {1, 5, 3};
    std::cout << maxarray(a, 3) << std::endl;
    return 0;
}

