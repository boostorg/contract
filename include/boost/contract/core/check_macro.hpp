
#ifndef BOOST_CONTRACT_CHECK_MACRO_HPP_
#define BOOST_CONTRACT_CHECK_MACRO_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Macro for implementation checks.
*/

// IMPORTANT: Included by contract_macro.hpp so must #if-guard all its includes.
#include <boost/contract/core/config.hpp> 
#ifndef BOOST_CONTRACT_NO_CHECKS
    #include <boost/contract/detail/check.hpp>
    #include <boost/contract/detail/assert.hpp>

    #define BOOST_CONTRACT_CHECK(condition) \
        BOOST_CONTRACT_DETAIL_CHECK(BOOST_CONTRACT_DETAIL_ASSERT(condition))
#else
    /**
    Preferred way to assert implementation check conditions.
    
    It is preferred to use this macro instead of programming implementation
    checks in a nullary functor passed to @RefClass{boost::contract::check}
    constructor because this macro will completely remove implementation checks
    from the code when @RefMacro{BOOST_CONTRACT_NO_CHECKS} is defined.

    @see @RefSect{advanced_topics.implementation_checks, Implementation Checks}

    @param condition    The condition to be asserted within implementation code
                        (function body, etc.).
                        This is not a variadic macro parameter so any comma it
                        might contain must be protected by round parenthesis
                        (i.e., @c BOOST_CONTRACT_CHECK((condition)) will always
                        work).
    */
    #define BOOST_CONTRACT_CHECK(condition) /* nothing */
#endif

#endif // #include guard

