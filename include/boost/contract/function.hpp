
#ifndef BOOST_CONTRACT_FUNCTION_HPP_
#define BOOST_CONTRACT_FUNCTION_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Program contracts for non-member, private, and protected functions.
*/

#include <boost/contract/detail/all_core_headers.hpp>
#if !defined(BOOST_CONTRACT_NO_FUNCTIONS) || \
        !defined(BOOST_CONTRACT_NO_INVARIANTS)
    #include <boost/contract/detail/operation/function.hpp>
#endif

namespace boost { namespace contract {

/**
Program contracts for non-member, private and protected functions.
This is used to specify preconditions, postconditions, and old value assignments
at body for non-member, private and protected functions (these functions never
check class invariants, see
@RefSect{contract_programming_overview, Contract Programming Overview}).

For optimization, this can be omitted for functions that do not have
preconditions and postconditions.
@see @RefSect{tutorial, Tutorial}
@return The result of this function must be assigned to a variable of type
        @RefClass{boost::contract::guard} declared locally just before the body
        of the contracted function (otherwise this library will generate a
        run-time error, see @RefMacro{BOOST_CONTRACT_ON_MISSING_GUARD}).
*/
specify_precondition_old_postcondition<> function() {
    // Must #if also on ..._INVARIANTS here because specify_... is generic.
    #if !defined(BOOST_CONTRACT_NO_FUNCTIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        return specify_precondition_old_postcondition<>(
                new boost::contract::detail::function());
    #else
        return specify_precondition_old_postcondition<>();
    #endif
}

} } // namespace

#endif // #include guard

