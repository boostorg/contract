// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_CODE_CONTRACT_CLASS_HPP_
#define CONTRACT_AUX_CODE_CONTRACT_CLASS_HPP_

#include "kind.hpp"
#include "contract_name.hpp"
#include "precondition.hpp"
#include "postcondition.hpp"
#include "function_sign.hpp"
#include "function_template.hpp"
#include "../../check01.hpp"
#include "../../preprocessor/sign/static.hpp"
#include "../../preprocessor/sign/result_type.hpp"
#include "../../preprocessor/sign/class_type.hpp"
#include "../../preprocessor/sign/base_types.hpp"
#include "../../preprocessor/sign/args.hpp"
#include <boost/preprocessor.hpp>

#define CONTRACT_AUX_CODE_CONTRACT_CLASS_BASE_CONTRACT_( \
        z, n, kind_n_sign) \
    /* base_type::contract_name<UNUSED> */ \
    typename BOOST_PP_SEQ_ELEM(n, \
            CONTRACT_AUX_PP_SIGN_BASE_TYPES(BOOST_PP_TUPLE_ELEM( \
                    2, 1, kind_n_sign)))::template \
            CONTRACT_AUX_CODE_CONTRACT_NAME( \
                    BOOST_PP_TUPLE_ELEM(2, 0, kind_n_sign), \
                    BOOST_PP_TUPLE_ELEM(2, 1, kind_n_sign)) < \
    CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_OR_UNUSED_ARG_NAMES( \
            BOOST_PP_TUPLE_ELEM(2, 1, kind_n_sign)) \
            >

#define CONTRACT_AUX_CODE_CONTRACT_CLASS_BASE_CONTRACTS_(kind, sign) \
    BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE( \
                    CONTRACT_AUX_PP_SIGN_BASE_TYPES(sign)), \
            CONTRACT_AUX_CODE_CONTRACT_CLASS_BASE_CONTRACT_, \
            (kind, sign)) \

// In a separate macro to handle eventual template param commas.
#define CONTRACT_AUX_CODE_CONTRACT_CLASS_TPARAM_OR_UNUSED_( \
        sign) \
    < CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_OR_UNUSED_ARG_NAMES(sign) >

// Can be function, constructor, or destructor member.
#define CONTRACT_AUX_CODE_CONTRACT_CLASS_BASE_( \
        kind, sign) \
    ::contract:: \
    BOOST_PP_IF(BOOST_PP_EQUAL(kind, \
            CONTRACT_AUX_CODE_KIND_CONSTRUCTOR), \
        constructor \
    , BOOST_PP_IF(BOOST_PP_EQUAL(kind, \
            CONTRACT_AUX_CODE_KIND_DESTRUCTOR), \
        destructor \
    , BOOST_PP_IF(CONTRACT_AUX_PP_SIGN_IS_STATIC(sign), \
        static_member_function \
    , BOOST_PP_IF(CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER(sign), \
        nonstatic_member_function \
    , /* else (non member function) */ \
        nonmember_function \
    )))) < \
            CONTRACT_AUX_CODE_F(sign) \
            /* , base0::contract-name, ... (only non-static memi) */ \
            /* which is enforced by preprocessing) */ \
            BOOST_PP_COMMA_IF(CONTRACT_AUX_PP_SIGN_HAS_BASES(sign)) \
            BOOST_PP_IF(CONTRACT_AUX_PP_SIGN_HAS_BASES(sign), \
                CONTRACT_AUX_CODE_CONTRACT_CLASS_BASE_CONTRACTS_ \
            , \
                BOOST_PP_TUPLE_EAT(2) \
            )(kind, sign) \
    >

#define CONTRACT_AUX_CODE_CONTRACT_CLASS(kind, sign) \
    /* struct for pub inherit of call() and pub default constr. */ \
    CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_OR_UNUSED0_SIGN(sign) \
    struct CONTRACT_AUX_CODE_CONTRACT_NAME(kind, sign): \
            CONTRACT_AUX_CODE_CONTRACT_CLASS_BASE_(kind, sign) { \
        /* default constructor */ \
        CONTRACT_AUX_CODE_CONTRACT_NAME(kind, sign)(): \
                /* constr base class passing pre, post, and body */ \
                CONTRACT_AUX_CODE_CONTRACT_CLASS_BASE_(kind, sign)( \
                /* &class_type::contract_body_func_name_ */ \
                & /* make it a function pointer */ \
                BOOST_PP_EXPR_IF( \
                        CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER(sign), \
                    CONTRACT_AUX_PP_SIGN_CLASS_TYPE(sign) :: \
                    BOOST_PP_EXPR_IF( \
    CONTRACT_AUX_PP_SIGN_HAS_FUNCTION_TEMPLATE_ARGS(sign), \
                        template \
                    ) /* endif */ \
                ) /* endif */ \
                CONTRACT_BODY( \
                        CONTRACT_AUX_CODE_FUNCTION_NAME(kind, sign)) \
                BOOST_PP_EXPR_IF( \
    CONTRACT_AUX_PP_SIGN_HAS_FUNCTION_TEMPLATE_ARGS(sign), \
                    < \
                ) /* endif */ \
                CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_ARG_NAMES(sign) \
                BOOST_PP_EXPR_IF( \
    CONTRACT_AUX_PP_SIGN_HAS_FUNCTION_TEMPLATE_ARGS(sign), \
                    > \
                ) \
                /* , &[class_type::]contract_precondition_f-name_ */ \
                /* (but not for destructor) */ \
                BOOST_PP_COMMA_IF(BOOST_PP_AND( \
                        CONTRACT_AUX_CHECK_PRECONDITION_01, \
                        BOOST_PP_NOT(BOOST_PP_EQUAL(kind, \
                                CONTRACT_AUX_CODE_KIND_DESTRUCTOR)))) \
                BOOST_PP_IF(BOOST_PP_AND( \
                        CONTRACT_AUX_CHECK_PRECONDITION_01, \
                        BOOST_PP_NOT(BOOST_PP_EQUAL(kind, \
                                CONTRACT_AUX_CODE_KIND_DESTRUCTOR))), \
                    & /* make it a function pointer */ \
                    BOOST_PP_EXPR_IF( \
                            CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER(sign), \
                        CONTRACT_AUX_PP_SIGN_CLASS_TYPE(sign) \
                        ::template /* typename workaround */ \
                    ) /* endif */ \
                    CONTRACT_AUX_CODE_PRECONDITION_NAME(kind, sign) \
                    CONTRACT_AUX_CODE_CONTRACT_CLASS_TPARAM_OR_UNUSED_ \
                , /* else */ \
                    BOOST_PP_TUPLE_EAT(1) \
                )(sign) \
                /* , &[class_type::]contract_postcondition_f-name_ */ \
                /* (but not for destructor) */ \
                BOOST_PP_COMMA_IF(BOOST_PP_AND( \
                        CONTRACT_AUX_CHECK_POSTCONDITION_01, \
                        BOOST_PP_NOT(BOOST_PP_EQUAL(kind, \
                                CONTRACT_AUX_CODE_KIND_DESTRUCTOR)))) \
                BOOST_PP_IF(BOOST_PP_AND( \
                        CONTRACT_AUX_CHECK_POSTCONDITION_01, \
                        BOOST_PP_NOT(BOOST_PP_EQUAL(kind, \
                                CONTRACT_AUX_CODE_KIND_DESTRUCTOR))), \
                    & /* make it a function pointer */ \
                    BOOST_PP_EXPR_IF( \
                            CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER(sign), \
                        CONTRACT_AUX_PP_SIGN_CLASS_TYPE(sign) \
                        ::template /* typename workaround */ \
                    ) /* endif */ \
                    CONTRACT_AUX_CODE_POSTCONDITION_NAME(kind, sign) \
                    CONTRACT_AUX_CODE_CONTRACT_CLASS_TPARAM_OR_UNUSED_ \
                , /* else */ \
                    BOOST_PP_TUPLE_EAT(1) \
                )(sign) \
                ) {} /* empty constructor implementation */ \
    }; /* contract class */

#endif // #include guard

