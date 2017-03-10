
#ifndef BOOST_CONTRACT_ASSERT_HPP_
#define BOOST_CONTRACT_ASSERT_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Assert contract conditions.
*/

#include <boost/contract/core/config.hpp>
#ifndef BOOST_CONTRACT_NO_ALL
    #include <boost/contract/detail/assert.hpp>
    #define BOOST_CONTRACT_ASSERT(condition) \
        BOOST_CONTRACT_DETAIL_ASSERT(condition) /* no `;`  here */
#else
    /**
    Preferred way to assert contract conditions.

    Any exception thrown from within a contract (preconditions, postconditions,
    exception guarantees, old value copies at body, class invariants, etc.) is
    interpreted by this library as a contract failure.
    Therefore, users can program contract assertions manually throwing an
    exception when an asserted condition is checked to be @c false (this
    library will then call the appropriate contract failure handler
    @RefFunc{boost::contract::precondition_failure}, etc.).
    However, it is preferred to use this macro instead because it expands to
    code that throws @RefClass{boost::contract::assertion_failure} with the
    correct assertion file name (using <c>__FILE__</c>), line number (using
    <c>__LINE__</c>), and asserted condition code so to produce informative
    error messages.

    @see    @RefSect{tutorial, Tutorial},
            @RefSect{advanced_topics.throw_on_failure, Throw on Failure},
            @RefSect{extra_topics.no_macros__no_c__11_, No Macros}
    
    @param condition    The contract condition being checked.
                        (This is not a variadic macro parameter so any comma it
                        might contain must be protected by round parenthesis,
                        but @c BOOST_CONTRACT_ASSERT((condition)) will always
                        work.)
    */
    #define BOOST_CONTRACT_ASSERT(condition) {}
#endif

#endif // #include guard

