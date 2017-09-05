// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_HPP_

#include "next.hpp"
#include "returns.hpp"
#include <boost/preprocessor.hpp>

#define CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_CODE_ERR_(seq_sign_err, \
        missing_token_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_RETURN_ERR(seq_sign_err, \
        BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err), \
        (BOOST_PP_EMPTY), \
        missing_token_err)
        
#define CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_CODE_OK_(seq_sign_err, \
        missing_token_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_RETURN_OK(seq_sign_err, \
        BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 0, \
                seq_sign_err)), \
        ( BOOST_PP_SEQ_HEAD(BOOST_PP_TUPLE_ELEM( \
                3, 0, seq_sign_err)) ) )

#define CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_CODE_OP_(seq_sign_err, \
        missing_token_err) \
    /* size: == 0 error, == 1 only trailing (EMPTY), >= 2 for pre */ \
    BOOST_PP_IF(BOOST_PP_LESS(BOOST_PP_SEQ_SIZE( \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err)), 2), \
        CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_CODE_ERR_ \
    , \
        CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_CODE_OK_ \
    )(seq_sign_err, missing_token_err)

#define CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_CODE_(seq_sign_err, \
        missing_token_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_APPLY( \
            CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_CODE_OP_, \
            /* BLOCK_CODE_OP_ can handle EMPTY, so used also here */ \
            CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_CODE_OP_, \
            seq_sign_err, missing_token_err)

#define CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_1(seq_sign_err, \
        empty_seq, missing_token_err2, missing_token_err1) \
    /* 1st code block -- e.g., (precondition_code_block) */ \
    CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_CODE_( \
            /* skip (precondition) */ \
            CONTRACT_AUX_PP_SIGN_PARSE_NEXT_SKIP(seq_sign_err), \
            missing_token_err2)

#define CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_2(seq_sign_err, \
        empty_seq, missing_token_err2, missing_token_err1) \
    /* 2nd code block -- e.g., (postcondition_code_block) */ \
    CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_CODE_( \
    /* 1st code block -- e.g., (result) */ \
    CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_CODE_( \
            /* skip tag -- e.g., (precondition) */ \
            CONTRACT_AUX_PP_SIGN_PARSE_NEXT_SKIP(seq_sign_err), \
            missing_token_err1), \
            missing_token_err2)

#define CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_NONE_OK_(seq_sign_err, \
        empty_seq, missing_token_err2, missing_token_err1) \
    CONTRACT_AUX_PP_SIGN_PARSE_RETURN_OK(seq_sign_err, \
        BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err), \
        empty_seq /* empty code block(s) */ )

#define CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_NONE_ERR_(seq_sign_err, \
        empty_seq, missing_token_err2, missing_token_err1) \
    CONTRACT_AUX_PP_SIGN_PARSE_RETURN_ERR(seq_sign_err, \
        BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err), \
        (BOOST_PP_EMPTY), \
        missing_token_err2)

#define CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_( \
        seq_sign_err, check_macro, required, number_of_blocks, \
        empty_seq, missing_token_err2, missing_token_err1) \
    BOOST_PP_IF(BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_TUPLE_ELEM( \
            3, 2, seq_sign_err)), \
        /* error, just pass error up*/ \
        seq_sign_err \
        BOOST_PP_TUPLE_EAT(4) \
    , BOOST_PP_IF(CONTRACT_AUX_PP_SIGN_PARSE_NEXT_IS_NOT( \
            seq_sign_err, check_macro), \
        BOOST_PP_IF(required, \
            CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_NONE_ERR_ \
        , /* else */ \
            CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_NONE_OK_ \
        ) /* endif */ \
    , /* else */ \
        BOOST_PP_CAT(CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_, \
                number_of_blocks) \
    )) /* endif */ \
    (seq_sign_err, empty_seq, missing_token_err2, missing_token_err1)

// number_of_blocks can be 1 or 2 -- e.g., 2 for postcondition w/
// results. error 2 specified before 1 always because last block is
// most significative.

// Optional but required after (tag) is specified.
#define CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_OPTIONAL( \
        seq_sign_err, check_macro, number_of_blocks, \
        empty_seq, missing_token_err2, missing_token_err1) \
    CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_(seq_sign_err, check_macro, \
            0 /* optional */, number_of_blocks, empty_seq, \
            missing_token_err2, missing_token_err1)

// Tag and block must always be present.
#define CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_REQUIRED( \
        seq_sign_err, check_macro, number_of_blocks, \
        missing_token_err2, missing_token_err1) \
    CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_(seq_sign_err, check_macro, \
            1 /* required */, number_of_blocks, ( BOOST_PP_EMPTY ), \
            missing_token_err2, missing_token_err1)

#endif // #include guard

