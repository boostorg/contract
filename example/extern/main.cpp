// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Extern (non-member) functions supported as usual.

#include <contract.hpp>
#include <iostream>

//[ extern_cpp

extern void ext(int x) // Some external linkage.
CONTRACT_FUNCTION( (extern) (void) (ext)( (int)(x) )
(body) ({
    std::cout << x << std::endl;
}) )

extern "C" void ext_c(int x) // External linkage callable from C.
CONTRACT_FUNCTION( (extern "C") (void) (ext_c)( (int)(x) )
(body) ({
    std::cout << x << std::endl;
}) )

//]

int main() {
    ext(1);
    ext_c(2);
    return 0;
}

