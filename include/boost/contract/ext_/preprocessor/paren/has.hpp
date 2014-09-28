
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_EXT_PP_HAS_PAREN_HPP_
#define BOOST_CONTRACT_EXT_PP_HAS_PAREN_HPP_

#include <boost/preprocessor/detail/check.hpp>

// PRIVATE //

// Variadic so handle any arity.
#define BOOST_CONTRACT_EXT_PP_HAS_PAREN_CHECK(...) \
    1

#define BOOST_PP_CHECK_RESULT_BOOST_CONTRACT_EXT_PP_HAS_PAREN_CHECK \
    0, BOOST_PP_NIL

// PUBLIC //

// Adapted from BOOST_PP_IS_UNARY but for variadic macros.
#define BOOST_CONTRACT_EXT_PP_HAS_PAREN(tokens) \
    BOOST_PP_CHECK(tokens, BOOST_CONTRACT_EXT_PP_HAS_PAREN_CHECK)

#endif // #include guard

