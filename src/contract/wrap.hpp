// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_WRAP_HPP_
#define CONTRACT_WRAP_HPP_

#include <boost/mpl/assert.hpp>

// Tools to workaround preprocessor limitations when passing macro
// parameters containing commas.
// All these approaches require using a large number of `()` because 
// these are the only parenthesis recognized by the preprocessor.
// Essentially these tools provide a method to wrap all expressions
// (code blocks, types, etc) that might be passed as a macro
// parameter within `()` (and in addition to the `()` wrapping
// already required to build preprocessor sequences).
//
// VALUES 
// Value expressions with commas must be wrapped by an extra
// `( ... )` when passed as macro parameters:
//     CONTRACT_ASSERT( ( std::map<K, T>().empty() ) );
//
// TYPES 
// Type macro parameters with commas are wrapped by `( ... )` using
// the wrapper template that wraps the comma-separated type as the
// first argument of a function type. A macro is also provided to
// ease the use of the template class:
//     (typename CONTRACT_WRAP_TYPE( (std::map<K, T>) ))
// `typename` must be used _outside_ the macro when within templates.
//
// CODE bLOCKS 
// Use a combination of value and type expression wrapping.

#define CONTRACT_WRAP_TYPE(parenthesized_type) \
    /* must NOT prefix with `::` to work within contract macros */ \
    contract::wrap<void parenthesized_type >::type

namespace contract {

// Never used.
template<typename F> struct wrap {
    BOOST_MPL_ASSERT_MSG(false,
            CONTRACT_ERROR_invalid_use_of_wrap_class_see_CONTRACT_WRAP_TYPE_macro, ());
};


// In the past I had to drop const here.. why? That was done with
// an additional specialization like below, is that still needed?
// template<typename T> struct wrap<void (T const&)> { typedef T& type; };
template<typename T> struct wrap<void(T)> { typedef T type; };

} // namespace

#endif // #include guard

