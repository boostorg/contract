// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_ASSERT_HPP_
#define CONTRACT_AUX_ASSERT_HPP_

#include "../from.hpp"
#include <stdexcept>
#include <iostream> // For default handlers.

// Default failure handlers do not throw (exception specification
// throw()) so they comply with STL exception safety requirements.

// Inlining functions also to avoid multiple definition error.

namespace contract { namespace aux {

// In general this could throw for user defined handlers.
// Failure handlers are automatically called by the library when
// contracts throw (any exception). Therefore, at the entry of failure
// handlers the exception thrown by the contract is always active and
// not yet handled and the exception object can be obtained by
// throw/catch:
//  void throwing_handler(from const& where) {
//      try { throw; }
//      catch (std::exception& ex) {
//          ... // Do something with ex (e.g., print ex.what()).
//          throw; // Re-throw to pass up thrown exception.
//      } // Thrown exception passed up.
//  }
// @param where Used to take different actions based on where the
//  contract failed (e.g., never throw from within destructors).
typedef void (* contract_failed_handler)(from const& where);

// Block Invariant //

// Default calls terminate and never throws.
inline void default_block_invariant_failed_handler(from const& where)
        throw() {
    std::cerr << "block invariant: "; // No trailing '\n'.
    std::terminate();
}

static contract_failed_handler block_invariant_failed_handler =
        &default_block_invariant_failed_handler;

// Class Invariant //

// Default calls terminate and never throws.
inline void default_class_invariant_failed_handler(from const& where)
        throw() {
    std::cerr << "class invariant: "; // No trailing '\n'.
    std::terminate();
}

static contract_failed_handler class_invariant_failed_handler =
        &default_class_invariant_failed_handler;

// Precondition //

// Default calls terminate and never throws.
inline void default_precondition_failed_handler(from const& where)
        throw() {
    std::cerr << "precondition: "; // No trailing '\n'.
    std::terminate();
}

static contract_failed_handler precondition_failed_handler =
        &default_precondition_failed_handler;

// Postcondition //

// Default calls terminate and never throws.
inline void default_postcondition_failed_handler(from const& where)
        throw() {
    std::cerr << "postcondition: "; // No trailing '\n'.
    std::terminate();
}

static contract_failed_handler postcondition_failed_handler =
        &default_postcondition_failed_handler;

}} // namespace

#endif // #include guard

