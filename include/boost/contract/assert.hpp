
#ifndef BOOST_CONTRACT_ASSERT_HPP_
#define BOOST_CONTRACT_ASSERT_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Facility to assert contract conditions.
*/

#include <boost/contract/detail/all_core_headers.hpp>

/* PUBLIC */

#if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_INVARIANTS)
    #include <boost/contract/detail/assert.hpp>
    #define BOOST_CONTRACT_ASSERT(condition) \
        BOOST_CONTRACT_DETAIL_ASSERT(condition) /* no `;`  here */
#else
    /**
    Preferred way to assert contract conditions.
    Any exception thrown from within a preconditions, postcondition, or
    class invariant functor is interpreted by this library as a contract
    failure. Therefore, users can program contract assertions manually throwing
    exceptions from the precondition, postcondition, or invariant functions when
    the asserted condition is checked to be @c false (this library will then
    call the appropriate contract failure handler
    @RefFunc{boost::contract::precondition_failure}, etc.).
    However, using this macro is preferred because in case @p condition is
    checked to be @c false, this macro expands to code that throws
    @RefClass{boost::contract::assertion_failure} with the correct assertion
    file name (<c>__FILE__</c>), line number (<c>__LINE__</c>), and asserted
    condition source code so to produce an informative error message.

    This macro is not a variadic macro. Therefore, if @p condition contains
    commas not already wrapped by round parenthesis, it needs to be wrapped by
    an outer set of extra round parenthesis <c>BOOST_CONTRACT_ASSERT((...))</c>
    (as usual with C++ non-variadic macro parameters).
    @see @RefSect{tutorial, Tutorial}
    @param condition The contract condition being checked.
    */
    #define BOOST_CONTRACT_ASSERT(condition) {}
#endif

#endif // #include guard

