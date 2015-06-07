
#ifndef BOOST_CONTRACT_CONFIG_HPP_
#define BOOST_CONTRACT_CONFIG_HPP_

/** @file */

// TODO: base_types, invariant, and static_invariant must be public. Allow to
// make them private (so to not alter user's public API) by declaring some
// `friend class boost::contract::aux::access;` from the user's class (then
// this lib can access base_types, invariant, and static_invariant via that
// access class).

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

// TODO: Implement following up/down error levels.
//  #ifdef PEDANTIC
//  *   error: if contracted class missing `invariant const [volatile]`
//      mistakes: inv func could be missing const, be misspelled, not be
//      public, etc.
//  *   error: if `invariant const` but not `invariant const volatile` and
//      there are contracts for volatile members.
//      mistakes: assume `invariant const` will be called also for volatile
//      members.
//  *   error: if R != result_type<F>& && R != optional<result_type<F>>&
//      mistakes: c++ should warn already if overriding func has different
//      result type (but maybe not if it's a covariant type, in which case
//      the lib's cast on v' void* result_ will probably segfault?).
//  #ifdef PERMISSIVE

#endif // #include guard

