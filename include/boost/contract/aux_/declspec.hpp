
#ifndef BOOST_CONTRACT_AUX_DECLSPEC_HPP_
#define BOOST_CONTRACT_AUX_DECLSPEC_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/config.hpp>

/* PUBLIC */

// IMPORTANT: In general, this library should always and only be compiled and
// used as a shared library. Otherwise, lib's state won't be shared among
// different user programs and user libraries.
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_CONTRACT_DYN_LINK)
    #ifdef BOOST_CONTRACT_AUX_CONFIG_SOURCE
        #define BOOST_CONTRACT_AUX_DECLSPEC BOOST_SYMBOL_EXPORT
    #else
        #define BOOST_CONTRACT_AUX_DECLSPEC BOOST_SYMBOL_IMPORT
    #endif
#else
    #define BOOST_CONTRACT_AUX_DECLSPEC /* nothing */
#endif

#endif // #include guard

