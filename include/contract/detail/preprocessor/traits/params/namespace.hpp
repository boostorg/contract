
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMESPACE_HPP_
#define CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMESPACE_HPP_

// PRIVATE //

#define CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMESPACE_GET_( \
        params, param_name_macro) \
    ( \
        CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* optional trait */ \
        CONTRACT_DETAIL_PP_KEYWORD_NAMESPACE_REMOVE_FRONT( \
                CONTRACT_DETAIL_PP_KEYWORD_USING_REMOVE_FRONT( \
                param_name_macro(BOOST_PP_LIST_FIRST(params)))) \
    , \
        BOOST_PP_LIST_REST(params) \
    )

// Precondition: size(params) >= 1 (i.e., is_cons(params)).
#define CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMESPACE_CHECK_( \
        params, param_name_macro) \
    BOOST_PP_IIF(BOOST_PP_BITAND( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_USING_FRONT( \
                    param_name_macro(BOOST_PP_LIST_FIRST(params))), \
            CONTRACT_DETAIL_PP_KEYWORD_IS_NAMESPACE_FRONT( \
                    CONTRACT_DETAIL_PP_KEYWORD_USING_REMOVE_FRONT( \
                    param_name_macro(BOOST_PP_LIST_FIRST(params))))), \
        CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMESPACE_GET_ \
    , \
        ( \
            CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* no tag-namespace */ \
        , \
            params \
        ) \
        BOOST_PP_TUPLE_EAT(2) \
    )(params, param_name_macro)

// PROTECTED //

// Expand to 2-tuple `(tag_namespace, params)`.
#define CONTRACT_DETAIL_PP_PARAMS_TRAITS_AUX_NAMESPACE( \
        params, param_name_macro) \
    BOOST_PP_IIF(BOOST_PP_LIST_IS_CONS(params), \
        CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMESPACE_CHECK_ \
    , \
        ( \
            CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* no tag-namespace */ \
        , \
            params \
        ) \
        BOOST_PP_TUPLE_EAT(2) \
    )(params, param_name_macro)

// PUBLIC //

// Expand to `[tag_namespace]` (empty is not specified).
#define CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMESPACE(params_traits) \
    BOOST_PP_CAT(CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_, \
            BOOST_PP_TUPLE_ELEM(4, 0, params_traits))

#endif // #include guard

