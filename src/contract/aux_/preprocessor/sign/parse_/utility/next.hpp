// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_NEXT_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_NEXT_HPP_

#include "optional.hpp"
#include "../../../seq.hpp"
#include <boost/preprocessor.hpp>

#define CONTRACT_AUX_PP_SIGN_PARSE_NEXT_IS_NOT( \
        seq_sign_err, check_macro) \
    BOOST_PP_IS_EMPTY(CONTRACT_AUX_PP_SEQ_BACK( \
            BOOST_PP_TUPLE_ELEM(3, 1, \
            CONTRACT_AUX_PP_SIGN_PARSE_OPTIONAL( \
                    seq_sign_err, check_macro))) \
    (/* expand empty */))

#define CONTRACT_AUX_PP_SIGN_PARSE_NEXT_SKIP(seq_sign_err) \
    ( \
        BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 0, \
                seq_sign_err)) \
        , BOOST_PP_TUPLE_ELEM(3, 1, seq_sign_err) \
        , BOOST_PP_TUPLE_ELEM(3, 2, seq_sign_err) \
    )

#endif // #include guard

