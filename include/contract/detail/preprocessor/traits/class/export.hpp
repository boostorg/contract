
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_CLASS_TRAITS_EXPORT_HPP_
#define CONTRACT_DETAIL_PP_CLASS_TRAITS_EXPORT_HPP_

#include <contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <contract/detail/preprocessor/traits/aux_/keyword.hpp>
#include <contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <contract/detail/preprocessor/keyword/export.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_CLASS_TRAITS_EXPORT_TRAIT_(sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* optional trait */ \
    CONTRACT_DETAIL_PP_TRAITS_AUX_KEYWORD(sign, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_EXPORT_FRONT, export)

#define CONTRACT_DETAIL_PP_CLASS_TRAITS_EXPORT_SIGN_(sign) \
        CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_KEYWORD(sign, \
            CONTRACT_DETAIL_PP_KEYWORD_EXPORT_REMOVE_FRONT)

// PROTECTED //

#define CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_EXPORT(traits_sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            CONTRACT_DETAIL_PP_CLASS_TRAITS_EXPORT_TRAIT_, \
            CONTRACT_DETAIL_PP_CLASS_TRAITS_EXPORT_SIGN_)

// PUBLIC //

// Expand to `[export]`.
#define CONTRACT_DETAIL_PP_CLASS_TRAITS_EXPORT(class_traits) \
    BOOST_PP_CAT(CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_, \
            BOOST_PP_ARRAY_ELEM(1, class_traits))

#endif // #include guard

