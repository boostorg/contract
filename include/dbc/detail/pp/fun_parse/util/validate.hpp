/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_PP_FUN_PARSE_VALIDATE_HPP_
#define DBC_PP_FUN_PARSE_VALIDATE_HPP_

#include "returns.hpp"
#include <boost/preprocessor.hpp>

#define DBC_PP_FUN_PARSE_VALIDATE_(valid_traits_size, sign_traits_err) /**/ \
    BOOST_PP_IF(BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_TUPLE_ELEM( \
            3, 2, sign_traits_err)), \
        sign_traits_err /* already an error, just return it */ \
    , BOOST_PP_IF(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            3, 0, sign_traits_err)), \
        DBC_PP_FUN_PARSE_RETURN_ERR_(sign_traits_err, \
            BOOST_PP_EMPTY(), /* empty signature */ \
            BOOST_PP_EMPTY(), /* don't append any traits */ \
            DBC_ERROR_extra_tokens_in_function_signature_ /* remaining tokens are BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)) */) \
    , BOOST_PP_IF(BOOST_PP_NOT_EQUAL(valid_traits_size, BOOST_PP_SEQ_SIZE( \
            BOOST_PP_TUPLE_ELEM(3, 1, sign_traits_err))), \
        DBC_PP_FUN_PARSE_RETURN_ERR_(sign_traits_err, \
            BOOST_PP_EMPTY(), /* empty signature */ \
            BOOST_PP_EMPTY(), /* don't append any traits */ \
            /* maybe this only happens on internal error... I'm not sure */ \
            DBC_ERROR_wrong_number_of_traits_after_parsing_function_signature_ /* BOOST_PP_STRINGIZE(valid_traits_size) when BOOST_PP_STRINGIZE(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(3, 1, sign_traits_err))) found */) \
    , /* else (it's valid, no error) */ \
        sign_traits_err \
    ))) \
    /**/

#endif // DBC_PP_FUN_PARSE_VALIDATE_HPP_

