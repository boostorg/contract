
#ifndef BOOST_CONTRACT_CONSTRUCTOR_HPP_
#define BOOST_CONTRACT_CONSTRUCTOR_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Program contracts for constructors.
*/

#include <boost/contract/core/config.hpp>
#include <boost/contract/core/specify.hpp>
#include <boost/contract/core/access.hpp>
#include <boost/contract/core/constructor_precondition.hpp>
#if     defined(BOOST_CONTRACT_STATIC_LINK) || \
        !defined(BOOST_CONTRACT_NO_CONSTRUCTORS) || \
        !defined(BOOST_CONTRACT_NO_PRECONDITIONS)
    #include <boost/contract/detail/operation/constructor.hpp>
#endif

namespace boost { namespace contract {

/**
Program contracts for constructors.
This is used to specify postconditions, old value assignments at body, and
check class invariants for constructors (see
@RefClass{boost::contract::constructor_precondition} to specify preconditions
for constructors instead).

For optimization, this can be omitted for constructors that do not have
postconditions when the enclosing class has no invariants.
@see @RefSect{tutorial, Tutorial}
@param obj The object @c this from the scope of the contracted constructor.
@return The result of this function must be assigned to a variable of type
        @RefClass{boost::contract::guard} declared locally just before the body
        of the contracted constructor (otherwise this library will generate a
        run-time error, see @RefMacro{BOOST_CONTRACT_ON_MISSING_GUARD}).
*/
template<class Class>
specify_old_postcondition_except<> constructor(Class* obj) {
    // Must #if also on ..._PRECONDITIONS here because specify_... is generic.
    #if     defined(BOOST_CONTRACT_STATIC_LINK) || \
            !defined(BOOST_CONTRACT_NO_CONSTRUCTORS) || \
            !defined(BOOST_CONTRACT_NO_PRECONDITIONS)
        return specify_old_postcondition_except<>(
                new boost::contract::detail::constructor<Class>(obj));
    #else
        return specify_old_postcondition_except<>();
    #endif
}

} } // namespace

#endif // #include guard

