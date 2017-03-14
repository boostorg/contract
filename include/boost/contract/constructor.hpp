
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
#if     !defined(BOOST_CONTRACT_NO_CONSTRUCTORS) || \
        !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
         defined(BOOST_CONTRACT_STATIC_LINK)
    #include <boost/contract/detail/operation/constructor.hpp>
#endif

namespace boost { namespace contract {

/**
Program contracts for constructors.

This is used to specify postconditions, exception guarantees, old value copies
at body, and check class invariants for constructors (see
@RefClass{boost::contract::constructor_precondition} to specify preconditions
for constructors instead).

For optimization, this can be omitted for constructors that do not have
postconditions and exception guarantees when the enclosing class has no
invariants.

@see @RefSect{tutorial.constructors, Constructors}
    
@param obj  The object @c this from the scope of the enclosing constructor
            declaring the contract.
            (Constructors check all class invariants, including static and
            volatile invariants, see also @RefSect{tutorial.class_invariants,
            Class Invariants} and
            @RefSect{advanced_topics.volatile_public_functions,
            Volatile Public Functions}).

@tparam Class   The class type of the enclosing constructor declaring the
                contract.
                (Usually this template parameter is automatically deduced by C++
                and it does not need to be explicitly specified by programmers.)

@return The result of this function must be explicitly assigned to a variable of
        type @RefClass{boost::contract::check} declared locally just before the
        code of the constructor body (otherwise this library will generate a
        run-time error, see @RefMacro{BOOST_CONTRACT_ON_MISSING_CHECK_DECL}).
*/
template<class Class>
specify_old_postcondition_except<> constructor(Class* obj) {
    // Must #if also on ..._PRECONDITIONS here because specify_... is generic.
    #if     !defined(BOOST_CONTRACT_NO_CONSTRUCTORS) || \
            !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
             defined(BOOST_CONTRACT_STATIC_LINK)
        return specify_old_postcondition_except<>(
                new boost::contract::detail::constructor<Class>(obj));
    #else
        return specify_old_postcondition_except<>();
    #endif
}

} } // namespace

#endif // #include guard

