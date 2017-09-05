
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_PARAMS_TRAITS_VOID_HPP_
#define CONTRACT_DETAIL_PP_PARAMS_TRAITS_VOID_HPP_

// PRIVATE //

// Precondition: size(params) == 1.
#define CONTRACT_DETAIL_PP_PARAMS_TRAITS_CHECK_VOID_(params, param_name_macro) \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_VOID_FRONT( /* false if unary */\
            param_name_macro(BOOST_PP_LIST_FIRST(params))), \
        BOOST_PP_NIL /* `(func_name)( void )` returns empty param pp-list */ \
    , \
        params \
    )

// PROTECTED //

// Expand to nil pp-list if params is `(void, NIL)`.
#define CONTRACT_DETAIL_PP_PARAMS_TRAITS_AUX_VOID(params, param_name_macro) \
    BOOST_PP_IIF(BOOST_PP_EQUAL(BOOST_PP_LIST_SIZE(params), 1), \
        CONTRACT_DETAIL_PP_PARAMS_TRAITS_CHECK_VOID_ \
    , \
        params BOOST_PP_TUPLE_EAT(2) \
    )(params, param_name_macro)

#endif // #include guard

