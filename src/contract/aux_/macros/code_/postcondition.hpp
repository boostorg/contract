// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_CODE_POSTCONDITION_HPP_
#define CONTRACT_AUX_CODE_POSTCONDITION_HPP_

#include "function_sign.hpp"
#include "contract_name.hpp"
#include "function_template.hpp"
#include "../../symbol.hpp"
#include "../../preprocessor/sign/static.hpp"
#include "../../preprocessor/sign/class_type.hpp"
#include "../../preprocessor/sign/args.hpp"
#include "../../preprocessor/sign/postcondition.hpp"
#include <boost/preprocessor.hpp>
    
#define CONTRACT_AUX_CODE_POSTCONDITION_ARG_(z, n, argument) \
    /* arg<argument_type> argument_name */ \
    typename ::contract::aux::arg< \
            CONTRACT_AUX_PP_SIGN_ARG_TYPE(argument) >::type \
    CONTRACT_AUX_PP_SIGN_ARG_NAME(argument) \
    /* , */ \
    BOOST_PP_COMMA() \
    /* arg< old< copyable<argument_type> > > OLDOF(argument_name) */ \
    /* or noold (with no argument name) if not copyable */ \
    BOOST_PP_IF(CONTRACT_AUX_PP_SIGN_ARG_IS_COPYABLE(argument), \
        typename ::contract::aux::arg< typename \
                ::contract::aux::old< ::contract::copyable< \
                        CONTRACT_AUX_PP_SIGN_ARG_TYPE(argument) \
                > /* no ::type */ >::type >::type \
        CONTRACT_OLDOF(CONTRACT_AUX_PP_SIGN_ARG_NAME(argument)) \
    , /* else (not copyable) */ \
        ::contract::noold /* no old for this argument */ \
    ) /* endif */

// Postcondition name must be prefixed with full contract name to
// allow for overloading (because precondition signature eventually
// adds const qualifiers to function and its arguments).
#define CONTRACT_AUX_CODE_POSTCONDITION_NAME(kind, sign) \
    CONTRACT_AUX_CODE_CONTRACT_NAME_PREFIXED(kind, sign, \
            (postcondition))

#define CONTRACT_AUX_CODE_POSTCONDITION_SIGN(kind, sign) \
    CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_OR_UNUSED_SIGN(sign) \
    /* static-member postcond. is static (no object) */ \
    BOOST_PP_EXPR_IF(CONTRACT_AUX_PP_SIGN_IS_STATIC(sign), \
        static \
    ) \
    void CONTRACT_AUX_CODE_POSTCONDITION_NAME(kind, sign)( \
            /* old object only if non-static member, plus always */ \
            /* noold for constr. because non copyable class type */ \
            BOOST_PP_EXPR_IF(BOOST_PP_AND( \
                    CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER(sign), \
                    BOOST_PP_NOT( \
                            CONTRACT_AUX_PP_SIGN_IS_STATIC(sign))), \
                BOOST_PP_IF( \
                        CONTRACT_AUX_PP_SIGN_CLASS_TYPE_IS_COPYABLE( \
                        sign), \
                    typename ::contract::aux::arg< typename \
                            ::contract::aux::old< \
                            ::contract::copyable< \
                                CONTRACT_AUX_PP_SIGN_CLASS_TYPE( \
                                sign)* /* pointer to class type */ \
                            > /* no ::type */ >::type >::type \
                            CONTRACT_OLDOF(this) \
                , /* else */ \
                    ::contract::noold /* no old object */ \
                ) /* endif */ \
            ) /* endif */ \
            BOOST_PP_COMMA_IF(BOOST_PP_AND( \
                    CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER(sign), \
                    BOOST_PP_AND(BOOST_PP_NOT( \
                            CONTRACT_AUX_PP_SIGN_IS_STATIC(sign)), \
                            CONTRACT_AUX_PP_SIGN_HAS_ARGS(sign)))) \
            CONTRACT_AUX_PP_SIGN_ARG_ENUM(sign, \
                    CONTRACT_AUX_PP_SIGN_HAS_ARGS, \
                    CONTRACT_AUX_PP_SIGN_ARGS, \
                    CONTRACT_AUX_CODE_POSTCONDITION_ARG_) \
            BOOST_PP_COMMA_IF(BOOST_PP_NOT( \
                    CONTRACT_AUX_PP_SIGN_IS_VOID_RESULT(sign))) \
            BOOST_PP_EXPR_IF(BOOST_PP_NOT( \
                    CONTRACT_AUX_PP_SIGN_IS_VOID_RESULT(sign)), \
                typename ::contract::aux::arg< \
                        CONTRACT_AUX_PP_SIGN_RESULT_TYPE(sign) \
                        >::type \
                CONTRACT_AUX_PP_SIGN_POSTCONDITION_RESULT(sign)) \
            ) \
    /* static-member and non-member no const (no object) */ \
    BOOST_PP_EXPR_IF(BOOST_PP_AND( \
            CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER(sign), \
            BOOST_PP_NOT(CONTRACT_AUX_PP_SIGN_IS_STATIC(sign))), \
        const \
    )

#define CONTRACT_AUX_CODE_POSTCONDITION(kind, sign) \
    CONTRACT_AUX_CODE_POSTCONDITION_SIGN(kind, sign) /* signature */ \
    CONTRACT_AUX_PP_SIGN_POSTCONDITION(sign) /* code block */

#endif // #include guard

