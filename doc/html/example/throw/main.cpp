// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Configure the library to throw on contract failure.

//[ throw_on_failure_cpp

#include <contract.hpp>
#include <iostream>

// User defined exception (not even derived from `std::exception`).
class not_a_number {};

double sqrt(double x)
CONTRACT_FUNCTION( (double) (sqrt)( (double)(x) )
(precondition) ({
    // Eventually throws user-defined exception.
    if (!( x >= 0.0 )) throw not_a_number();
})
(postcondition) (root) ({
    // Eventually throw library defined exception `contract::failure`.
    CONTRACT_ASSERT( (root * root) == x );
})
(body) ({
    return 0.0; // Intentionally incorrect to fail postcondition.
}) )

void throwing_handler(const contract::from& where) {
    if (where == contract::FROM_DESTRUCTOR) {
        // Cannot throw from within destructor for STL exception safety.
        std::clog << "Ignored destructor contract failure" << std::endl;
    } else {
        // Failure handlers always called with active an exception.
        throw; // Re-throw active exception thrown by precondition.
    }
}

void postcondition_throwing_handler(const contract::from& where) {
    // try/catch/re-throw to get active exception (for logging, etc.).
    try {
        throw; // Re-throw active exception thrown by precondition.
    } catch (std::exception& error) { // Get exception object.
        std::clog << "Throwing '" << error.what() << "'" << std::endl;
        
        throw; // Re-throw.
    } // Non standard exception also thrown.
}

int main() {
    // Setup contract failure handlers that throw (instead of terminate).
    contract::set_precondition_failed(&throwing_handler);
    contract::set_postcondition_failed(&postcondition_throwing_handler);
    // Invariants not used by this examples but set anyway...
    contract::set_class_invariant_failed(&throwing_handler);
    contract::set_block_invariant_failed(&throwing_handler);

    try {
        std::cout << sqrt(-1.0) << std::endl;
    } catch (not_a_number&) {
        std::clog << "Ignored not a number exception" << std::endl;
    }

    try {
        std::cout << sqrt(4.0) << std::endl;
    } catch (...) {
        std::clog << "Unable to calculate square root" << std::endl;
    }

    return 0;
}

//]

