// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_COPYABLE_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_COPYABLE_HPP_

#include "apply.hpp"
#include "required.hpp"
#include "optional.hpp"
#include "../../../keyword/is_copyable.hpp"
#include "../../../seq.hpp"
#include <boost/preprocessor.hpp>

#define CONTRACT_AUX_PP_SIGN_PARSE_COPYABLE_OP_( \
        seq_sign_err, data) \
    ( BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err) \
    , CONTRACT_AUX_PP_SEQ_REST_N_TO_TUPLE_( \
            2, BOOST_PP_TUPLE_ELEM(3, 1, seq_sign_err)) \
    , BOOST_PP_TUPLE_ELEM(3, 2, seq_sign_err))
    
#define CONTRACT_AUX_PP_SIGN_PARSE_COPYABLE( \
        seq_sign_err, missing_token_error) \
    CONTRACT_AUX_PP_SIGN_PARSE_APPLY( \
            CONTRACT_AUX_PP_SIGN_PARSE_COPYABLE_OP_, \
            CONTRACT_AUX_PP_SIGN_PARSE_COPYABLE_OP_, \
            CONTRACT_AUX_PP_SIGN_PARSE_REQUIRED( \
                    CONTRACT_AUX_PP_SIGN_PARSE_OPTIONAL( \
                            seq_sign_err, \
                            CONTRACT_AUX_PP_KEYWORD_IS_COPYABLE), \
                    missing_token_error), \
            ~)

#endif // #include guard

