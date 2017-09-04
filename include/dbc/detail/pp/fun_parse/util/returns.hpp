/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_PP_FUN_PARSE_RETURNS_HPP_
#define DBC_PP_FUN_PARSE_RETURNS_HPP_

#include <boost/preprocessor.hpp>

#define DBC_PP_FUN_PARSE_RETURN_OK_(sign_traits_err, \
        remaining_sign, append_traits) \
    ( /* return new sing_traits_err 3-tuple */ \
        /* signature still to be parsed */ \
        remaining_sign, \
        /* append specified new attrs to existing ones (seq concatenation) */ \
        BOOST_PP_TUPLE_ELEM(3, 1, sign_traits_err) append_traits, \
        /* no error (code, message) */ \
        (0, "") \
    )

#define DBC_PP_FUN_PARSE_RETURN_ERR_(sign_traits_err, \
        remaining_sign, append_traits, error_msg) \
    ( /* return new sing_traits_err 3-tuple */ \
        /* signature still to be parsed */ \
        remaining_sign, \
        /* append specified new attrs to existing ones (seq concatenation) */ \
        BOOST_PP_TUPLE_ELEM(3, 1, sign_traits_err) append_traits, \
        /* error (code, message) */ \
        (1, error_msg) \
    )

#endif // DBC_PP_FUN_PARSE_RETURNS_HPP_

