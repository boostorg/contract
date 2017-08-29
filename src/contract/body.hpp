// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_BODY_HPP_
#define CONTRACT_BODY_HPP_

#include "config.hpp"
#include "aux_/symbol.hpp"
#include "aux_/preprocessor/sign/function_name.hpp"
#include <boost/preprocessor.hpp>

// Constructor and destructor must specify both class type and name
// bacause they can be different from tempate `myclass<T>::myclass`
// (if `myclass<T>::myclass<T>` cannot be used for constructor name,
// and the same gives an "obsolete" warning for destructors...).

#if defined(CONTRACT_CHECK_CLASS_INVARIANT) || \
        defined(CONTRACT_CHECK_PRECONDITION) || \
        defined(CONTRACT_CHECK_POSTCONDITION)
#   define CONTRACT_CTOR_BODY_(class_type, ctor_name, body_name) \
        void class_type::CONTRACT_AUX_INTERNAL_SYMBOL( \
                BOOST_PP_CAT(body_, body_name))
#else
#   define CONTRACT_CTOR_BODY_(class_type, ctor_name, body_name) \
        class_type::ctor_name
#endif // check contract

#define CONTRACT_CONSTRUCTOR_BODY(class_type, class_name) \
    CONTRACT_CTOR_BODY_(class_type, class_name, \
            CONTRACT_CONFIG_CONSTRUCTOR_FUNCTION_NAME_)

// The ~ is NOT specified by caller (it is added here). This is to
// be consistent with signature-sequence for destructors.
#define CONTRACT_DESTRUCTOR_BODY(class_type, class_name) \
    CONTRACT_CTOR_BODY_(class_type, ~class_name, \
            CONTRACT_CONFIG_DESTRUCTOR_FUNCTION_NAME_)

// Use `BODY(operator(==, equal)` for operators.
#if defined(CONTRACT_CHECK_CLASS_INVARIANT) || \
        defined(CONTRACT_CHECK_PRECONDITION) || \
        defined(CONTRACT_CHECK_POSTCONDITION)
#   define CONTRACT_BODY(function_name) \
        CONTRACT_AUX_INTERNAL_SYMBOL(BOOST_PP_CAT(body_, \
                CONTRACT_AUX_PP_SIGN_FUNCTION_NAME_WORD( \
                function_name)))
#else
#   define CONTRACT_BODY(function_name) \
            CONTRACT_AUX_PP_SIGN_FUNCTION_NAME_SYMBOLIC(function_name)
#endif // check contract

#endif // #include guard

