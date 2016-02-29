
#ifndef BOOST_CONTRACT_AUX_DEBUG_HPP_
#define BOOST_CONTRACT_AUX_DEBUG_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Usually, never #defined (so "debug" assertions always in code).
#ifdef BOOST_CONTRACT_AUX_NDEBUG
    #define BOOST_CONTRACT_AUX_DEBUG(cond) /* nothing */
#else
    #include <cassert>
    // Extra parenthesis around assert because that is also a macro.
    #define BOOST_CONTRACT_AUX_DEBUG(cond) (assert(cond))
#endif

#endif // #include guard

