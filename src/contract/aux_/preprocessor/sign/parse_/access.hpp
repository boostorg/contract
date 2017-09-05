// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_ACCESS_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_ACCESS_HPP_

#include "utility/apply.hpp"
#include "utility/returns.hpp"
#include "../../keyword/is_private.hpp"
#include "../../keyword/is_protected.hpp"
#include "../../keyword/is_public.hpp"
#include <boost/preprocessor.hpp>

#define CONTRACT_AUX_PP_SIGN_PARSE_ACCESS_OP_( \
        seq_sign_err, data) /**/ \
    BOOST_PP_IF(CONTRACT_AUX_PP_KEYWORD_IS_PRIVATE( \
            BOOST_PP_SEQ_HEAD(BOOST_PP_TUPLE_ELEM(3, 0, \
            seq_sign_err))), \
        CONTRACT_AUX_PP_SIGN_PARSE_RETURN_OK(seq_sign_err, \
                BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 0, \
                seq_sign_err)), (private) ) \
    , BOOST_PP_IF(CONTRACT_AUX_PP_KEYWORD_IS_PROTECTED( \
            BOOST_PP_SEQ_HEAD(BOOST_PP_TUPLE_ELEM(3, 0, \
            seq_sign_err))), \
        CONTRACT_AUX_PP_SIGN_PARSE_RETURN_OK(seq_sign_err, \
                BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 0, \
                seq_sign_err)), (protected) ) \
    , BOOST_PP_IF(CONTRACT_AUX_PP_KEYWORD_IS_PUBLIC( \
            BOOST_PP_SEQ_HEAD(BOOST_PP_TUPLE_ELEM(3, 0, \
            seq_sign_err))), \
        CONTRACT_AUX_PP_SIGN_PARSE_RETURN_OK(seq_sign_err, \
                BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 0, \
                seq_sign_err)), (public) ) \
    , /* else (error) */ \
        CONTRACT_AUX_PP_SIGN_PARSE_RETURN_ERR(seq_sign_err, \
                BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 0, \
                /* no valid access given */ \
                seq_sign_err)), (BOOST_PP_EMPTY), \
                CONTRACT_ERROR_given_invalid_access_specifier_where_private_protected_or_public_expected) /* Invalid token is BOOST_PP_STRINGIZE(BOOST_PP_SEQ_HEAD(BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err))) */ \
    ))) /* end if */

#define CONTRACT_AUX_PP_SIGN_PARSE_ACCESS_ERR_( \
        seq_sign_err, data) \
    CONTRACT_AUX_PP_SIGN_PARSE_RETURN_ERR(seq_sign_err, \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err), \
            (BOOST_PP_EMPTY) /* no valid access given */, \
            CONTRACT_ERROR_missing_access_specifier_where_private_protected_or_public_expected)

#define CONTRACT_AUX_PP_SIGN_PARSE_ACCESS(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_APPLY( \
            CONTRACT_AUX_PP_SIGN_PARSE_ACCESS_OP_, \
            CONTRACT_AUX_PP_SIGN_PARSE_ACCESS_ERR_, \
            seq_sign_err, ~)

#define CONTRACT_AUX_PP_SIGN_PARSE_NO_ACCESS(seq_sign_err) \
    /* macro */ \
    BOOST_PP_IF(CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER( \
            BOOST_PP_TUPLE_ELEM(3, 1, seq_sign_err)), \
        CONTRACT_AUX_PP_SIGN_PARSE_RETURN_ERR \
    , /* else */ \
        CONTRACT_AUX_PP_SIGN_PARSE_APPEND_TRAITS \
    ) /* endif */ \
    /* params */ \
    BOOST_PP_IF(CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER( \
            BOOST_PP_TUPLE_ELEM(3, 1, seq_sign_err)), \
        ( BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err), \
            (BOOST_PP_EMPTY), \
            CONTRACT_ERROR_class_member_must_specify_private_protected_or_public_access ) \
    , /* else */ \
        ( (BOOST_PP_EMPTY), seq_sign_err ) \
    ) /* endif */

#endif // #include guar

