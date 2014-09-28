
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_HPP_

#include <boost/contract/ext_/preprocessor/paren/has.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// PRIVATE //

#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_(a, b) \
    BOOST_CONTRACT_EXT_PP_HAS_PAREN(BOOST_PP_CAT(a, b))

// PUBLIC //

// `checking_prefix ## tokens` expand to unary (e.g., `(1)`) iff `tokens` start
// with keyword to check.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS( \
        tokens, checking_prefix) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(tokens), \
        0 BOOST_PP_TUPLE_EAT(2) \
    , \
        BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_ \
    )(checking_prefix, tokens)

#endif // #include guard

