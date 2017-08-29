// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_OLD_HPP_
#define CONTRACT_OLD_HPP_

#include "aux_/symbol.hpp"
#include "boost/type_traits.hpp"
#include "boost/utility.hpp"

#define CONTRACT_OLDOF(variable_name) \
    CONTRACT_AUX_INTERNAL_SYMBOL(BOOST_PP_CAT(old_, variable_name))

namespace contract {

// Old //

// IMPORTANT: This class should be an "empty shell" so compiler
// should be able to optimize away this type (0 size), the calls to
// its constructor (since they have no effect), and passing this type
// by value in function calls. Therefore, this class should add no
// runtime overhead in handling old values for non-copyable types.
class noold {
public:
    // Needed by the library internally to pass old by value.
    template<typename T>
    /* no explicit */ noold(T const&)
            // IMPORTANT: This copy operation must do nothing so to 
            // add not overhead when copying noold values.
            {}

    // IMPORTANT: Must have NO implementation so compile-time error
    // if attempt to use any variable of noold type in postconditions.

private:
    noold& operator=(noold const&); // No copy operator.
};

// Copy //

template<typename T> class copyable;

// Copy wrapper that holds copied object.
// IMPORTANT: This class template is declared here instead that in
// contract::aux because users might want to declare it friend when
// they want this library to access copy constructors that would be
// otherwise private. A class might be copyable only to support
// contract but not in general (see "counter" example in
// [Mitchell2002]):
//  class c {
//  private:
//      // Only contract library can access copy constructor.
//      friend class contract::copy<c>;
//      c(c const& source);
//  };
// Also the user could specialized this template for a user's defined
// type so to relax the constant-correct copy constructor requirement.
// NOTE: If T is noold, this copy does not add any overhead because
// noold implements its copy constructor to do nothing.
template<typename T>
class copy: boost::noncopyable {
// Typedefs are private so they are not part of this class API.
// Keep this class API to a minimum as user might need to specialize
// this template to relax copy requirements so the user must provide
// all public entities in the specialization.
private:
    // Value type removes ref (so it will deep copy ref) but keeps
    // ptr (so it will NOT deep copy ptr).
    typedef typename boost::add_const<typename
            boost::remove_reference<T>::type>::type const_type;
    // For argument passing.
    typedef typename boost::add_reference<const_type>::type const_ref;

public:
    const_type value; // Hold copied object.

    // Source passed as const ref ensuring contract const-correctness.
    copy(const_ref source):
            // Value type not a ref so this will copy.
            value(source) {}
};

} // namespace

#endif // #include guard

