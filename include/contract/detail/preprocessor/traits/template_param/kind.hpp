
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_HPP_
#define CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_HPP_

#include <contract/detail/preprocessor/traits/aux_/apply_1.hpp>
#include <contract/detail/preprocessor/traits/aux_/list_1.hpp>
#include <contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <contract/detail/preprocessor/keyword/contract/deduce.hpp>
#include <contract/detail/preprocessor/keyword/contract/in.hpp>
#include <contract/detail/preprocessor/keyword/contract/out.hpp>
#include <contract/detail/preprocessor/keyword/typename.hpp>
#include <contract/detail/preprocessor/keyword/class.hpp>
#include <contract/detail/preprocessor/keyword/template.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

// Cannot use PP_TUPLE_REM for reentrancy on GCC with C++0x.
#define CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_REM_(tokens) tokens

#define CONTRACT_DETAIL_PP_TEMPLATE_PARAM_REQUIRES_AUTO_(sign) \
    BOOST_PP_EXPR_IF(CONTRACT_DETAIL_PP_KEYWORD_IS_REQUIRES_FRONT(sign), \
        requires \
    ) \
    BOOST_PP_EXPR_IF(CONTRACT_DETAIL_PP_KEYWORD_IS_AUTO_FRONT(sign), \
        auto /* named value template parameter any type */ \
    )

#define CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TPL_REMOVE_template\
    CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_REMOVE

#define CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TPL_YES_( \
        sign) \
    template( \
        CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_1(sign, \
                1, /* might be empty */ \
                0, /* no defaults (use usual `=` instead) */ \
                CONTRACT_DETAIL_PP_KEYWORD_IS_TEMPLATE_FRONT, \
                CONTRACT_DETAIL_PP_KEYWORD_TEMPLATE_REMOVE_FRONT, \
                CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_REM_) \
    ) \
    BOOST_PP_EXPR_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_CLASS_FRONT( \
            CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TAGGED_LIST(sign, \
                    CONTRACT_DETAIL_PP_KEYWORD_IS_TEMPLATE_FRONT, \
  CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TPL_REMOVE_)), \
        class \
    )

#define CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TPL_(sign) \
    /* template tparam `template(tparam_list) class` */ \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_TEMPLATE_FRONT(sign), \
        CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TPL_YES_ \
    , \
        BOOST_PP_TUPLE_EAT(1) \
    )(sign)
    
#define CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TPL_REQUIRES_AUTO_(sign) \
    CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TPL_(sign) \
    /* requires and auto (named params only ) */ \
    CONTRACT_DETAIL_PP_TEMPLATE_PARAM_REQUIRES_AUTO_( \
            CONTRACT_DETAIL_PP_KEYWORD_CLASS_REMOVE_FRONT( \
            CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TAGGED_LIST( \
                  sign \
                , CONTRACT_DETAIL_PP_KEYWORD_IS_TEMPLATE_FRONT \
                , CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TPL_REMOVE_ \
            )))

#define CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TRAIT_(sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* optional trait */ \
    BOOST_PP_EXPR_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_DEDUCE_FRONT(sign), \
        deduce \
    ) \
    BOOST_PP_EXPR_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_IN_FRONT( \
            CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT(sign)), \
        in \
    ) \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_TYPENAME_FRONT( \
            CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE_FRONT( \
            CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT(sign))), \
        BOOST_PP_IDENTITY(typename) \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_CLASS_FRONT( \
            CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE_FRONT( \
            CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT(sign))), \
        BOOST_PP_IDENTITY(class) \
    , BOOST_PP_EMPTY \
    ))() \
    /* template tparam `template(tparam_list) class` */ \
    CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TPL_REQUIRES_AUTO_( \
            /* the following removal order matters */ \
            CONTRACT_DETAIL_PP_KEYWORD_CLASS_REMOVE_FRONT( \
            CONTRACT_DETAIL_PP_KEYWORD_TYPENAME_REMOVE_FRONT( \
            CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE_FRONT( \
            CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT( \
                sign \
            )))))

#define CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_SIGN_(sign) \
    /* the following removal order matters */ \
    CONTRACT_DETAIL_PP_KEYWORD_AUTO_REMOVE_FRONT( \
    CONTRACT_DETAIL_PP_KEYWORD_REQUIRES_REMOVE_FRONT( \
    CONTRACT_DETAIL_PP_KEYWORD_CLASS_REMOVE_FRONT( \
    CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TAGGED_LIST( \
        CONTRACT_DETAIL_PP_KEYWORD_TYPENAME_REMOVE_FRONT( \
        CONTRACT_DETAIL_PP_KEYWORD_CLASS_REMOVE_FRONT( \
        CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE_FRONT( \
        CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT( \
            sign \
        )))), \
        CONTRACT_DETAIL_PP_KEYWORD_IS_TEMPLATE_FRONT, \
        CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TPL_REMOVE_ \
    ))))

// PROTECTED //

#define CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_AUX_KIND(traits_sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY_INIT_1(traits_sign, \
            CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TRAIT_, \
            CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_SIGN_)

// PUBLIC //

// Expand to `[deduce] [in] [typename | class | template(tparam_list) class]
// [auto | requires]` (empty for positional value tparam).
#define CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND(tparam_traits) \
    BOOST_PP_CAT(CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_, \
            BOOST_PP_ARRAY_ELEM(0, BOOST_PP_TUPLE_ELEM(2, 0, tparam_traits)))

#endif // #include guard

