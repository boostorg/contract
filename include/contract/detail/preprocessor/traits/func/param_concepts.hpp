
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAM_CONCEPTS_HPP_
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAM_CONCEPTS_HPP_

#include <contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <contract/detail/preprocessor/traits/aux_/list.hpp>
#include <contract/detail/preprocessor/keyword/contract/requires.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

// For reentrancy on GCC++0x, PP_TUPLE_REM(1) doesn't work.
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAM_CONCEPTS_REM_(tokens) tokens

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAM_CONCEPTS_TRAIT_(sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST(sign, \
            0, /* might not be empty */ \
            0, /* might not have defaults */ \
            CONTRACT_DETAIL_PP_KEYWORD_IS_REQUIRES_FRONT, \
            CONTRACT_DETAIL_PP_KEYWORD_REQUIRES_REMOVE_FRONT, \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAM_CONCEPTS_REM_)

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAM_CONCEPTS_REMOVE_requires \
    CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_REMOVE

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAM_CONCEPTS_SIGN_(sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TAGGED_LIST(sign, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_REQUIRES_FRONT, \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_CONCEPTS_REMOVE_)

// PROTECTED //

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_PARAM_CONCEPTS(traits_sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAM_CONCEPTS_TRAIT_, \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAM_CONCEPTS_SIGN_)

// PUBLIC //

// Expand to pp-list of function parameter (not template param) concept types.
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAM_CONCEPTS(func_traits) \
    BOOST_PP_ARRAY_ELEM(13, func_traits)

#endif // #include guard

