
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS_HPP_
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS_HPP_

#include <contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <contract/detail/preprocessor/traits/aux_/list.hpp>
#include <contract/detail/preprocessor/traits/assertion.hpp>
#include <contract/detail/preprocessor/keyword/contract/precondition.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

// For reentrancy on GCC with C++0x.
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS_REM_(tokens) tokens

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS_TRAIT_(sign) \
    CONTRACT_DETAIL_PP_ASSERTION_TRAITS( \
            CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST(sign, \
                    0, /* might not be empty */ \
                    0, /* might not have defaults */ \
                    CONTRACT_DETAIL_PP_KEYWORD_IS_PRECONDITION_FRONT, \
                    CONTRACT_DETAIL_PP_KEYWORD_PRECONDITION_REMOVE_FRONT, \
                    CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS_REM_))

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS_REMOVE_precondition \
    CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_REMOVE

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS_SIGN_(sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TAGGED_LIST(sign, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_PRECONDITION_FRONT, \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS_REMOVE_)

// PROTECTED //

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_PRECONDITIONS(traits_sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS_TRAIT_, \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS_SIGN_)

// PUBLIC //

// Expand to pp-list of precondition assertions.
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS(func_traits) \
    BOOST_PP_ARRAY_ELEM(20, func_traits)

#endif // #include guard

