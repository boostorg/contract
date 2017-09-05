// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_APPEND_TRAITS_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_APPEND_TRAITS_HPP_

#include "apply.hpp"
#include "returns.hpp"
#include <boost/preprocessor.hpp>

#define CONTRACT_AUX_PP_SIGN_PARSE_APPEND_TRAITS_OP_( \
        seq_sign_err, traits_to_append) \
    CONTRACT_AUX_PP_SIGN_PARSE_RETURN_OK(seq_sign_err, \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err), \
            traits_to_append)

#define CONTRACT_AUX_PP_SIGN_PARSE_APPEND_TRAITS( \
        traits_to_append, seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_APPLY( \
            CONTRACT_AUX_PP_SIGN_PARSE_APPEND_TRAITS_OP_, \
            CONTRACT_AUX_PP_SIGN_PARSE_APPEND_TRAITS_OP_, \
            seq_sign_err, traits_to_append)

#endif // #include guard

