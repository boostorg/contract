
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_UNINITIALIZED_HPP_
#define CONTRACT_AUX_UNINITIALIZED_HPP_

#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <cassert>
#include <stdexcept>

namespace contract { namespace aux {

// This function is used as a default parameter value for parameter names
// that are specified together with an `=` which cannot be separated using
// pp-metaprogramming (e.g., old-of and return values in postconditions).
// However, this is used just to compile the code an this default value should
// never actually be used and this function should never be called (because the
// default value access an invalid pointer) so this function aborts.
// NOTE: This cannot be achieved simply using a C-style cast `(T)0` as the
// default parameter value because in some cases (e.g., if T is a & to a
// complex type like void_result) the cast will generate a compiler-error.
template< typename T >
struct uninitialized {
    // NOTE: This needs to be a template class with a static member function
    // instead of just a template function because otherwise some compilers
    // (MSVC) will not be able to deduce the template type (even if it is
    // always explicitly specified when invoking the function).
    static typename boost::add_reference<T>::type value() {
        assert(false); // Internal Error: Should never execute this.
        typename boost::add_pointer<T>::type ptr = 0;
        return *ptr;
    }
};

}} // namespace contract::aux

#endif // #include guard

