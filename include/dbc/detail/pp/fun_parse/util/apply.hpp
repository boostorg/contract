/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_PP_FUN_PARSE_APPLY_HPP_
#define DBC_PP_FUN_PARSE_APPLY_HPP_

#include <boost/preprocessor.hpp>

// Can't use BOOST_PP_IDENTITY() because it trails with BOOST_PP_EMPTY...
#define DBC_PP_FUN_PARSE_APPLY_IDENTITY_(sign_traits_err, data) sign_traits_err

// Token seq ends with (BOOST_PP_EMPTY) because std does not allow empty seq
// "()" (some compilers are able to handle "()" but not all). The ending
// (BOOST_PP_EMPTY) is ignored.
#define DBC_PP_FUN_PARSE_APPLY_(parse_macro, parse_empty_macro, \
        sign_traits_err, data) \
    BOOST_PP_IF(BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_TUPLE_ELEM( \
            3, 2, sign_traits_err)), \
        DBC_PP_FUN_PARSE_APPLY_IDENTITY_ /* error, just pass error up*/ \
    , BOOST_PP_IF(BOOST_PP_GREATER(BOOST_PP_SEQ_SIZE( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)), 1), \
        parse_macro /* more tokens left, continue parsing */ \
    , /* else */ \
        parse_empty_macro /* only (BOOST_PP_EMPTY) left, done */ \
    ))(sign_traits_err, data)

#endif // DBC_PP_FUN_PARSE_APPLY_HPP_

