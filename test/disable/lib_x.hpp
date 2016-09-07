
#ifndef BOOST_CONTRACT_TEST_LIB_X_HPP_
#define BOOST_CONTRACT_TEST_LIB_X_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Test contracts in .cpp compiled to never check post/except.

#include "../detail/oteststream.hpp"
#include <boost/config.hpp>
#include <string>

#ifdef BOOST_CONTRACT_TEST_LIB_X_DYN_LINK
    #ifdef BOOST_CONTRACT_TEST_LIB_X_SOURCE
        #define BOOST_CONTRACT_TEST_LIB_X_DECLSPEC BOOST_SYMBOL_EXPORT
    #else
        #define BOOST_CONTRACT_TEST_LIB_X_DECLSPEC BOOST_SYMBOL_IMPORT
    #endif
#else
    #define BOOST_CONTRACT_TEST_LIB_X_DECLSPEC /* nothing */
#endif

BOOST_CONTRACT_TEST_DETAIL_OTESTSTREAM_STR_DECL(
        BOOST_CONTRACT_TEST_LIB_X_DECLSPEC, out)

void BOOST_CONTRACT_TEST_LIB_X_DECLSPEC x();

#endif

