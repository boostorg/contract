// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PRECONDITION_HPP_
#define CONTRACT_AUX_PP_SIGN_PRECONDITION_HPP_

#include "seq_.hpp"
#include <boost/preprocessor.hpp>

#define CONTRACT_AUX_PP_SIGN_PRECONDITION(sign) \
    BOOST_PP_SEQ_ELEM(CONTRACT_AUX_PP_SIGN_SEQ_PRECONDITION_INDEX, \
            sign)

#endif // #include guard

