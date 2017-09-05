
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_HPP_
#define CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_HPP_

#include <contract/detail/preprocessor/traits/params.hpp>
#include <contract/detail/preprocessor/traits/template_param.hpp>
#include <contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <contract/detail/preprocessor/traits/aux_/list.hpp>
#include <contract/detail/preprocessor/keyword/template.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_TRAIT_(sign) \
    ( \
        CONTRACT_DETAIL_PP_KEYWORD_IS_TEMPLATE_FRONT(sign) \
    , \
        CONTRACT_DETAIL_PP_TEMPLATE_PARAMS_TRAITS(sign) \
    )

#define CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_REMOVE_template \
    CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_REMOVE

#define CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_SIGN_(sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TAGGED_LIST(sign, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_TEMPLATE_FRONT, \
            CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_REMOVE_)

#define CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_INDEX_ 2

// PROTECTED //

#define CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_TEMPLATE(traits_sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_TRAIT_, \
            CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_SIGN_)

// PUBLIC //

// Expand to 1 iff it is a template (even if no params `template<>`).
#define CONTRACT_DETAIL_PP_CLASS_TRAITS_IS_TEMPLATE(class_traits) \
    BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_ARRAY_ELEM( \
            CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_INDEX_, class_traits))

// Expand to tparams traits (see `TEMPLATE_PARAM_TRAITS` macros).
#define CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_PARAMS(class_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PP_ARRAY_ELEM( \
            CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_INDEX_, \
            class_traits))

#define CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_REPLACE( \
        class_traits, template_sign) \
    /* can't use ARRAY_REPLACE here because it has reentrancy _D */ \
    ( BOOST_PP_ARRAY_SIZE(class_traits), \
    ( \
        CONTRACT_DETAIL_PP_ARRAY_REM(CONTRACT_DETAIL_PP_ARRAY_FIRST_N( \
                CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_INDEX_, \
                class_traits)) \
        , CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_TRAIT_(template_sign) \
        , CONTRACT_DETAIL_PP_ARRAY_REM(CONTRACT_DETAIL_PP_ARRAY_REST_N( \
                BOOST_PP_INC( \
                        CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_INDEX_), \
                class_traits)) \
    ) )

#endif // #include guard

