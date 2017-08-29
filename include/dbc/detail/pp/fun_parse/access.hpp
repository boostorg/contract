/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_PP_FUN_PARSE_ACCESS_HPP_
#define DBC_PP_FUN_PARSE_ACCESS_HPP_

#include "../keywords.hpp"
#include "util/apply.hpp"
#include "util/returns.hpp"
#include <boost/preprocessor.hpp>

#define DBC_PP_FUN_PARSE_ACCESS_OP_(sign_traits_err, data) /**/ \
    BOOST_PP_IF(DBC_PP_IS_PRIVATE_(BOOST_PP_SEQ_HEAD( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err))), \
        DBC_PP_FUN_PARSE_RETURN_OK_(sign_traits_err, \
                BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)),\
                (private) ) \
    , BOOST_PP_IF(DBC_PP_IS_PROTECTED_(BOOST_PP_SEQ_HEAD( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err))), \
        DBC_PP_FUN_PARSE_RETURN_OK_(sign_traits_err, \
                BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)),\
                (protected) ) \
    , BOOST_PP_IF(DBC_PP_IS_PUBLIC_(BOOST_PP_SEQ_HEAD( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err))), \
        DBC_PP_FUN_PARSE_RETURN_OK_(sign_traits_err, \
                BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)),\
                (public) ) \
    , /* else (error) */ \
        DBC_PP_FUN_PARSE_RETURN_ERR_(sign_traits_err, \
                BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)),\
                (BOOST_PP_EMPTY) /* no valid access given */, \
                /* The invalid token is BOOST_PP_STRINGIZE(BOOST_PP_SEQ_HEAD(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err))) */ \
                DBC_ERROR_given_invalid_access_specifier_where_private_protected_or_public_expected_) \
    ))) /* endif */ \
    /**/

#define DBC_PP_FUN_PARSE_ACCESS_NO_(sign_traits_err, data) \
    DBC_PP_FUN_PARSE_RETURN_ERR_(sign_traits_err, \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err), \
            (BOOST_PP_EMPTY) /* no valid access given */, \
            DBC_ERROR_missing_access_specifier_where_private_protected_or_public_expected_)

#define DBC_PP_FUN_PARSE_ACCESS_(sign_traits_err) \
    DBC_PP_FUN_PARSE_APPLY_(DBC_PP_FUN_PARSE_ACCESS_OP_, \
            DBC_PP_FUN_PARSE_ACCESS_NO_, sign_traits_err, ~)

#endif // DBC_PP_FUN_PARSE_ACCESS_HPP_

