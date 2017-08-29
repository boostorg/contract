// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_CODE_FUNCTION_SIGN_HPP_
#define CONTRACT_AUX_CODE_FUNCTION_SIGN_HPP_

#include "kind.hpp"
#include "function_template.hpp"
#include "../../../config.hpp"
#include "../../preprocessor/sign/export.hpp"
#include "../../preprocessor/sign/inline.hpp"
#include "../../preprocessor/sign/extern.hpp"
#include "../../preprocessor/sign/static.hpp"
#include "../../preprocessor/sign/virtual.hpp"
#include "../../preprocessor/sign/result_type.hpp"
#include "../../preprocessor/sign/function_name.hpp"
#include "../../preprocessor/sign/args.hpp"
#include "../../preprocessor/sign/const.hpp"
#include "../../preprocessor/sign/volatile.hpp"
#include <boost/preprocessor.hpp>

#define CONTRACT_AUX_CODE_FUNCTION_ARG_(z, n, argument) \
    CONTRACT_AUX_PP_SIGN_ARG_TYPE(argument) \
    CONTRACT_AUX_PP_SIGN_ARG_NAME(argument)

#define CONTRACT_AUX_CODE_FUNCTION_COPYABLE_ARG_( \
        z, n, argument) \
    BOOST_PP_EXPR_IF(CONTRACT_AUX_PP_SIGN_ARG_IS_COPYABLE(argument), \
        ::contract::copyable< ) \
    CONTRACT_AUX_PP_SIGN_ARG_TYPE(argument) \
    BOOST_PP_EXPR_IF(CONTRACT_AUX_PP_SIGN_ARG_IS_COPYABLE(argument), \
        > ) \

#define CONTRACT_AUX_CODE_FUNCTION_NAME(kind, sign) \
    BOOST_PP_IF(BOOST_PP_EQUAL(kind, \
            CONTRACT_AUX_CODE_KIND_CONSTRUCTOR), \
        CONTRACT_CONFIG_CONSTRUCTOR_FUNCTION_NAME_ \
    , BOOST_PP_IF(BOOST_PP_EQUAL(kind, \
            CONTRACT_AUX_CODE_KIND_DESTRUCTOR), \
        CONTRACT_CONFIG_DESTRUCTOR_FUNCTION_NAME_ \
    , /* else */ \
        CONTRACT_AUX_PP_SIGN_FUNCTION_NAME(sign) \
    )) /* endif */

#define CONTRACT_AUX_CODE_FUNCTION_SIGN( \
        kind, force_inline, name, sign) \
    /* no invalid combination already enforced by preprocessing */ \
    /* (no static and virtual, only constructors explicit, etc) */ \
    /* NOTE: `explicit` is not used because it only applies to */ \
    /* constructors (which cannot be defined by this library */ \
    /* because C++ does not support delegating constructors). */ \
    CONTRACT_AUX_PP_SIGN_EXPORT(sign) \
    CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_SIGN(sign) \
    BOOST_PP_EXPR_IF(BOOST_PP_OR(force_inline, \
            CONTRACT_AUX_PP_SIGN_IS_INLINE(sign)), inline) \
    /* NOTE: `extern` shall not be repeated ihere (for the body, */ \
    /* nor for the original function definition, etc) because it */ \
    /* needs to appear only once and in the original function */ \
    /* signature declaration programmed by the user. */ \
    CONTRACT_AUX_PP_SIGN_STATIC(sign) \
    CONTRACT_AUX_PP_SIGN_VIRTUAL(sign) \
    CONTRACT_AUX_PP_SIGN_RESULT_TYPE(sign) \
    name \
    BOOST_PP_LPAREN() \
        CONTRACT_AUX_PP_SIGN_ARG_ENUM(sign, \
                CONTRACT_AUX_PP_SIGN_HAS_ARGS, \
                CONTRACT_AUX_PP_SIGN_ARGS, \
                CONTRACT_AUX_CODE_FUNCTION_ARG_) \
    BOOST_PP_RPAREN() \
    CONTRACT_AUX_PP_SIGN_CONST(sign) \
    CONTRACT_AUX_PP_SIGN_VOLATILE(sign)

// The function type template parameter `F`.
#define CONTRACT_AUX_CODE_F(sign) \
    /* result_type */ \
    CONTRACT_AUX_PP_SIGN_RESULT_TYPE(sign) \
    ( \
        /* [copyable]<class_type [const]> * */ \
        BOOST_PP_EXPR_IF(CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER( \
                sign), \
            BOOST_PP_EXPR_IF( \
                    CONTRACT_AUX_PP_SIGN_CLASS_TYPE_IS_COPYABLE( \
                    sign), \
                ::contract::copyable< ) \
            CONTRACT_AUX_PP_SIGN_CLASS_TYPE(sign) \
            CONTRACT_AUX_PP_SIGN_CONST(sign) \
            CONTRACT_AUX_PP_SIGN_VOLATILE(sign) \
            BOOST_PP_EXPR_IF( \
                    CONTRACT_AUX_PP_SIGN_CLASS_TYPE_IS_COPYABLE( \
                    sign), \
                > ) \
            * /* pointer (must be outside of copyable<>) */ \
        ) /* endif */ \
        /* , [copyable]< argument_type0 >, ... */ \
        BOOST_PP_COMMA_IF(BOOST_PP_AND( \
                CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER(sign), \
                CONTRACT_AUX_PP_SIGN_HAS_ARGS(sign))) \
        CONTRACT_AUX_PP_SIGN_ARG_ENUM(sign, \
                CONTRACT_AUX_PP_SIGN_HAS_ARGS, \
                CONTRACT_AUX_PP_SIGN_ARGS, \
                CONTRACT_AUX_CODE_FUNCTION_COPYABLE_ARG_) \
    )

#endif // #include guard

