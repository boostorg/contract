// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_CODE_CONTRACTED_FUNCTION_HPP_
#define CONTRACT_AUX_CODE_CONTRACTED_FUNCTION_HPP_

#include "contract_name.hpp"
#include "args.hpp"
#include "function_sign.hpp"
#include "function_template.hpp"
#include "../../preprocessor/sign/result_type.hpp"
#include "../../preprocessor/sign/static.hpp"
#include "../../preprocessor/sign/function_name.hpp"
#include "../../preprocessor/sign/class.hpp"
#include <boost/preprocessor.hpp>

#define CONTRACT_AUX_CODE_CONTRACTED_FUNCTION_MEMBER(kind, sign) \
    { \
        BOOST_PP_EXPR_IF(BOOST_PP_NOT( \
                CONTRACT_AUX_PP_SIGN_IS_VOID_RESULT(sign)), \
            return \
        ) \
        ( /* extra paren `(` to handle commas in macro params */ \
            CONTRACT_AUX_CODE_CONTRACT_NAME(kind, sign) \
                < \
    CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_OR_UNUSED_ARG_NAMES(sign) \
                > \
                (/* creates contract object */ \
                ).call( \
                BOOST_PP_EXPR_IF(BOOST_PP_AND( \
                        CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER(sign), \
                        BOOST_PP_NOT( \
                        CONTRACT_AUX_PP_SIGN_IS_STATIC(sign))), \
                    this \
                ) \
                BOOST_PP_COMMA_IF(BOOST_PP_AND( \
                        CONTRACT_AUX_PP_SIGN_HAS_ARGS(sign), \
                        BOOST_PP_AND( \
                        CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER(sign), \
                        BOOST_PP_NOT( \
                        CONTRACT_AUX_PP_SIGN_IS_STATIC(sign))))) \
                /* argument0, ... */ \
                CONTRACT_AUX_CODE_ARG_NAMES(sign) \
                ) \
        ); /* extra parenthesis `)` to handle commas in macro params */ \
    }

#define CONTRACT_AUX_CODE_CONTRACTED_FUNCTION_NON_MEMBER(kind, sign) \
    CONTRACT_AUX_CODE_FUNCTION_SIGN(kind, \
            1, /* force inline to avoid duplicate definition err */ \
            /* use name symbol to handle operators */ \
            CONTRACT_AUX_PP_SIGN_FUNCTION_NAME_SYMBOL(sign), sign) \
    CONTRACT_AUX_CODE_CONTRACTED_FUNCTION_MEMBER(kind, sign)

#endif // #include guard

