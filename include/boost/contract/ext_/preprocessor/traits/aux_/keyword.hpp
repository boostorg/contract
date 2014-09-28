
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_HPP_
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_HPP_

#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/tuple/rem.hpp>

// PUBLIC //

// A keyword (among 1 single possible one).

// IMPLEMENTATION: EXPAND needed for MSVC.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD( \
    tokens, \
    is_keyword_macro, keyword \
) \
    BOOST_PP_EXPR_IIF(BOOST_PP_EXPAND(is_keyword_macro(tokens)), keyword)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_SKIP( \
    tokens, \
    is_keyword_macro, remove_keyword_macro \
) \
    BOOST_PP_IIF(is_keyword_macro(tokens), \
        remove_keyword_macro \
    , \
        BOOST_PP_TUPLE_REM(1) \
    )(tokens)

// A keyword among 2 possible ones.

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2( \
    tokens, \
    is_keyword_macro1, keyword1, \
    is_keyword_macro2, keyword2 \
) \
    BOOST_PP_IIF(is_keyword_macro1(tokens), \
        keyword1 BOOST_PP_EMPTY \
    , BOOST_PP_IIF(is_keyword_macro2(tokens), \
        keyword2 BOOST_PP_EMPTY \
    , \
        BOOST_PP_EMPTY \
    ))()

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_SKIP( \
    tokens, \
    is_keyword_macro1, remove_keyword_macro1, \
    is_keyword_macro2, remove_keyword_macro2 \
) \
    BOOST_PP_IIF(is_keyword_macro1(tokens), \
        remove_keyword_macro1 \
    , BOOST_PP_IIF(is_keyword_macro2(tokens), \
        remove_keyword_macro2 \
    , \
        BOOST_PP_TUPLE_REM(1) \
    ))(tokens)

// A keyword among 3 possible ones.

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD3( \
    tokens, \
    is_keyword_macro1, keyword1, \
    is_keyword_macro2, keyword2, \
    is_keyword_macro3, keyword3 \
) \
    BOOST_PP_IIF(is_keyword_macro1(tokens), \
        keyword1 BOOST_PP_EMPTY \
    , BOOST_PP_IIF(is_keyword_macro2(tokens), \
        keyword2 BOOST_PP_EMPTY \
    , BOOST_PP_IIF(is_keyword_macro3(tokens), \
        keyword3 BOOST_PP_EMPTY \
    , \
        BOOST_PP_EMPTY \
    )))()

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD3_SKIP(\
    tokens, \
    is_keyword_macro1, remove_keyword_macro1, \
    is_keyword_macro2, remove_keyword_macro2, \
    is_keyword_macro3, remove_keyword_macro3 \
) \
    BOOST_PP_IIF(is_keyword_macro1(tokens), \
        remove_keyword_macro1 \
    , BOOST_PP_IIF(is_keyword_macro2(tokens), \
        remove_keyword_macro2 \
    , BOOST_PP_IIF(is_keyword_macro3(tokens), \
        remove_keyword_macro3 \
    , \
        BOOST_PP_TUPLE_REM(1) \
    )))(tokens)

#endif // #include guard

