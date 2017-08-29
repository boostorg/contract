
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_TEMPLATE_HPP_
#define CONTRACT_AUX_CODE_TEMPLATE_HPP_

#include <contract/detail/preprocessor/traits/class.hpp> // c
#include <contract/detail/preprocessor/traits/func.hpp> // f
#include <contract/detail/preprocessor/traits/template_param.hpp> // t
#include <contract/detail/preprocessor/list/to_array.hpp>
#include <contract/detail/preprocessor/keyword/template.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/list/for_each_i.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// PRIVATE //

// Template parameters.

#define CONTRACT_AUX_CODE_TEMPLATE_TEMPLATE_PARAM_SPLIT_(tparams_list) \
    tparams_list , 

#define CONTRACT_AUX_CODE_TEMPLATE_PARAM_TEMPLATE_KIND_ENUM_( \
        tparams_list) \
    CONTRACT_DETAIL_PP_ARRAY_REM( \
            CONTRACT_DETAIL_PP_LIST_TO_ARRAY(tparams_list))

#define CONTRACT_AUX_CODE_TEMPLATE_PARAM_TEMPLATE_KIND_TOKENS_(tparams_class) \
    template< \
        /* cannot use LIST_ENUM here because of reentrancy */ \
        BOOST_PP_IIF(BOOST_PP_LIST_IS_CONS(BOOST_PP_TUPLE_ELEM( \
                2, 0, tparams_class)), \
            CONTRACT_AUX_CODE_TEMPLATE_PARAM_TEMPLATE_KIND_ENUM_ \
        , \
            BOOST_PP_TUPLE_EAT(1) \
        )(BOOST_PP_TUPLE_ELEM(2, 0, tparams_class)) \
    > BOOST_PP_TUPLE_ELEM(2, 1, tparams_class)

// Precondition: tparams_class is `( tparams_list ) class`
#define CONTRACT_AUX_CODE_TEMPLATE_PARAM_TEMPLATE_KIND_(tparams_class) \
    CONTRACT_AUX_CODE_TEMPLATE_PARAM_TEMPLATE_KIND_TOKENS_( ( \
            CONTRACT_AUX_CODE_TEMPLATE_TEMPLATE_PARAM_SPLIT_ tparams_class ) )

// Precondition: !EMPTY(KIND(t))
#define CONTRACT_AUX_CODE_TEMPLATE_PARAM_KIND_(t) \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_TEMPLATE_FRONT( \
            CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND(t)), \
        /* template<...> class for template tparam */ \
        CONTRACT_AUX_CODE_TEMPLATE_PARAM_TEMPLATE_KIND_ \
    , \
        BOOST_PP_TUPLE_REM(1) /* typename or class for type tparam */ \
    )(CONTRACT_DETAIL_PP_KEYWORD_TEMPLATE_REMOVE_FRONT( \
            CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND(t)))
    
// Precondition: t is a positional tparam.
#define CONTRACT_AUX_CODE_TEMPLATE_PARAM_ENUM_(r, unused, i, t) \
    BOOST_PP_COMMA_IF(i) \
    /* typename, class, or template<...> class (non-value tparams) */ \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY( \
            CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND(t)), \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        CONTRACT_AUX_CODE_TEMPLATE_PARAM_KIND_ \
    )(t) \
    /* otherwise, type requirement (value tparams) */ \
    BOOST_PP_IF(BOOST_PP_ARRAY_SIZE( \
            CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_REQUIREMENT(t)), \
        BOOST_PP_ARRAY_ENUM \
    , \
        BOOST_PP_TUPLE_EAT(1) \
    )(CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_REQUIREMENT(t)) \
    /* name */ \
    CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_NAME(t) \
    /* default */ \
    BOOST_PP_IF(BOOST_PP_ARRAY_SIZE( \
            CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_DEFAULT(t)), \
        = BOOST_PP_ARRAY_ENUM \
    , \
        BOOST_PP_TUPLE_EAT(1) \
    )(CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_DEFAULT(t))

#define CONTRACT_AUX_CODE_TEMPLATE_PARAM_NAME_ENUM_(r, unused, i, t) \
    BOOST_PP_COMMA_IF(i) \
    CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_NAME(t)

// Count (because template template params can introduced unwrapped commas).

#define CONTRACT_AUX_CODE_TEMPLATE_COUNT_INC_(count, unused) \
    BOOST_PP_INC(count)
        
#define CONTRACT_AUX_CODE_TEMPLATE_COUNT_TEMPLATE_PARAMS_SIZE_( \
        count, tparams_list) \
    BOOST_PP_ADD(count, BOOST_PP_LIST_SIZE(tparams_list))

#define CONTRACT_AUX_CODE_TEMPLATE_COUNT_TEMPLATE_PARAMS_( \
        count, tparams_class) \
    BOOST_PP_IIF(BOOST_PP_LIST_IS_CONS(BOOST_PP_TUPLE_ELEM(2, 0, \
            tparams_class)), \
        /* as many tokens as tparams 1 for `template<typename X> class`, */ \
        /* 2 for `tempalte<typename X, typename Y> class`, etc */ \
        CONTRACT_AUX_CODE_TEMPLATE_COUNT_TEMPLATE_PARAMS_SIZE_ \
    , \
        /* no tparams `tempalte<> class` but still 1 token */ \
        CONTRACT_AUX_CODE_TEMPLATE_COUNT_INC_ \
    )(count, BOOST_PP_TUPLE_ELEM(2, 0, tparams_class))

// Precondition: tparams_class is `( tparams_list ) class`
#define CONTRACT_AUX_CODE_TEMPLATE_COUNT_TEMPLATE_(count, tparams_class) \
    CONTRACT_AUX_CODE_TEMPLATE_COUNT_TEMPLATE_PARAMS_(count, ( \
            CONTRACT_AUX_CODE_TEMPLATE_TEMPLATE_PARAM_SPLIT_ tparams_class ) )

// Precondition: !EMPTY(KIND(t))
#define CONTRACT_AUX_CODE_TEMPLATE_COUNT_KIND_(count, t) \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_TEMPLATE_FRONT( \
            CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND(t)), \
        /* template<...> class for template tparam */ \
        CONTRACT_AUX_CODE_TEMPLATE_COUNT_TEMPLATE_ \
    , \
        CONTRACT_AUX_CODE_TEMPLATE_COUNT_INC_ /* it is type tparam */ \
    )(count, CONTRACT_DETAIL_PP_KEYWORD_TEMPLATE_REMOVE_FRONT( \
            CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND(t)))

#define CONTRACT_AUX_CODE_TEMPLATE_COUNT_(d, count, t) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY( \
            CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND(t)), \
        CONTRACT_AUX_CODE_TEMPLATE_COUNT_INC_ /* it is value tparam */ \
    , \
        CONTRACT_AUX_CODE_TEMPLATE_COUNT_KIND_ \
    )(count, t)

// PUBLIC //

// Precondition: All of these only work on positional tparams.

// For template specializations, template01 is 1 and tparams is nil pp-list,
#define CONTRACT_AUX_CODE_TEMPLATE_DECL(template01, tparams) \
    BOOST_PP_EXPR_IIF(template01, template< ) /* for specializations */ \
    BOOST_PP_LIST_FOR_EACH_I(CONTRACT_AUX_CODE_TEMPLATE_PARAM_ENUM_, ~, \
            tparams) \
    BOOST_PP_EXPR_IIF(template01, > )

#define CONTRACT_AUX_CODE_TEMPLATE_PARAM_NAME_ENUM(tparams) \
    BOOST_PP_LIST_FOR_EACH_I(CONTRACT_AUX_CODE_TEMPLATE_PARAM_NAME_ENUM_, \
            ~, tparams)

#define CONTRACT_AUX_CODE_TEMPLATE_INSTANCE(tparams) \
    BOOST_PP_EXPR_IIF(BOOST_PP_LIST_IS_CONS(tparams), < ) \
    CONTRACT_AUX_CODE_TEMPLATE_PARAM_NAME_ENUM(tparams) \
    BOOST_PP_EXPR_IIF(BOOST_PP_LIST_IS_CONS(tparams), > )

// Count number of template tokens: 1 for template<> and template<typename X>,
// 2 for template<typename X, typename Y>, etc.
#define CONTRACT_AUX_CODE_TEMPLATE_COUNT(tparams) \
    /* cannot just use LIST_SIZE because of template template param */ \
    BOOST_PP_LIST_FOLD_LEFT(CONTRACT_AUX_CODE_TEMPLATE_COUNT_, 0, tparams)

#endif // #include guard

