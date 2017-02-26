
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
    #define BOOST_CONTRACT_CHECK(condition) /* nothing */
#endif

#endif // #include guard

