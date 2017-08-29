
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_HPP_
#define CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_HPP_

#include <contract/detail/preprocessor/keyword/contract/out.hpp>
#include <contract/detail/preprocessor/keyword/contract/in.hpp>
#include <contract/detail/preprocessor/keyword/contract/deduce.hpp>
#include <contract/detail/preprocessor/keyword/contract/requires.hpp>
#include <contract/detail/preprocessor/keyword/auto.hpp>

// Utilities that only transform parameter traits into Boost.Parameter formats.

// PRIVATE //

#define CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_REQ_( \
        d, p, required_params, optional_params) \
    ( \
        BOOST_PP_LIST_APPEND(required_params, ( \
            ( /* Boost.Parameter required param is 2-tuple */ \
                CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_CLASSIFIED_NAME(p) \
            , \
                CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_TYPE_REQUIREMENT(p) \
            ) \
        , BOOST_PP_NIL)) \
    , \
        optional_params \
    )

#define CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_OPT_( \
        d, p, required_params, optional_params) \
    ( \
        required_params \
    , \
        BOOST_PP_LIST_APPEND(optional_params, ( \
            ( /* Boost.Parameter optional param is 3-tuple */ \
                CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_CLASSIFIED_NAME(p) \
            , \
                CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_TYPE_REQUIREMENT(p) \
            , \
                BOOST_PP_ARRAY_ENUM( \
                        CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_DEFAULT(p)) \
            ) \
        , BOOST_PP_NIL)) \
    )

#define CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_REQOPT_TUPLE_( \
        d, required_optional, p) \
    BOOST_PP_IF(BOOST_PP_ARRAY_SIZE( \
            CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_DEFAULT(p)), \
        CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_OPT_ \
    , \
        CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_REQ_ \
    )(d, p \
        , BOOST_PP_TUPLE_ELEM(2, 0, required_optional) \
        , BOOST_PP_TUPLE_ELEM(2, 1, required_optional) \
    )

// PUBLIC //

#define CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_REQOPT(params) \
    BOOST_PP_LIST_FOLD_LEFT( \
            CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_REQOPT_TUPLE_, \
            (BOOST_PP_NIL, BOOST_PP_NIL), params)

// Expand to 1 iff `out` (not if `in out`).
#define CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_IS_OUT_ONLY(p) \
    CONTRACT_DETAIL_PP_KEYWORD_IS_OUT_FRONT( \
            CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT( \
                CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER(p) \
                BOOST_PP_NIL /* handle possible EMPTY after removals */ \
            ))

// Expand to 1 iff `out` or `in out`.
#define CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_IS_OUT_OR_INOUT(p) \
    CONTRACT_DETAIL_PP_KEYWORD_IS_OUT_FRONT( \
            CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE_FRONT( \
            CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT( \
                CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER(p) \
                BOOST_PP_NIL /* handle possible EMPTY after removals */ \
            )))

// Precondition: classifier is `[deduce] out | in | in out` (i.e., named param).
#define CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_CLASSIFIED_NAME(p) \
    /* order of following checking is important */ \
    BOOST_PP_IIF(CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_IS_OUT_ONLY(p), \
        out \
    , BOOST_PP_IIF( /* already checked not out-only, so in-out */ \
            CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_IS_OUT_OR_INOUT(p), \
        in_out \
    , /* else, in-only */ \
        BOOST_PP_TUPLE_REM(1) \
    ))(CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p))
                
#define CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_TYPE_REQUIREMENT(p) \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_AUTO_FRONT( \
            /* the following removal order is important */ \
            CONTRACT_DETAIL_PP_KEYWORD_OUT_REMOVE_FRONT( \
            CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE_FRONT( \
            CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT( \
                CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER(p) \
                BOOST_PP_NIL /* handle possible EMPTY after removals */ \
            )))), \
        * BOOST_PP_TUPLE_EAT(1) /* any type */ \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_REQUIRES_FRONT( \
            /* the following removal order is important */ \
            CONTRACT_DETAIL_PP_KEYWORD_OUT_REMOVE_FRONT( \
            CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE_FRONT( \
            CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT( \
                CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER(p) \
                BOOST_PP_NIL /* handle possible EMPTY after removals */ \
            )))), \
        * BOOST_PP_ARRAY_DATA /* matching type requirement */ \
    , \
        BOOST_PP_ARRAY_DATA /* exact type specified */ \
    ))(CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE(p))

// Tag.

#define CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_TAG(params, p) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY( \
            CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMESPACE(params)), \
        CONTRACT_AUX_CONFIG_NAMED_PARAMETER_TAG_NAMESPACE_DEFAULT \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMESPACE \
    )(params) \
    :: \
    CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p)

#define CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_TEMPLATE_TAG(tparams, t) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY( \
            CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMESPACE(tparams)), \
        CONTRACT_AUX_CONFIG_NAMED_PARAMETER_TAG_NAMESPACE_DEFAULT \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMESPACE \
    )(tparams) \
    :: \
    CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_NAME(t)

#endif // #include guard

