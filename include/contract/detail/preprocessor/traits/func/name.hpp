
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME_HPP_
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME_HPP_

#include <contract/detail/preprocessor/traits/aux_/name.hpp>
#include <contract/detail/preprocessor/array/first_n.hpp>
#include <contract/detail/preprocessor/array/rest_n.hpp>
#include <contract/detail/preprocessor/array/rem.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME_INDEX_ 11

// PROTECTED //

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_NAME(traits_sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_WITH_OPERATOR, \
            CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_NAME_WITH_OPERATOR)

// PUBLIC //

// Expand to `name` (this is always alphanumeric even for operators).
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME(func_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PP_ARRAY_ELEM( \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME_INDEX_, func_traits))

// Expand to `(n, (token1, ...))` (array to handle commas in operator tokens,
// 0-size if not an operator, tokens do not include the `operator` keyword).
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_OPERATOR(func_traits) \
    BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_ARRAY_ELEM( \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME_INDEX_, func_traits))

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME_REPLACE(func_traits, name_sign) \
    /* cannot use ARRAY_REPLACE because it has reentrancy _D */ \
    ( BOOST_PP_ARRAY_SIZE(func_traits), \
    ( \
          CONTRACT_DETAIL_PP_ARRAY_REM(CONTRACT_DETAIL_PP_ARRAY_FIRST_N( \
                CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME_INDEX_, \
                func_traits)) \
        , CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_WITH_OPERATOR(name_sign) \
        , CONTRACT_DETAIL_PP_ARRAY_REM(CONTRACT_DETAIL_PP_ARRAY_REST_N( \
                BOOST_PP_INC(CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME_INDEX_), \
                func_traits)) \
    ) )

#endif // #include guard

