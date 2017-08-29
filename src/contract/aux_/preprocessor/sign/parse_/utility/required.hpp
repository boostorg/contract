// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_REQUIRED_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_REQUIRED_HPP_

#include "apply.hpp"
#include "returns.hpp"
#include <boost/preprocessor.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>

#define CONTRACT_AUX_PP_SIGN_PARSE_REQUIRED_OPTION_( \
        seq_sign_err, missing_token_err, is_option) \
    BOOST_PP_IF(BOOST_PP_IS_EMPTY(BOOST_PP_SEQ_HEAD( \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err))), \
        CONTRACT_AUX_PP_SIGN_PARSE_RETURN_ERR( \
                seq_sign_err, BOOST_PP_SEQ_TAIL( \
                BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err)), \
                (BOOST_PP_EMPTY), /* error, return empty seq */ \
                missing_token_err) \
    , BOOST_PP_IF(is_option, \
        CONTRACT_AUX_PP_SIGN_PARSE_RETURN_OK( \
                seq_sign_err, BOOST_PP_SEQ_TAIL( \
                BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err)), \
                ( BOOST_PP_SEQ_HEAD( \
                  BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err)) \
                  /* if option, seq elem must have EMPTY postfix */ \
                  BOOST_PP_EMPTY ) ) \
    , /* else */ \
        CONTRACT_AUX_PP_SIGN_PARSE_RETURN_OK( \
                seq_sign_err, BOOST_PP_SEQ_TAIL( \
                BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err)), \
                ( BOOST_PP_SEQ_HEAD( \
                  BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err)) \
                  /* if not an option, no empty postfix */ \
                  ) ) \
    )) /* endif */

// These OP and NO macros are used outside this file (so they are
// part of the API).

#define CONTRACT_AUX_PP_SIGN_PARSE_REQUIRED_OPTION_OP( \
        seq_sign_err, missing_token_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_REQUIRED_OPTION_( \
            seq_sign_err, missing_token_err, 1)

#define CONTRACT_AUX_PP_SIGN_PARSE_REQUIRED_OP( \
        seq_sign_err, missing_token_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_REQUIRED_OPTION_( \
            seq_sign_err, missing_token_err, 0)

#define CONTRACT_AUX_PP_SIGN_PARSE_REQUIRED_NO( \
        seq_sign_err, missing_token_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_RETURN_ERR(seq_sign_err, \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err), \
            (BOOST_PP_EMPTY) /* error, return empty seq */, \
            missing_token_err) \

#define CONTRACT_AUX_PP_SIGN_PARSE_REQUIRED( \
        seq_sign_err, missing_token_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_APPLY( \
            CONTRACT_AUX_PP_SIGN_PARSE_REQUIRED_OP, \
            CONTRACT_AUX_PP_SIGN_PARSE_REQUIRED_NO, \
            seq_sign_err, missing_token_err)

#endif // #include guard

