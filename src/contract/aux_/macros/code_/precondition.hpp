// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_CODE_PRECONDITION_HPP_
#define CONTRACT_AUX_CODE_PRECONDITION_HPP_

#include "kind.hpp"
#include "contract_name.hpp"
#include "function_sign.hpp"
#include "function_template.hpp"
#include "../../symbol.hpp"
#include "../../preprocessor/sign/static.hpp"
#include "../../preprocessor/sign/args.hpp"
#include "../../preprocessor/sign/precondition.hpp"
#include <boost/preprocessor.hpp>
    
#define CONTRACT_AUX_CODE_PRECONDITION_ARG_(z, n, argument) \
    typename ::contract::aux::arg< \
            CONTRACT_AUX_PP_SIGN_ARG_TYPE(argument) >::type \
    CONTRACT_AUX_PP_SIGN_ARG_NAME(argument)

// Precondition name must be prefixed with full contract name to
// allow for overloading (because precondition signature eventually
// adds const qualifiers to function and its arguments).
#define CONTRACT_AUX_CODE_PRECONDITION_NAME(kind, sign) \
    CONTRACT_AUX_CODE_CONTRACT_NAME_PREFIXED(kind, sign, \
            (precondition))

#define CONTRACT_AUX_CODE_PRECONDITION_SIGN(kind, sign) \
    CONTRACT_AUX_CODE_FUNCTION_TEMPLATE_OR_UNUSED_SIGN(sign) \
    /* static-member and constr. precond. is static (no object) */ \
    BOOST_PP_EXPR_IF(BOOST_PP_OR( \
            CONTRACT_AUX_PP_SIGN_IS_STATIC(sign), \
            BOOST_PP_EQUAL(kind, \
                    CONTRACT_AUX_CODE_KIND_CONSTRUCTOR)), \
        static \
    ) \
    void CONTRACT_AUX_CODE_PRECONDITION_NAME(kind, sign)( \
            CONTRACT_AUX_PP_SIGN_ARG_ENUM(sign, \
                    CONTRACT_AUX_PP_SIGN_HAS_ARGS, \
                    CONTRACT_AUX_PP_SIGN_ARGS, \
                    CONTRACT_AUX_CODE_PRECONDITION_ARG_) \
            ) \
    /* static-member, constr, and non-member no const (no object) */ \
    BOOST_PP_EXPR_IF(BOOST_PP_AND( \
            CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER(sign), \
            BOOST_PP_NOT(BOOST_PP_OR( \
                    CONTRACT_AUX_PP_SIGN_IS_STATIC(sign), \
                    BOOST_PP_EQUAL(kind, \
                            CONTRACT_AUX_CODE_KIND_CONSTRUCTOR)))), \
        const \
    )

#define CONTRACT_AUX_CODE_PRECONDITION(kind, sign) \
    CONTRACT_AUX_CODE_PRECONDITION_SIGN(kind, sign) /* signature */ \
    CONTRACT_AUX_PP_SIGN_PRECONDITION(sign) /* code block */

#endif // #include guard

