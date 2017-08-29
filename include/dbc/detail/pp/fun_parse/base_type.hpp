/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_PP_FUN_PARSE_BASE_TYPE_HPP_
#define DBC_PP_FUN_PARSE_BASE_TYPE_HPP_

#include "../keywords.hpp"
#include "util/apply.hpp"
#include "util/returns.hpp"
#include "util/required.hpp"
#include <boost/preprocessor.hpp>

#define DBC_PP_FUN_PARSE_BASE_TYPE_NO_(sign_traits_err, data) \
    DBC_PP_FUN_PARSE_RETURN_OK_(sign_traits_err, \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err), \
            (/* empty seq elem if no token */))

#define DBC_PP_FUN_PARSE_BASE_TYPE_REQUIRED_(sign_traits_err, data) \
    BOOST_PP_IF(BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_TAIL( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err))), \
        DBC_PP_FUN_PARSE_REQUIRED_OP_ \
    , /* else (no token left to parse in signature) */ \
        DBC_PP_FUN_PARSE_REQUIRED_NO_ \
    )( ( \
            BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)) \
            , BOOST_PP_TUPLE_ELEM(3, 1, sign_traits_err) \
            , BOOST_PP_TUPLE_ELEM(3, 2, sign_traits_err) \
        ), \
        DBC_ERROR_missing_base_class_type_in_DBC_BASE_specifier_ \
    ) /* endif */ \

#define DBC_PP_FUN_PARSE_BASE_TYPE_OP_(sign_traits_err, data) \
    BOOST_PP_IF(DBC_PP_IS_BASE_(BOOST_PP_SEQ_HEAD( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err))), \
        DBC_PP_FUN_PARSE_BASE_TYPE_REQUIRED_ \
    , /* else (no DBC_BASE() specifier found */ \
        DBC_PP_FUN_PARSE_BASE_TYPE_NO_ \
    )(sign_traits_err, data) /* endif */

#define DBC_PP_FUN_PARSE_BASE_TYPE_(sign_traits_err) \
    DBC_PP_FUN_PARSE_APPLY_(DBC_PP_FUN_PARSE_BASE_TYPE_OP_, \
            DBC_PP_FUN_PARSE_BASE_TYPE_NO_, sign_traits_err, ~)

#endif // DBC_PP_FUN_PARSE_BASE_TYPE_HPP_

