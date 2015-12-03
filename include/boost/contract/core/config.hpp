
#ifndef BOOST_CONTRACT_CONFIG_HPP_
#define BOOST_CONTRACT_CONFIG_HPP_

/** @file */

// TODO: Disable pre, post, and/or entry/exit inv (all combinations). Can I compile lib1 with some contract enabled/disable settings, lib2 with other settings and then link the two together?

// TODO: Add a config macro PRECONDITIONS_DISABLE_NOTHING to avoid disabling contract assertions within assertions checking for preconditions (to avoid passing unchecked arguments to function body...). This is what N1962 does... but this macro should be #undef by default.

#ifndef BOOST_CONTRACT_CONFIG_NO_PRECONDITIONS
#   define BOOST_CONTRACT_CONFIG_NO_PRECONDITIONS 0
#endif

#ifndef BOOST_CONTRACT_CONFIG_NO_POSTCONDITIONS
#   define BOOST_CONTRACT_CONFIG_NO_POSTCONDITIONS 0
#endif

#ifndef BOOST_CONTRACT_CONFIG_NO_INVARIANTS
#   define BOOST_CONTRACT_CONFIG_NO_INVARIANTS 0
#endif

#ifndef BOOST_CONTRACT_CONFIG_BASE_TYPES
#   define BOOST_CONTRACT_CONFIG_BASE_TYPES base_types
#endif

#ifndef BOOST_CONTRACT_CONFIG_INVARIANT
#   define BOOST_CONTRACT_CONFIG_INVARIANT invariant
#endif

// C++ does not allow to overload member functions based on static classifier,
// so a name different from the non-static class invariant member must be used.
#ifndef BOOST_CONTRACT_CONFIG_STATIC_INVARIANT
#   define BOOST_CONTRACT_CONFIG_STATIC_INVARIANT static_invariant
#endif

// BOOST_CONTRACT_CONFIG_PERMISSING (#undef by default).

// Type of exception to throw is `guard c = ...` is missing. This is a
// programming error so by default this library calls abort. If this macro is
// #defined however, this library will throw the exception specified by the
// macro value instead of calling abort. When #defined, this macro must be a
// default constructible type.
// Code instruction(s) to execute when contracts are missing `guard c = ...`.
// In general, this is #undefined and this library calls `assert(false)` when
// contract guards are missing. Missing a contract guard is a logic error in
// the program (similar to dereferencing a null pointer) so terminating the
// program via `abort` or `assert` as this library does by default is the only
// safe thing to do. Therefore, it is recommended to never #define this macro.
// However, this macro can be defined to throw an exception, call a function,
// a no-op, or any other user code in case users truly need to handle missing
// contract guard logic errors without terminating the program, for example:
//  #define BOOST_CONFIG_ON_MISSING_GUARD { throw my_logic_error(); }
// BOOST_CONTRACT_CONFIG_ON_MISSING_GUARD

#endif // #include guard

