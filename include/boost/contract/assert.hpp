
#ifndef BOOST_CONTRACT_ASSERT_HPP_
#define BOOST_CONTRACT_ASSERT_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Facilities to assert contract conditions.
*/

#include <boost/contract/detail/all_core_headers.hpp>

/* PUBLIC */

#if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_INVARIANTS)
    #include <boost/preprocessor/stringize.hpp>
    // Ternary operator used so this macro expand to an expression and it can
    // be used with `if` and all other statements.
    #define BOOST_CONTRACT_ASSERT(condition) \
        ((condition) ? (void*)0 : throw boost::contract::assertion_failure( \
                __FILE__, __LINE__, BOOST_PP_STRINGIZE(condition)))
#else
    /**
    Preferred way to assert contract conditions.
    Any exception thrown from within a preconditions, postcondition, and
    class invariant functor is interpreted by this library as a contract
    failure. Therefore, users can program contract assertions manually throwing
    exceptions in case the asserted condition is checked to be @c false (this
    library will then call the appropriate contract failure handler).
    However, using this macro is preferred because in case @condition is
    checked to be @c false, this macro expands to code that throws
    @RefClass{boost::contract::assertion_failure} with the correct assertion
    file name (@c __FILE__), line number (@c __LINE__), and condition source
    code text that will produce an informative error message.
    @see @RefSect{advanced_topics, Advanced Topics}.
    @param condition The contract condition being checked.
    */
    #define BOOST_CONTRACT_ASSERT(condition) /* nothing */
#endif

#endif // #include guard

