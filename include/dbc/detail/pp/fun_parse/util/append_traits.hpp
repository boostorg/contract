/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_PP_FUN_PARSE_APPEND_TRAITS_HPP_
#define DBC_PP_FUN_PARSE_APPEND_TRAITS_HPP_

#include "apply.hpp"
#include "returns.hpp"
#include <boost/preprocessor.hpp>

#define DBC_PP_FUN_PARSE_APPEND_TRAITS_OP_(sign_traits_err, traits_to_append) \
    DBC_PP_FUN_PARSE_RETURN_OK_(sign_traits_err, \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err), \
            traits_to_append)

#define DBC_PP_FUN_PARSE_APPEND_TRAITS_(traits_to_append, sign_traits_err) \
    DBC_PP_FUN_PARSE_APPLY_(DBC_PP_FUN_PARSE_APPEND_TRAITS_OP_, \
            DBC_PP_FUN_PARSE_APPEND_TRAITS_OP_, sign_traits_err, \
            traits_to_append)

#endif // DBC_PP_FUN_PARSE_APPEND_TRAITS_HPP_

