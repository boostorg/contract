// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_POSTCONDITION_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_POSTCONDITION_HPP_

#include "../../keyword/is_postcondition.hpp"
#include "../result_type.hpp"
#include "utility/block.hpp"
#include "utility/match_not.hpp"

// If not specified defaults `result` and` {}` are used. In this case
// `result` (as any other name) can be used no name the result becase
// there is no postcondition code that uses it anyway.

#define CONTRACT_AUX_PP_SIGN_PARSE_POSTCONDITION_RESULT_( \
        seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_OPTIONAL(seq_sign_err, \
            CONTRACT_AUX_PP_KEYWORD_IS_POSTCONDITION, \
            2, /* 2 blocks (result)(preconditions_code_block) */ \
            (result) ({}), /* default if not specified */ \
            CONTRACT_ERROR_missing_postcondition_code_block, \
            CONTRACT_ERROR_missing_postcondition_result_name)

#define CONTRACT_AUX_PP_SIGN_PARSE_POSTCONDITION_NORESULT_( \
        seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_OPTIONAL( \
            ( \
                BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err) \
                , BOOST_PP_TUPLE_ELEM(3, 1, seq_sign_err) \
                        /* append EMPTY for result name */ \
                        (result) /* default if not specified */ \
                , BOOST_PP_TUPLE_ELEM(3, 2, seq_sign_err) \
            ), \
            CONTRACT_AUX_PP_KEYWORD_IS_POSTCONDITION, \
            1, /* 1 block (preconditions_code_block) */ \
            ({}), /* default if not specified */ \
            CONTRACT_ERROR_missing_postcondition_code_block, \
            BOOST_PP_EMPTY)

#define CONTRACT_AUX_PP_SIGN_PARSE_POSTCONDITION(seq_sign_err) \
    BOOST_PP_IF(CONTRACT_AUX_PP_SIGN_IS_VOID_RESULT( \
            BOOST_PP_TUPLE_ELEM(3, 1, seq_sign_err)), \
        CONTRACT_AUX_PP_SIGN_PARSE_POSTCONDITION_NORESULT_ \
    , /* else */ \
        CONTRACT_AUX_PP_SIGN_PARSE_POSTCONDITION_RESULT_ \
    )(seq_sign_err)

#define CONTRACT_AUX_PP_SIGN_PARSE_NO_POSTCONDITION(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_APPEND_TRAITS( (BOOST_PP_EMPTY) ({}), \
            CONTRACT_AUX_PP_SIGN_PARSE_MATCH_NOT( \
                    CONTRACT_AUX_PP_KEYWORD_IS_POSTCONDITION, \
                    CONTRACT_ERROR_cannot_specify_postcondition_code_block, \
                    seq_sign_err))

#endif // #include guard

