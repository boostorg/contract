
#ifndef BOOST_CONTRACT_ASSERT_HPP_
#define BOOST_CONTRACT_ASSERT_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file */

#include <boost/contract/aux_/all_core_headers.hpp>

/* PUBLIC */

// Must use ternary operator expr here (instead of if-statement) so this macro
// can always be used with if-statements and all other C++ constructs.
#if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_INVARIANTS)
    #include <boost/preprocessor/stringize.hpp>
    #define BOOST_CONTRACT_ASSERT(condition) \
        ((condition) ? (void*)0 : throw boost::contract::assertion_failure( \
                __FILE__, __LINE__, BOOST_PP_STRINGIZE(condition)))
#else
    #define BOOST_CONTRACT_ASSERT(condition) /* nothing */
#endif

#endif // #include guard

