
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

Allow to program preconditions and postconditions (both optional) for
non-member, private and protected functions (these functions never check
invariants or participate in subcontracting).
The result of this function must be assigned to a local variable of type
@RefClass{boost::contract::guard} at the scope of the function being contracted.

@code
    // Enclosing function scope.
    boost::contract::guard c = boost::contract::function()
        .precondition(...)      // Optional.
        .old(...)               // Optional.
        .postcondition(...)     // Optional.
    ;
    ... // Enclosing function body.
@endcode

For optimization purposes this can be avoided for functions that do not have
preconditions and postconditions.

Where <c>.precondition(...)</c>, <c>.old(...)</c>, and
<c>.postcondition(...)</c> take nullary functors that assert preconditions,
assign old value pointers just before body execution (most of the times it
should be sufficient to assign these pointers where they are first declared
instead), and assert postconditions respectively.
@SeeAlso @RefSect{tutorial, Tutorial}
*/
set_precondition_old_postcondition<> function() {
    // Must #if also on ..._INVARIANTS here because set_... is generic.
    #if !defined(BOOST_CONTRACT_NO_FUNCTIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        return set_precondition_old_postcondition<>(
                new boost::contract::detail::function());
    #else
        return set_precondition_old_postcondition<>();
    #endif
}

} } // namespace

#endif // #include guard

