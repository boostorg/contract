// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_BASE_TYPES_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_BASE_TYPES_HPP_

#include "utility/apply.hpp"
#include "utility/returns.hpp"
#include "utility/required.hpp"
#include "utility/append_traits.hpp"
#include "../../keyword/is_inherit.hpp"
#include <boost/preprocessor.hpp>

#define CONTRACT_AUX_PP_SIGN_PARSE_BASE_TYPES_REQUIRED_( \
        d, seq_sign_err) \
    BOOST_PP_IF(BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_TAIL( \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err))), \
        /* now base must be there -- base option is now required */ \
        CONTRACT_AUX_PP_SIGN_PARSE_REQUIRED_OP \
    , /* else (no token left to parse in signature) */ \
        CONTRACT_AUX_PP_SIGN_PARSE_REQUIRED_NO \
    )( ( \
            BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 0, \
            seq_sign_err)) \
            , BOOST_PP_TUPLE_ELEM(3, 1, seq_sign_err) \
            , BOOST_PP_TUPLE_ELEM(3, 2, seq_sign_err) \
        ), \
        CONTRACT_ERROR_missing_base_class_type_for_inherit \
    ) /* endif */

#define CONTRACT_AUX_PP_SIGN_PARSE_BASE_TYPES_PRED_( \
        n, seq_sign_err) \
    CONTRACT_AUX_PP_KEYWORD_IS_INHERIT( \
            BOOST_PP_SEQ_HEAD(BOOST_PP_TUPLE_ELEM(3, 0, \
            seq_sign_err)))

#define CONTRACT_AUX_PP_SIGN_PARSE_BASE_TYPES_WHILE_(seq_sign_err) \
    BOOST_PP_WHILE(CONTRACT_AUX_PP_SIGN_PARSE_BASE_TYPES_PRED_, \
        CONTRACT_AUX_PP_SIGN_PARSE_BASE_TYPES_REQUIRED_, \
        ( \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err) \
            , (BOOST_PP_EMPTY) \
            , BOOST_PP_TUPLE_ELEM(3, 2, seq_sign_err) \
        ) )

#define CONTRACT_AUX_PP_SIGN_PARSE_BASE_TYPES_APPEND_( \
        orig_seq_sign_err, bases_seq_sign_err) \
    ( \
        /* ramining seq from parsed bases */ \
        BOOST_PP_TUPLE_ELEM(3, 0, bases_seq_sign_err) \
        /* sign is original one plus (seq concat) bases one */ \
        , BOOST_PP_TUPLE_ELEM(3, 1, orig_seq_sign_err) \
            /* seq concat with base seq */ \
            ( BOOST_PP_TUPLE_ELEM(3, 1, bases_seq_sign_err) ) \
        /* err is from parsed bases */ \
        , BOOST_PP_TUPLE_ELEM(3, 2, bases_seq_sign_err) \
    )

#define CONTRACT_AUX_PP_SIGN_PARSE_BASE_TYPES_OP_( \
        seq_sign_err, data) \
    CONTRACT_AUX_PP_SIGN_PARSE_BASE_TYPES_APPEND_(seq_sign_err, \
        CONTRACT_AUX_PP_SIGN_PARSE_BASE_TYPES_WHILE_(seq_sign_err))

#define CONTRACT_AUX_PP_SIGN_PARSE_BASE_TYPES_NO_( \
        seq_sign_err, data) \
    CONTRACT_AUX_PP_SIGN_PARSE_RETURN_OK(seq_sign_err, \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err), \
            (BOOST_PP_EMPTY) /* empty seq elem if no token */)

#define CONTRACT_AUX_PP_SIGN_PARSE_BASE_TYPES(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_APPLY( \
            CONTRACT_AUX_PP_SIGN_PARSE_BASE_TYPES_OP_, \
            CONTRACT_AUX_PP_SIGN_PARSE_BASE_TYPES_NO_, \
            seq_sign_err, ~)

#define CONTRACT_AUX_PP_SIGN_PARSE_NO_BASE_TYPES(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_APPEND_TRAITS( \
            ( (BOOST_PP_EMPTY) ), seq_sign_err)

#endif // #include guard

