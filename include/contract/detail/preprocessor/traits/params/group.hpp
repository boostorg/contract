
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_PARAMS_TRAITS_GROUP_HPP_
#define CONTRACT_DETAIL_PP_PARAMS_TRAITS_GROUP_HPP_

// PRIVATE //

#define CONTRACT_DETAIL_PP_PARAMS_TRAITS_GROUP_POSITIONAL_(d, p, \
        tag_namespace, positional_params, named_params, deduced_params, \
        param_classifier_macro) \
    ( \
        tag_namespace \
    , \
        BOOST_PP_LIST_APPEND(positional_params, (p, BOOST_PP_NIL)) \
    , \
        named_params \
    , \
        deduced_params \
    , \
        param_classifier_macro \
    )

#define CONTRACT_DETAIL_PP_PARAMS_TRAITS_GROUP_NAMED_(d, p, \
        tag_namespace, positional_params, named_params, deduced_params, \
        param_classifier_macro) \
    ( \
        tag_namespace \
    , \
        positional_params \
    , \
        BOOST_PP_LIST_APPEND(named_params, (p, BOOST_PP_NIL)) \
    , \
        deduced_params \
    , \
        param_classifier_macro \
    )

#define CONTRACT_DETAIL_PP_PARAMS_TRAITS_GROUP_DEDUCED_(d, p, \
        tag_namespace, positional_params, named_params, deduced_params, \
        param_classifier_macro) \
    ( \
        tag_namespace \
    , \
        positional_params \
    , \
        named_params \
    , \
        BOOST_PP_LIST_APPEND(deduced_params, (p, BOOST_PP_NIL)) \
    , \
        param_classifier_macro \
    )

#define CONTRACT_DETAIL_PP_PARAMS_TRAITS_GROUP_BY_CLASSIFIER_(d, p, \
        tag_namespace, positional_params, named_params, deduced_params, \
        param_classifier_macro) \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_DEDUCE_FRONT( \
            param_classifier_macro(p)), \
        CONTRACT_DETAIL_PP_PARAMS_TRAITS_GROUP_DEDUCED_ \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_IN_FRONT( /* also `in out` */ \
            param_classifier_macro(p)), \
        CONTRACT_DETAIL_PP_PARAMS_TRAITS_GROUP_NAMED_ \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_OUT_FRONT( \
            param_classifier_macro(p)), \
        CONTRACT_DETAIL_PP_PARAMS_TRAITS_GROUP_NAMED_ \
    , \
        CONTRACT_DETAIL_PP_PARAMS_TRAITS_GROUP_POSITIONAL_ \
    )))(d, p, tag_namespace, positional_params, named_params, deduced_params, \
            param_classifier_macro)

#define CONTRACT_DETAIL_PP_PARAMS_TRAITS_GROUP_TUPLE_( \
        d, tag_positional_named_deduced_classifier, p) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY( \
            /* only positional param can have EMPTY classifier */ \
            BOOST_PP_TUPLE_ELEM(5, 4, \
                    tag_positional_named_deduced_classifier)(p)), \
        CONTRACT_DETAIL_PP_PARAMS_TRAITS_GROUP_POSITIONAL_ \
    , \
        CONTRACT_DETAIL_PP_PARAMS_TRAITS_GROUP_BY_CLASSIFIER_ \
    )(d, p, \
        BOOST_PP_TUPLE_ELEM(5, 0, tag_positional_named_deduced_classifier), \
        BOOST_PP_TUPLE_ELEM(5, 1, tag_positional_named_deduced_classifier), \
        BOOST_PP_TUPLE_ELEM(5, 2, tag_positional_named_deduced_classifier), \
        BOOST_PP_TUPLE_ELEM(5, 3, tag_positional_named_deduced_classifier), \
        BOOST_PP_TUPLE_ELEM(5, 4, tag_positional_named_deduced_classifier) \
    )
    
#define CONTRACT_DETAIL_PP_PARAMS_TRAITS_GROUP_TUPLE_5TO4_( \
        tag_positional_named_deduced_classifier) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, tag_positional_named_deduced_classifier) \
    , \
        BOOST_PP_TUPLE_ELEM(5, 1, tag_positional_named_deduced_classifier) \
    , \
        BOOST_PP_TUPLE_ELEM(5, 2, tag_positional_named_deduced_classifier) \
    , \
        BOOST_PP_TUPLE_ELEM(5, 3, tag_positional_named_deduced_classifier) \
    )

// PRIVATE //

// Group params pp-list into positional, named, and deduced.
#define CONTRACT_DETAIL_PP_PARAMS_TRAITS_AUX_GROUP( \
        namespace_params, param_classifier_macro) \
    CONTRACT_DETAIL_PP_PARAMS_TRAITS_GROUP_TUPLE_5TO4_( \
    BOOST_PP_LIST_FOLD_LEFT(CONTRACT_DETAIL_PP_PARAMS_TRAITS_GROUP_TUPLE_, \
        ( \
            BOOST_PP_TUPLE_ELEM(2, 0, namespace_params) \
        , \
            BOOST_PP_NIL /* positinal params */ \
        , \
            BOOST_PP_NIL /* named params */ \
        , \
            BOOST_PP_NIL /* deduced params */ \
        , \
            param_classifier_macro \
        ) \
        , BOOST_PP_TUPLE_ELEM(2, 1, namespace_params) \
    ))

// PUBLIC //

// Expand to pp-list of positional params (see PARAM_TRAITS).
#define CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL(params_traits) \
    BOOST_PP_TUPLE_ELEM(4, 1, params_traits)

// Expand to pp-list of named (induced) params (see PARAM_TRAITS).
#define CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMED(params_traits) \
    BOOST_PP_TUPLE_ELEM(4, 2, params_traits)

// Expand to pp-list of (named) deduced params (see PARAM_TRAITS).
#define CONTRACT_DETAIL_PP_PARAMS_TRAITS_DEDUCED(params_traits) \
    BOOST_PP_TUPLE_ELEM(4, 3, params_traits)

#endif // #include guard

