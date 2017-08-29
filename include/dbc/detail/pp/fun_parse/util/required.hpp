/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_PP_FUN_PARSE_REQUIRED_HPP_
#define DBC_PP_FUN_PARSE_REQUIRED_HPP_

#include "../../seq.hpp"
#include "apply.hpp"
#include "returns.hpp"
#include <boost/preprocessor.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>

#define DBC_PP_FUN_PARSE_REQUIRED_OPTION_(sign_traits_err, \
        missing_token_err, is_option) \
    BOOST_PP_IF(BOOST_PP_IS_EMPTY(BOOST_PP_SEQ_HEAD( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err))), \
        DBC_PP_FUN_PARSE_RETURN_ERR_(sign_traits_err, BOOST_PP_SEQ_TAIL( \
                BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)), \
                (BOOST_PP_EMPTY), /* error, return empty seq */ \
                missing_token_err) \
    , BOOST_PP_IF(is_option, \
        DBC_PP_FUN_PARSE_RETURN_OK_(sign_traits_err, BOOST_PP_SEQ_TAIL( \
                BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)), \
                ( BOOST_PP_SEQ_HEAD( \
                  BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)) \
                  /* if option, seq elem must have EMPTY postfix */ \
                  BOOST_PP_EMPTY ) ) \
    , /* else */ \
        DBC_PP_FUN_PARSE_RETURN_OK_(sign_traits_err, BOOST_PP_SEQ_TAIL( \
                BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)), \
                ( BOOST_PP_SEQ_HEAD( \
                  BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)) \
                  /* if not an option, no empty postfix */ \
                  ) ) \
    )) /* endif */

#define DBC_PP_FUN_PARSE_REQUIRED_OPTION_OP_(sign_traits_err, \
        missing_token_err) \
    DBC_PP_FUN_PARSE_REQUIRED_OPTION_( \
            sign_traits_err, missing_token_err, 1)

#define DBC_PP_FUN_PARSE_REQUIRED_OP_(sign_traits_err, missing_token_err) \
    DBC_PP_FUN_PARSE_REQUIRED_OPTION_( \
            sign_traits_err, missing_token_err, 0)

#define DBC_PP_FUN_PARSE_REQUIRED_NO_(sign_traits_err, missing_token_err) \
    DBC_PP_FUN_PARSE_RETURN_ERR_(sign_traits_err, \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err), \
            (BOOST_PP_EMPTY) /* error, return empty seq */, \
            missing_token_err) \

#define DBC_PP_FUN_PARSE_REQUIRED_(sign_traits_err, missing_token_err) \
    DBC_PP_FUN_PARSE_APPLY_(DBC_PP_FUN_PARSE_REQUIRED_OP_, \
            DBC_PP_FUN_PARSE_REQUIRED_NO_, sign_traits_err, \
            missing_token_err)

#endif // DBC_PP_FUN_PARSE_REQUIRED_HPP_

