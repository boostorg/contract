// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_FUNCTION_TEMPLATE_ARGS_HPP_
#define CONTRACT_AUX_PP_SIGN_FUNCTION_TEMPLATE_ARGS_HPP_

#include "arg.hpp" // #included here for caller to inspect single arg.
#include "seq_.hpp"
#include <boost/preprocessor.hpp>

// You should get the args iff HAS_ARGS is true (otherwise you'll get
// a seq with 1 tuple with all empty 
// ( (BOOST_PP_EMPTY, BOOST_PP_EMPTY, BOOST_PP_EMPTY) ) for no args).

#define CONTRACT_AUX_PP_SIGN_FUNCTION_TEMPLATE_ARGS(sign) \
    BOOST_PP_SEQ_ELEM( \
            CONTRACT_AUX_PP_SIGN_SEQ_FUNCTION_TEMPLATE_ARGS_INDEX, \
            sign)

#define CONTRACT_AUX_PP_SIGN_HAS_FUNCTION_TEMPLATE_ARGS(f) \
    BOOST_PP_NOT(BOOST_PP_IS_EMPTY(BOOST_PP_TUPLE_ELEM(3, 2, \
            BOOST_PP_SEQ_HEAD( \
            CONTRACT_AUX_PP_SIGN_FUNCTION_TEMPLATE_ARGS(f))) \
            (/* exapnd emtpy */) ))

// Expand in arg that can be inspected using macros in "arg.hpp".
#define CONTRACT_AUX_PP_SIGN_FUNCTION_TEMPLATE_ARG(n, sign) \
    BOOST_PP_SEQ_ELEM(n, \
            CONTRACT_AUX_PP_SIGN_FUNCTION_TEMPLATE_ARGS(sign))

#endif // #include guard

