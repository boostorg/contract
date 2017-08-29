// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_RETURNS_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_RETURNS_HPP_

#include <boost/preprocessor.hpp>

#define CONTRACT_AUX_PP_SIGN_PARSE_RETURN_OK(seq_sign_err, \
        remaining_seq, append_traits) \
    ( /* return new seq_sign_err 3-tuple */ \
        /* signature still to be parsed */ \
        remaining_seq, \
        /* append new traits to existing ones (seq concatenation) */ \
        BOOST_PP_TUPLE_ELEM(3, 1, seq_sign_err) append_traits, \
        /* no error (code, message) */ \
        (0, "") \
    )

#define CONTRACT_AUX_PP_SIGN_PARSE_RETURN_ERR(seq_sign_err, \
        remaining_seq, append_traits, error_msg) \
    ( /* return new seq_sing_err 3-tuple */ \
        /* signature still to be parsed */ \
        remaining_seq, \
        /* append new traits to existing ones (seq concatenation) */ \
        BOOST_PP_TUPLE_ELEM(3, 1, seq_sign_err) append_traits, \
        /* error (code, message) */ \
        (1, error_msg) \
    )

#endif // #include guard

