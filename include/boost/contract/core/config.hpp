
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

#endif // #include guard

