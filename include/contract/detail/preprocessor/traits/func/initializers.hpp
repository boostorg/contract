
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_FUNC_TRAITS_INITIALIZERS_HPP_
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_INITIALIZERS_HPP_

#include <contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <contract/detail/preprocessor/traits/aux_/list.hpp>
#include <contract/detail/preprocessor/keyword/contract/initialize.hpp>
#include <contract/detail/preprocessor/keyword/try.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_INITIALIZERS_TRAIT_COMMA_(sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA(BOOST_PP_TUPLE_REM(1), sign)

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_INITIALIZERS_TRAIT_(sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST(sign, \
            0, /* might not be empty */ \
            0, /* might not have defaults */ \
            CONTRACT_DETAIL_PP_KEYWORD_IS_INITIALIZE_FRONT, \
            CONTRACT_DETAIL_PP_KEYWORD_INITIALIZE_REMOVE_FRONT, \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_INITIALIZERS_TRAIT_COMMA_)\

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_INITIALIZERS_REMOVE_initialize \
    CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_REMOVE

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_INITIALIZERS_SIGN_(sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TAGGED_LIST(sign, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_INITIALIZE_FRONT, \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_INITIALIZERS_REMOVE_)

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_INITIALIZERS_REMOVE_TRY_( \
        traits_sign) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, traits_sign) \
    , \
        CONTRACT_DETAIL_PP_KEYWORD_TRY_REMOVE_FRONT(BOOST_PP_TUPLE_ELEM(2, 1, \
                traits_sign)) \
    )

// PROTECTED //

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_INITIALIZERS(traits_sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY( \
            /* always remove eventual leading `try` to handle */ \
            /* function-try-blocks around initializers */ \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_INITIALIZERS_REMOVE_TRY_( \
                    traits_sign), \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_INITIALIZERS_TRAIT_, \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_INITIALIZERS_SIGN_)

// PUBLIC //

// Expand to pp-list of member initializers `(n, (init_token0, ...))` (array
// for possible unwrapped commas).
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_INITIALIZERS(func_traits) \
    BOOST_PP_ARRAY_ELEM(22, func_traits)

#endif // #include guard

