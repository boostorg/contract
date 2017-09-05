// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_ARG_HPP_
#define CONTRACT_AUX_PP_SIGN_ARG_HPP_

#include <boost/preprocessor.hpp>

// Utilities to inspect single argument trits. Used for both function
// arguments and function template parameters (called arguments).

// arg := ([copyable] EMPTY, type EMPTY, name EMPTY)

// Template parameters are never copyable...
#define CONTRACT_AUX_PP_SIGN_ARG_IS_COPYABLE(arg) \
    BOOST_PP_NOT(BOOST_PP_IS_EMPTY( \
            BOOST_PP_TUPLE_ELEM(3, 0, arg)(/* empand empty*/)))

#define CONTRACT_AUX_PP_SIGN_ARG_TYPE(arg) \
    BOOST_PP_TUPLE_ELEM(3, 1, arg) \
            (/* expand empty (never empty, used to handle no arg) */)

#define CONTRACT_AUX_PP_SIGN_ARG_NAME(arg) \
    BOOST_PP_TUPLE_ELEM(3, 2, arg) \
            (/* expand empty (never empty, used to handle no arg) */)

// Argument enumeration.

#define CONTRACT_AUX_PP_SIGN_ARG_ENUM_ARG_OP_(z, n, args_n_op) \
    BOOST_PP_TUPLE_ELEM(2, 1, args_n_op) /* operation macro */ \
            (z, n, \
                    BOOST_PP_SEQ_ELEM(n, /* arg */ \
                    BOOST_PP_TUPLE_ELEM(2, 0, args_n_op)) /* args */ \
            )

#define CONTRACT_AUX_PP_SIGN_ARG_ENUM_OP_(sign, \
        get_args_macro, op_arg_macro) \
    BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(get_args_macro(sign)), \
            CONTRACT_AUX_PP_SIGN_ARG_ENUM_ARG_OP_, \
            (get_args_macro(sign), op_arg_macro) )

/* Enumerate all argument applying op_arg_macro(z, n, argument). */
#define CONTRACT_AUX_PP_SIGN_ARG_ENUM(sign, \
        has_args_macro, get_args_macro, op_arg_macro) \
    BOOST_PP_IF(has_args_macro(sign), \
        CONTRACT_AUX_PP_SIGN_ARG_ENUM_OP_ \
    , \
        BOOST_PP_TUPLE_EAT(3) \
    )(sign, get_args_macro, op_arg_macro)

#define CONTRACT_AUX_PP_SIGN_ARG_ENUM_TRAILING(sign, \
        has_args_macro, get_args_macro, op_arg_macro) \
    BOOST_PP_COMMA_IF(has_args_macro(sign)) \
    CONTRACT_AUX_PP_SIGN_ARG_ENUM(sign, \
            has_args_macro, get_args_macro, op_arg_macro)

#endif // #include guard

