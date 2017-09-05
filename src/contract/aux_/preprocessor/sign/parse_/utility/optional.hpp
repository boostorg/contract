// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_OPTIONAL_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_OPTIONAL_HPP_

#include "apply.hpp"
#include "returns.hpp"
#include <boost/preprocessor.hpp>

#define CONTRACT_AUX_PP_SIGN_PARSE_OPTIONAL_NO_( \
        seq_sign_err, check_macro) \
    CONTRACT_AUX_PP_SIGN_PARSE_RETURN_OK(seq_sign_err, \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err), \
            (BOOST_PP_EMPTY) /* empty seq elem if no token */)

#define CONTRACT_AUX_PP_SIGN_PARSE_OPTIONAL_OP_( \
        seq_sign_err, check_macro) \
    BOOST_PP_IF(check_macro(BOOST_PP_SEQ_HEAD( \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err))), \
        CONTRACT_AUX_PP_SIGN_PARSE_RETURN_OK(seq_sign_err, \
                BOOST_PP_SEQ_TAIL( \
                        BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err)), \
                ( BOOST_PP_SEQ_HEAD( \
                        BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err)) \
                BOOST_PP_EMPTY ) \
                ) \
    , /* else */ \
        CONTRACT_AUX_PP_SIGN_PARSE_RETURN_OK(seq_sign_err, \
                BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err), \
                (BOOST_PP_EMPTY) /* empty se elem if no macth */) \
    ) /* endif */

#define CONTRACT_AUX_PP_SIGN_PARSE_OPTIONAL( \
        seq_sign_err, check_macro) \
    CONTRACT_AUX_PP_SIGN_PARSE_APPLY( \
            CONTRACT_AUX_PP_SIGN_PARSE_OPTIONAL_OP_, \
            CONTRACT_AUX_PP_SIGN_PARSE_OPTIONAL_NO_, \
            seq_sign_err, check_macro)

#endif // #include guard

