
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_TRAITS_AUX_KEYWORD_HPP_
#define CONTRACT_DETAIL_PP_TRAITS_AUX_KEYWORD_HPP_

#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// PROTECTED //

// A keyword.

#define CONTRACT_DETAIL_PP_TRAITS_AUX_KEYWORD(tokens, is_macro, keyword) \
    BOOST_PP_EXPR_IIF(BOOST_PP_EXPAND(is_macro(tokens)), /* expand for MSVC */ \
            keyword)

#define CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_KEYWORD(tokens, after_macro) \
    after_macro(tokens)

// A keyword among 2 possible ones.

#define CONTRACT_DETAIL_PP_TRAITS_AUX_KEYWORD2(tokens, \
        is_macro1, keyword1, is_macro2, keyword2) \
    BOOST_PP_IIF(is_macro1(tokens), \
        keyword1 BOOST_PP_EMPTY \
    , BOOST_PP_IIF(is_macro2(tokens), \
        keyword2 BOOST_PP_EMPTY \
    , \
        BOOST_PP_EMPTY /* expand to nothing */ \
    ))(/* expand empty */)

#define CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_KEYWORD2(tokens, \
        is_macro1, after_macro1, is_macro2, after_macro2) \
    BOOST_PP_IIF(is_macro1(tokens), \
        after_macro1 \
    , BOOST_PP_IIF(is_macro2(tokens), \
        after_macro2 \
    , \
        tokens BOOST_PP_TUPLE_EAT(1) /* remove nothing */ \
    ))(tokens)

// A keyword among 3 possible ones.

#define CONTRACT_DETAIL_PP_TRAITS_AUX_KEYWORD3(tokens, \
        is_macro1, keyword1, is_macro2, keyword2, is_macro3, keyword3) \
    BOOST_PP_IIF(is_macro1(tokens), \
        keyword1 BOOST_PP_EMPTY \
    , BOOST_PP_IIF(is_macro2(tokens), \
        keyword2 BOOST_PP_EMPTY \
    , BOOST_PP_IIF(is_macro3(tokens), \
        keyword3 BOOST_PP_EMPTY \
    , \
        BOOST_PP_EMPTY /* expand to nothing */ \
    )))(/* expand empty */)

#define CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_KEYWORD3(tokens, \
        is_macro1, after_macro1, is_macro2, after_macro2, \
        is_macro3, after_macro3) \
    BOOST_PP_IIF(is_macro1(tokens), \
        after_macro1 \
    , BOOST_PP_IIF(is_macro2(tokens), \
        after_macro2 \
    , BOOST_PP_IIF(is_macro3(tokens), \
        after_macro3 \
    , \
        tokens BOOST_PP_TUPLE_EAT(1) /* remove nothing */ \
    )))(tokens)

#endif // #include guard

