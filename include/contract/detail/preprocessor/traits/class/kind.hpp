
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_CLASS_TRAITS_KIND_HPP_
#define CONTRACT_DETAIL_PP_CLASS_TRAITS_KIND_HPP_

#include <contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <contract/detail/preprocessor/traits/aux_/keyword.hpp>
#include <contract/detail/preprocessor/keyword/class.hpp>
#include <contract/detail/preprocessor/keyword/struct.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_CLASS_TRAITS_KIND_TRAIT_(sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_KEYWORD2(sign, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_CLASS_FRONT, class, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_STRUCT_FRONT, struct)

#define CONTRACT_DETAIL_PP_CLASS_TRAITS_KIND_SIGN_(sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_KEYWORD2(sign, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_CLASS_FRONT, \
            CONTRACT_DETAIL_PP_KEYWORD_CLASS_REMOVE_FRONT, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_STRUCT_FRONT, \
            CONTRACT_DETAIL_PP_KEYWORD_STRUCT_REMOVE_FRONT)

// PROTECTED //

#define CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_KIND(traits_sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            CONTRACT_DETAIL_PP_CLASS_TRAITS_KIND_TRAIT_, \
            CONTRACT_DETAIL_PP_CLASS_TRAITS_KIND_SIGN_)

// PUBLIC //

// Expand to `class | struct`.
#define CONTRACT_DETAIL_PP_CLASS_TRAITS_KIND(class_traits) \
    BOOST_PP_ARRAY_ELEM(5, class_traits)

#endif // #include guard

