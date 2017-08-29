/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_PP_FUN_PARSE_MATCH_NOT_HPP_
#define DBC_PP_FUN_PARSE_MATCH_NOT_HPP_

#include "apply.hpp"
#include "returns.hpp"
#include <boost/preprocessor.hpp>

#define DBC_PP_FUN_PARSE_MATCH_NOT_NO_(sign_traits_err, match_n_err) \
    DBC_PP_FUN_PARSE_RETURN_OK_(sign_traits_err, \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err), \
            /* append nothing -- this is just a check */)

#define DBC_PP_FUN_PARSE_MATCH_NOT_OP_(sign_traits_err, match_n_err) \
    BOOST_PP_IF(BOOST_PP_TUPLE_ELEM(2, 0, match_n_err)/* macth macro */( \
            BOOST_PP_SEQ_HEAD(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err))), \
        DBC_PP_FUN_PARSE_RETURN_ERR_(sign_traits_err, \
                BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err), \
                /* append nothing -- this is just a check */, \
                BOOST_PP_TUPLE_ELEM(2, 1, match_n_err) /* err msg */) \
    , /* else */ \
        DBC_PP_FUN_PARSE_MATCH_NOT_NO_(sign_traits_err, check_macro) \
    ) /* endif */

#define DBC_PP_FUN_PARSE_MATCH_NOT_(match_macro, match_err, sign_traits_err) \
    DBC_PP_FUN_PARSE_APPLY_(DBC_PP_FUN_PARSE_MATCH_NOT_OP_, \
            DBC_PP_FUN_PARSE_MATCH_NOT_NO_, sign_traits_err, \
            (match_macro, match_err))

#endif // DBC_PP_FUN_PARSE_MATCH_NOT_HPP_

