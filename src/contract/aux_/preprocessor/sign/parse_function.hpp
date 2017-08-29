// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_FUNCTION_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_FUNCTION_HPP_

#include "parse_/body.hpp"
#include "parse_/postcondition.hpp"
#include "parse_/precondition.hpp"
#include "parse_/volatile.hpp"
#include "parse_/const.hpp"
#include "parse_/args.hpp"
#include "parse_/function_name.hpp"
#include "parse_/result_type.hpp"
#include "parse_/virtual.hpp"
#include "parse_/static.hpp"
#include "parse_/extern.hpp"
#include "parse_/inline.hpp"
#include "parse_/explicit.hpp"
#include "parse_/template.hpp"
#include "parse_/export.hpp"
#include "parse_/access.hpp"
#include "parse_/base_types.hpp"
#include "parse_/class_type.hpp"
#include "parse_/class.hpp"
#include "parse_/validate.hpp"
#include "class.hpp"

#define CONTRACT_AUX_PP_SIGN_PARSE_FUNCTION_MEMBER_(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_CONTRACT( \
    CONTRACT_AUX_PP_SIGN_PARSE_BODY( \
    CONTRACT_AUX_PP_SIGN_PARSE_POSTCONDITION( \
    CONTRACT_AUX_PP_SIGN_PARSE_PRECONDITION( \
    CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_MEMBER( \
    CONTRACT_AUX_PP_SIGN_PARSE_VOLATILE( \
    CONTRACT_AUX_PP_SIGN_PARSE_CONST( \
    CONTRACT_AUX_PP_SIGN_PARSE_COPYABLE_ARGS( \
    CONTRACT_AUX_PP_SIGN_PARSE_FUNCTION_NAME( \
    CONTRACT_AUX_PP_SIGN_PARSE_RESULT_TYPE( \
    CONTRACT_AUX_PP_SIGN_PARSE_VIRTUAL( \
    CONTRACT_AUX_PP_SIGN_PARSE_STATIC( \
    CONTRACT_AUX_PP_SIGN_PARSE_NO_EXTERN( \
    CONTRACT_AUX_PP_SIGN_PARSE_INLINE( \
    CONTRACT_AUX_PP_SIGN_PARSE_NO_EXPLICIT( \
    CONTRACT_AUX_PP_SIGN_PARSE_TEMPLATE_ARGS( \
    CONTRACT_AUX_PP_SIGN_PARSE_NO_EXPORT( \
    CONTRACT_AUX_PP_SIGN_PARSE_ACCESS( \
    CONTRACT_AUX_PP_SIGN_PARSE_BASE_TYPES( \
    CONTRACT_AUX_PP_SIGN_PARSE_COPYABLE_CLASS_TYPE( \
            seq_sign_err \
    ))))))))))))))))))))

#define CONTRACT_AUX_PP_SIGN_PARSE_FUNCTION_NON_MEMBER_(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_CONTRACT( \
    CONTRACT_AUX_PP_SIGN_PARSE_BODY( \
    CONTRACT_AUX_PP_SIGN_PARSE_POSTCONDITION( \
    CONTRACT_AUX_PP_SIGN_PARSE_PRECONDITION( \
    CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_NON_MEMBER( \
    CONTRACT_AUX_PP_SIGN_PARSE_NO_VOLATILE( \
    CONTRACT_AUX_PP_SIGN_PARSE_NO_CONST( \
    CONTRACT_AUX_PP_SIGN_PARSE_COPYABLE_ARGS( \
    CONTRACT_AUX_PP_SIGN_PARSE_FUNCTION_NAME( \
    CONTRACT_AUX_PP_SIGN_PARSE_RESULT_TYPE( \
    CONTRACT_AUX_PP_SIGN_PARSE_NO_VIRTUAL( \
    CONTRACT_AUX_PP_SIGN_PARSE_NO_STATIC( \
    CONTRACT_AUX_PP_SIGN_PARSE_EXTERN( \
    CONTRACT_AUX_PP_SIGN_PARSE_INLINE( \
    CONTRACT_AUX_PP_SIGN_PARSE_NO_EXPLICIT( \
    CONTRACT_AUX_PP_SIGN_PARSE_TEMPLATE_ARGS( \
    CONTRACT_AUX_PP_SIGN_PARSE_EXPORT( \
    CONTRACT_AUX_PP_SIGN_PARSE_NO_ACCESS( \
    CONTRACT_AUX_PP_SIGN_PARSE_NO_BASE_TYPES( \
    CONTRACT_AUX_PP_SIGN_PARSE_NO_CLASS_TYPE( \
            seq_sign_err \
    ))))))))))))))))))))

#define CONTRACT_AUX_PP_SIGN_PARSE_FUNCTION_(seq_sign_err) \
    BOOST_PP_IF(CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER( \
            BOOST_PP_TUPLE_ELEM(3, 1, seq_sign_err)), \
        CONTRACT_AUX_PP_SIGN_PARSE_FUNCTION_MEMBER_ \
    , /* else */ \
        CONTRACT_AUX_PP_SIGN_PARSE_FUNCTION_NON_MEMBER_ \
    )(seq_sign_err)

#define CONTRACT_AUX_PP_SIGN_PARSE_FUNCTION(seq) \
    CONTRACT_AUX_PP_SIGN_PARSE_FUNCTION_( \
    CONTRACT_AUX_PP_SIGN_PARSE_CLASS( \
            /* init seq_sign_err 3-elem tuple */ \
            /* fun signature to parse */ \
            ( seq (BOOST_PP_EMPTY), \
            /* parsed fun attributes (empty sequence to start) */, \
            (0, "") /* error (code, message) */ ) \
    ))

#endif // #include guard

