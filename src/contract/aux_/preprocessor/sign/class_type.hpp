// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_CLASS_TYPE_HPP_
#define CONTRACT_AUX_PP_SIGN_CLASS_TYPE_HPP_

#include "seq_.hpp"
#include <boost/preprocessor.hpp>

#define CONTRACT_AUX_PP_SIGN_CLASS_TYPE(sign) \
    BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PP_SEQ_ELEM( \
            CONTRACT_AUX_PP_SIGN_SEQ_CLASS_TYPE_INDEX, sign))

#define CONTRACT_AUX_PP_SIGN_CLASS_TYPE_IS_COPYABLE(sign) \
    BOOST_PP_NOT(BOOST_PP_IS_EMPTY( \
            BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_SEQ_ELEM( \
            CONTRACT_AUX_PP_SIGN_SEQ_CLASS_TYPE_INDEX, sign) \
            (/* expand empty */) )))

#endif // #include guard

