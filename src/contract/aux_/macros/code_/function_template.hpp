// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_HPP_
#define CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_HPP_

#include "../../symbol.hpp"
#include "../../preprocessor/sign/function_template_args.hpp"
#include <boost/preprocessor.hpp>

// TYPENAME/TEMPLATE WORLAROUND
// The UNUSED template parameter serves to ALWAYS make the function
// a templates so `typename` and `template` can always be used to
// identify types (workaround to avoid requiring the user to
// distinguish templates with (template) ).

// A value template argument of type int is used `int UNUSED` and
// always assigned to `0`. Similarly, a type template argument
// `typename UNUSED` always assigned to `void` could have been
// used. The int value parameter was used hoping it is easier to
// handle thatn the type parameter for the compiler... but not sure.
#define CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_ARG_UNUSED_TYPE_ int
#define CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_ARG_UNUSED_VALUE_ 0

// In addition, the UNUSED parameter is named to indicate an
// overloading error because the compiler will error on redefinition
// of this parameter in case no different argument names are used.
#define CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_ARG_UNUSED_NAME_ \
    CONTRACT_ERROR_overloaded_function_must_use_different_argument_names

// Arguments.

#define CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_ARG_NAME_OP_(z, n, arg) \
    CONTRACT_AUX_PP_SIGN_ARG_NAME(arg)
    
#define CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_ARG_NAMES(sign) \
    CONTRACT_AUX_PP_SIGN_ARG_ENUM(sign, \
            CONTRACT_AUX_PP_SIGN_HAS_FUNCTION_TEMPLATE_ARGS, \
            CONTRACT_AUX_PP_SIGN_FUNCTION_TEMPLATE_ARGS, \
            CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_ARG_NAME_OP_)
        
#define CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_OR_UNUSED_ARG_NAMES( \
        sign) \
    BOOST_PP_IF(CONTRACT_AUX_PP_SIGN_HAS_FUNCTION_TEMPLATE_ARGS( \
            sign), \
        CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_ARG_NAMES \
    , /* else */ \
        /* typename/template workaround */ \
        CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_ARG_UNUSED_VALUE_ \
        BOOST_PP_TUPLE_EAT(1) \
    )(sign) /* delay expansion for commas in tparams */

#define CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_ARG_OP_(z, n, arg) \
    CONTRACT_AUX_PP_SIGN_ARG_TYPE(arg) \
    CONTRACT_AUX_PP_SIGN_ARG_NAME(arg)
                
#define CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_ARGS(sign) \
    CONTRACT_AUX_PP_SIGN_ARG_ENUM(sign, \
            CONTRACT_AUX_PP_SIGN_HAS_FUNCTION_TEMPLATE_ARGS, \
            CONTRACT_AUX_PP_SIGN_FUNCTION_TEMPLATE_ARGS, \
            CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_ARG_OP_)
    
// Signatures.

#define CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_SIGN(sign) \
    BOOST_PP_EXPR_IF( \
            CONTRACT_AUX_PP_SIGN_HAS_FUNCTION_TEMPLATE_ARGS(sign), \
        template< \
    ) \
    BOOST_PP_IF( \
            CONTRACT_AUX_PP_SIGN_HAS_FUNCTION_TEMPLATE_ARGS(sign), \
        CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_ARGS \
    , /* else */ \
        BOOST_PP_TUPLE_EAT(1) \
    )(sign) \
    BOOST_PP_EXPR_IF( \
            CONTRACT_AUX_PP_SIGN_HAS_FUNCTION_TEMPLATE_ARGS(sign), \
        > \
    ) 

#define CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_OR_UNUSED_SIGN(sign) \
    template< \
        BOOST_PP_IF(CONTRACT_AUX_PP_SIGN_HAS_FUNCTION_TEMPLATE_ARGS( \
                sign), \
            CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_ARGS \
        , /* else */ \
            /* typename/template workaround */ \
            CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_ARG_UNUSED_TYPE_ \
            CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_ARG_UNUSED_NAME_ \
            BOOST_PP_TUPLE_EAT(1) \
        )(sign) \
    >

#define CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_OR_UNUSED0_SIGN(sign) \
    template< \
        BOOST_PP_IF(CONTRACT_AUX_PP_SIGN_HAS_FUNCTION_TEMPLATE_ARGS( \
                sign), \
            CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_ARGS \
        , /* else */ \
            /* typename/template workaround */ \
            CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_ARG_UNUSED_TYPE_ \
            CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_ARG_UNUSED_NAME_ \
            BOOST_PP_TUPLE_EAT(1) \
        )(sign) \
    >

#endif // #include guard

