// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_BASE_TYPE_HPP_
#define CONTRACT_AUX_PP_SIGN_BASE_TYPE_HPP_

#include "seq_.hpp"
#include <boost/preprocessor.hpp>

// bases := ( (BOOST_PP_EMPTY) (base0) (base1) ... )

#define CONTRACT_AUX_PP_SIGN_HAS_BASES(sign) \
    /* size > 1 because 1st elem (EMPTY) always there */ \
    BOOST_PP_GREATER(BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_ELEM( \
            CONTRACT_AUX_PP_SIGN_SEQ_BASE_TYPES_INDEX, sign)), 1)

#define CONTRACT_AUX_PP_SIGN_BASE_TYPES(sign) \
    BOOST_PP_IF(CONTRACT_AUX_PP_SIGN_HAS_BASES(sign), \
        BOOST_PP_SEQ_TAIL /* skip leading (EMPTY) */ \
    , \
        BOOST_PP_TUPLE_EAT(1) /* return nothing */ \
    )(BOOST_PP_SEQ_ELEM( \
            CONTRACT_AUX_PP_SIGN_SEQ_BASE_TYPES_INDEX, sign))

#endif // #include guard

