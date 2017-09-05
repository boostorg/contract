// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_POSTCONDITION_HPP_
#define CONTRACT_AUX_PP_SIGN_POSTCONDITION_HPP_

#include "seq_.hpp"
#include <boost/preprocessor.hpp>

#define CONTRACT_AUX_PP_SIGN_POSTCONDITION(sign) \
    BOOST_PP_SEQ_ELEM(CONTRACT_AUX_PP_SIGN_SEQ_POSTCONDITION_INDEX, \
            sign)

#define CONTRACT_AUX_PP_SIGN_POSTCONDITION_RESULT(sign) \
    BOOST_PP_SEQ_ELEM( \
            CONTRACT_AUX_PP_SIGN_SEQ_POSTCONDITION_RESULT_INDEX, \
            sign)

#endif // #include guard

