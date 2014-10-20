
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_HPP_

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/keyword.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/public.hpp>
#include <boost/contract/ext_/preprocessor/keyword/protected.hpp>
#include <boost/contract/ext_/preprocessor/keyword/private.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

// PRIVATE //

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_SIGN_(sign, traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD3_SKIP( \
        sign, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PUBLIC_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_PUBLIC_REMOVE_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PROTECTED_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_PROTECTED_REMOVE_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PRIVATE_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_PRIVATE_REMOVE_FRONT \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_TRAIT_(sign, traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PUSH_BACK(traits, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD3( \
            sign, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PUBLIC_FRONT, public, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PROTECTED_FRONT, protected, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PRIVATE_FRONT, private \
        ) \
        BOOST_PP_EMPTY \
    )

// PUBLIC //

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_PARSE(sign_traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_SIGN_ sign_traits \
    , \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_TRAIT_ sign_traits \
    )

// Expand to `public | protected | private | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ELEM( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_ACCESS_INDEX, \
        traits \
    )()

#endif // #include guard

