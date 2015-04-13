
#ifndef BOOST_CONTRACT_CONFIG_HPP_
#define BOOST_CONTRACT_CONFIG_HPP_

// The name of the invariant member function ("invariant" by default).
#ifndef BOOST_CONTRACT_CONFIG_INVARIANT
#   define BOOST_CONTRACT_CONFIG_INVARIANT invariant
#endif

// The name of the static invariant member function ("static invariant" by
// default).
// NOTE: C++ forbids function overload based on static classifier so a new
// function name, different from invariant's function name, had to be used.
#ifndef BOOST_CONTRACT_CONFIG_STATIC_INVARIANT
#   define BOOST_CONTRACT_CONFIG_STATIC_INVARIANT static_invariant
#endif

// The name of the base types type-def ("base_types" by default).
#ifndef BOOST_CONTRACT_CONFIG_BASE_TYPES
#   define BOOST_CONTRACT_CONFIG_BASE_TYPES base_types
#endif

// Disable some sanity checks on usage of APIs (0 by default).
#ifndef BOOST_CONTRACT_CONFIG_PERMISSIVE
#   define BOOST_CONTRACT_CONFIG_PERMISSIVE 0
#endif

#endif // #include guard

