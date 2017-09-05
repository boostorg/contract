// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_BODY_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_BODY_HPP_

#include "../../keyword/is_body.hpp"
#include "utility/block.hpp"

#define CONTRACT_AUX_PP_SIGN_PARSE_BODY(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_BLOCK_REQUIRED(seq_sign_err, \
            CONTRACT_AUX_PP_KEYWORD_IS_BODY, \
            1, /* just one block (body_code_block) */ \
            CONTRACT_ERROR_missing_body_code_block, \
            BOOST_PP_EMPTY /* no other block error */ )

#endif // #include guard

