// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_PRECONDITION_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_PRECONDITION_HPP_

#include "../../keyword/is_precondition.hpp"
#include "utility/match_not.hpp"
#include "utility/block.hpp"

#define CONTRACT_AUX_PP_SIGN_PARSE_PRECONDITION(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_OPTIONAL(seq_sign_err, \
            CONTRACT_AUX_PP_KEYWORD_IS_PRECONDITION, \
            1, /* just one block (preconditions_code_block) */ \
            ( {} ), /* default if not specified */ \
            CONTRACT_ERROR_missing_precondition_code_block, \
            BOOST_PP_EMPTY /* no other block error */ )

#define CONTRACT_AUX_PP_SIGN_PARSE_NO_PRECONDITION(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_APPEND_TRAITS( ({}), \
            CONTRACT_AUX_PP_SIGN_PARSE_MATCH_NOT( \
                    CONTRACT_AUX_PP_KEYWORD_IS_PRECONDITION, \
                    CONTRACT_ERROR_cannot_specify_precondition_code_block, \
                    seq_sign_err))

#endif // #include guard

