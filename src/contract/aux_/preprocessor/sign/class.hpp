// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_CLASS_HPP_
#define CONTRACT_AUX_PP_SIGN_CLASS_HPP_

#include "seq_.hpp"
#include <boost/preprocessor.hpp>

// Class, or struct, or empty if not specified.
#define CONTRACT_AUX_PP_SIGN_CLASS_OR_STRUCT_(sign) \
    BOOST_PP_SEQ_ELEM(CONTRACT_AUX_PP_SIGN_SEQ_CLASS_INDEX, sign) \
            (/* expand empty */)

// True if either class or struct, false if empty.
#define CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER(sign) \
    BOOST_PP_NOT(BOOST_PP_IS_EMPTY( \
            CONTRACT_AUX_PP_SIGN_CLASS_OR_STRUCT_(sign)))

// Always class or empty (never struct).
#define CONTRACT_AUX_PP_SIGN_CLASS(sign) \
    BOOST_PP_EXPR_IF(CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER(sign), \
            class)

// Alwasy struct or empty (never class).
#define CONTRACT_AUX_PP_SIGN_STRUCT(sign) \
    BOOST_PP_EXPR_IF(CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER(sign), \
            struct)

#endif // #include guard

