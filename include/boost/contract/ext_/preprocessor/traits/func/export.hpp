
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXPORT_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXPORT_HPP_

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/keyword.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/export.hpp>
#include <boost/contract/ext_/preprocessor/utility/expand.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

// NOTE: The `export` keyword for templates was deprecated in C++11 but it is
// supported here for compliance and compatibility with C++03.

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXPORT_SIGN_(sign, traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_SKIP( \
        sign, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IS_EXPORT_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_EXPORT_REMOVE_FRONT \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXPORT_TRAIT_(sign, traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
        traits, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD(sign, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_IS_EXPORT_FRONT, export) \
        BOOST_PP_EMPTY \
    )

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXPORT_PARSE(sign_traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_EXPAND_ONCE( \
                BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXPORT_SIGN_ sign_traits) \
    , \
        BOOST_CONTRACT_EXT_PP_EXPAND_ONCE( \
                BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXPORT_TRAIT_ sign_traits) \
    )

// Expand to `export | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXPORT(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_EXPORT_INDEX, traits)()

#endif // #include guard

