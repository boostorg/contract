// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_MATCH_NOT_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_MATCH_NOT_HPP_

#include "apply.hpp"
#include "returns.hpp"
#include <boost/preprocessor.hpp>

#define CONTRACT_AUX_PP_SIGN_PARSE_MATCH_NOT_NO_( \
        seq_sign_err, match_n_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_RETURN_OK(seq_sign_err, \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err), \
            /* append nothing -- this is just a check */)

#define CONTRACT_AUX_PP_SIGN_PARSE_MATCH_NOT_OP_( \
        seq_sign_err, match_n_err) \
    /* match macro */ \
    BOOST_PP_IF(BOOST_PP_TUPLE_ELEM(2, 0, match_n_err)( \
            BOOST_PP_SEQ_HEAD(BOOST_PP_TUPLE_ELEM(3, 0, \
            seq_sign_err))), \
        CONTRACT_AUX_PP_SIGN_PARSE_RETURN_ERR(seq_sign_err, \
                BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err), \
                /* append nothing -- this is just a check */, \
                /* err msg */ \
                BOOST_PP_TUPLE_ELEM(2, 1, match_n_err)) \
    , /* else */ \
        CONTRACT_AUX_PP_SIGN_PARSE_MATCH_NOT_NO_( \
                seq_sign_err, check_macro) \
    ) /* endif */

#define CONTRACT_AUX_PP_SIGN_PARSE_MATCH_NOT( \
        match_macro, match_err, seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_APPLY( \
            CONTRACT_AUX_PP_SIGN_PARSE_MATCH_NOT_OP_, \
            CONTRACT_AUX_PP_SIGN_PARSE_MATCH_NOT_NO_, \
            seq_sign_err, (match_macro, match_err))

#endif // #include guard

