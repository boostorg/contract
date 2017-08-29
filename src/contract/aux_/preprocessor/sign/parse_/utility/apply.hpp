// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_APPLY_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_APPLY_HPP_

#include <boost/preprocessor.hpp>

// Can't use BOOST_PP_IDENTITY() because trails with BOOST_PP_EMPTY.
#define CONTRACT_AUX_PP_SIGN_PARSE_APPLY_IDENTITY_( \
        seq_sign_err, data) \
    seq_sign_err

// Token seq ends with (BOOST_PP_EMPTY) because C++ Standard does not
// allow empty seq "()" (some compilers are able to handle "()" but 
// not all). The ending (BOOST_PP_EMPTY) is ignored.
#define CONTRACT_AUX_PP_SIGN_PARSE_APPLY(parse_macro, \
        parse_empty_macro, seq_sign_err, data) \
    BOOST_PP_IF(BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_TUPLE_ELEM( \
            3, 2, seq_sign_err)), \
        /* error, just pass error up*/ \
        CONTRACT_AUX_PP_SIGN_PARSE_APPLY_IDENTITY_ \
    , BOOST_PP_IF(BOOST_PP_GREATER(BOOST_PP_SEQ_SIZE( \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err)), 1), \
        parse_macro /* more tokens left, continue parsing */ \
    , /* else */ \
        parse_empty_macro /* only (BOOST_PP_EMPTY) left, done */ \
    ))(seq_sign_err, data)

// Quietly pass trough if cannot apply because seq is empty.
#define CONTRACT_AUX_PP_SIGN_PARSE_APPLY_QUIET( \
        parse_macro, seq_sign_err, data) \
    CONTRACT_AUX_PP_SIGN_PARSE_APPLY(parse_macro, \
            /* do nothing if cannot apply because seq empty */ \
            CONTRACT_AUX_PP_SIGN_PARSE_APPLY_IDENTITY_, \
            seq_sign_err, data)

#endif // #include guard

