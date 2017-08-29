// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_FUNCTION_HPP_
#define CONTRACT_AUX_FUNCTION_HPP_

#include "code_function.hpp"
#include "code_/static_error.hpp"
#include "code_/kind.hpp"
#include "../preprocessor/sign/parse_function.hpp"
#include "../preprocessor/sign/parse_constructor.hpp"
#include "../preprocessor/sign/parse_destructor.hpp"
#include <boost/preprocessor.hpp>

#define CONTRACT_AUX_FUNCTION(seq) \
    CONTRACT_AUX_FUNCTION_PARSED_( \
            CONTRACT_AUX_CODE_KIND_FUNCTION, \
            CONTRACT_AUX_PP_SIGN_PARSE_FUNCTION(seq))

#define CONTRACT_AUX_CONSTRUCTOR(seq) \
    CONTRACT_AUX_FUNCTION_PARSED_( \
            CONTRACT_AUX_CODE_KIND_CONSTRUCTOR, \
            CONTRACT_AUX_PP_SIGN_PARSE_CONSTRUCTOR(seq))

#define CONTRACT_AUX_DESTRUCTOR(seq) \
    CONTRACT_AUX_FUNCTION_PARSED_( \
            CONTRACT_AUX_CODE_KIND_DESTRUCTOR, \
            CONTRACT_AUX_PP_SIGN_PARSE_DESTRUCTOR(seq))

// Above intentionaly #defined before FUNCTION_PARSED_() to force 
// single expansiion of PARSE_FUNCTION()

#define CONTRACT_AUX_FUNCTION_OK_(kind, seq_sign_err) \
    CONTRACT_AUX_CODE_FUNCTION(kind, \
            BOOST_PP_TUPLE_ELEM(3, 1, seq_sign_err))

#define CONTRACT_AUX_FUNCTION_ERR_(kind, seq_sign_err) \
    CONTRACT_AUX_CODE_STATIC_ERROR(BOOST_PP_TUPLE_ELEM(2, 1, \
            BOOST_PP_TUPLE_ELEM(3, 2, seq_sign_err)))

#define CONTRACT_AUX_FUNCTION_PARSED_(kind, seq_sign_err) \
    BOOST_PP_IF(BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_TUPLE_ELEM( \
            3, 2, seq_sign_err)), \
        CONTRACT_AUX_FUNCTION_ERR_ /* expand to error */ \
    , /* else */ \
        CONTRACT_AUX_FUNCTION_OK_ /* expand to code */ \
    )(kind, seq_sign_err)

#endif // #include guard

