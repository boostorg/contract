// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_EXPLICIT_HPP_
#define CONTRACT_AUX_PP_SIGN_EXPLICIT_HPP_

#include "seq_.hpp"
#include <boost/preprocessor.hpp>

#define CONTRACT_AUX_PP_SIGN_EXPLICIT(sign) \
    BOOST_PP_SEQ_ELEM(CONTRACT_AUX_PP_SIGN_SEQ_EXPLICIT_INDEX, \
            sign)(/* expand empty */)

#define CONTRACT_AUX_PP_SIGN_IS_EXPLICIT(sign) \
    BOOST_PP_NOT(BOOST_PP_IS_EMPTY( \
            CONTRACT_AUX_PP_SIGN_EXPLICIT(sign)))

#endif // #include guard

