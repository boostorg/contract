
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
// TODO: Implement following static errors (unless PERMISSIVE): (1) error if contracted class has `invariant` or `invariant volatile` without `const` qualifiers; (2) error if `invariant const` but not `invariant const volatile` and there are contracts for volatile members (mistake: assume `invariant const` will be called also for volatile members); (3) error if R != result_type<F>& && R != optional<result_type<F>>& (mistake: C++ should warn already if overriding func has different result type (but maybe not if it's a covariant type, in which case the lib's cast on v' void* result_ will probably segfault? test it...).

#endif // #include guard

