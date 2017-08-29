// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_CODE_STATIC_VALIDATE_HPP_
#define CONTRACT_AUX_CODE_STATIC_VALIDATE_HPP_

#include "kind.hpp"
#include "../../preprocessor/sign/class_type.hpp"
#include "../../preprocessor/sign/function_name.hpp"
#include <boost/type_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/preprocessor.hpp>

// Compile-time signature validation. Any signature validation that
// can be done earlier at preprocessing-time should be done by
// PP_SIGN_VALIDATE() instead.
#define CONTRACT_AUX_CODE_STATIC_VALIDATE(kind, sign) \
    /* enforce class_type == class_name for constr and destr */ \
    BOOST_PP_EXPR_IF(BOOST_PP_EQUAL(kind, \
            CONTRACT_AUX_CODE_KIND_CONSTRUCTOR), \
        BOOST_MPL_ASSERT_MSG( (boost::is_same< \
                CONTRACT_AUX_PP_SIGN_CLASS_TYPE(sign), \
                CONTRACT_AUX_PP_SIGN_FUNCTION_NAME(sign) >::value), \
                /* must postfix contract so unique MPL class */ \
                BOOST_PP_CAT(CONTRACT_ERROR_constructor_name_must_match_class_type_for_, CONTRACT_AUX_CODE_CONTRACT_NAME(kind, sign)), \
                ()) \
        ; /* must close ASSERT macro within class scope */ \
    ) \
    /* enforce class_type == class_name for constr and destr */ \
    BOOST_PP_EXPR_IF(BOOST_PP_EQUAL(kind, \
            CONTRACT_AUX_CODE_KIND_DESTRUCTOR), \
        BOOST_MPL_ASSERT_MSG( (boost::is_same< \
                CONTRACT_AUX_PP_SIGN_CLASS_TYPE(sign), \
                CONTRACT_AUX_PP_SIGN_FUNCTION_NAME(sign) >::value), \
                /* must postfix contract so unique MPL class */ \
                BOOST_PP_CAT(CONTRACT_ERROR_destructor_name_must_match_class_type_, CONTRACT_AUX_CODE_CONTRACT_NAME(kind, sign)), \
                ()) \
        ; /* must close ASSERT macro within class scope */ \
    )

#endif // #include guard

