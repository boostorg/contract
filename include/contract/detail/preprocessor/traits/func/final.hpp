
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_FUNC_TRAITS_FINAL_HPP_
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_FINAL_HPP_

#include <contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <contract/detail/preprocessor/traits/aux_/keyword.hpp>
#include <contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <contract/detail/preprocessor/keyword/cxx11/override.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_FINAL_TRAIT_(sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* optional trait */ \
    CONTRACT_DETAIL_PP_TRAITS_AUX_KEYWORD(sign, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_FINAL_FRONT, override)

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_FINAL_SIGN_(sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_KEYWORD(sign, \
            CONTRACT_DETAIL_PP_KEYWORD_FINAL_REMOVE_FRONT)

// PROTECTED //

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_FINAL(traits_sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_FINAL_TRAIT_, \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_FINAL_SIGN_)

// PUBLIC //

// Expand to `[override]`.
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_FINAL(func_traits) \
    BOOST_PP_CAT(CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_, \
            BOOST_PP_ARRAY_ELEM(18, func_traits))

#endif // #include guard

