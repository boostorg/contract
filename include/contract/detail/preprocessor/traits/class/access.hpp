
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_CLASS_TRAITS_ACCESS_HPP_
#define CONTRACT_DETAIL_PP_CLASS_TRAITS_ACCESS_HPP_

#include <contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <contract/detail/preprocessor/traits/aux_/keyword.hpp>
#include <contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <contract/detail/preprocessor/keyword/public.hpp>
#include <contract/detail/preprocessor/keyword/protected.hpp>
#include <contract/detail/preprocessor/keyword/private.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_CLASS_TRAITS_ACCESS_TRAIT_(sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* optional trait */ \
    CONTRACT_DETAIL_PP_TRAITS_AUX_KEYWORD3(sign, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_PUBLIC_FRONT, public, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_PROTECTED_FRONT, protected, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_PRIVATE_FRONT, private)

#define CONTRACT_DETAIL_PP_CLASS_TRAITS_ACCESS_SIGN_(sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_KEYWORD3(sign, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_PUBLIC_FRONT, \
            CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_REMOVE_FRONT, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_PROTECTED_FRONT, \
            CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_REMOVE_FRONT, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_PRIVATE_FRONT, \
            CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_REMOVE_FRONT)

// PROTECTED //

#define CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_ACCESS(traits_sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY_INIT(traits_sign, \
            CONTRACT_DETAIL_PP_CLASS_TRAITS_ACCESS_TRAIT_, \
            CONTRACT_DETAIL_PP_CLASS_TRAITS_ACCESS_SIGN_)

// PUBLIC //

// Expand to `[public | protected | private]`.
#define CONTRACT_DETAIL_PP_CLASS_TRAITS_ACCESS(class_traits) \
    BOOST_PP_CAT(CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_, \
            BOOST_PP_ARRAY_ELEM(0, class_traits))

#endif // #include guard

