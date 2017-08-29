// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

/** @file
Augmented object state internally used by the library.
*/

namespace contract {

/**
Augmented object state internally used by the library.

As illustrated by the @c contract::nonstatic_member_function documentation, the class being contracted must declare a (private) member variable named @c contract_state_ of @c mutable type @c contract::state (see @c contract::nonstatic_member_function for example code).
The type @c contract::state must be declared a friend of the class.
This member variable is automatically declared when the @c CONTRACT_INVARIANT() macro is used (recommended).

This library will generate a compile-time error if this state variable is not declared and accessible to the contracts.

@Note This member variable is used internally by this library mainly to track when assertions are being checked so to disable assertion checking in nested function calls that could otherwise lead to infinite recursion (this is a common requirement for Contract Programming).
The friendship is requires so the library internally has access to the entire user class including non public members.

@See @c contract::nonstatic_member_function, Without the Macros section
*/
class state {};

} // namespace

