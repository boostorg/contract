// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_FUNCTION_NAME_HPP_
#define CONTRACT_AUX_PP_SIGN_FUNCTION_NAME_HPP_

#include "seq_.hpp"
#include "../keyword/is_operator.hpp"
#include <boost/preprocessor.hpp>

// Handle special name `( operator (symbol, word) )` for operators.
// These are NOT local macros -- do NOT #undef them! Mixed case
// names are necesseray because they must be prefixed by "operator".

#define CONTRACT_AUX_PP_SIGN_FUNCTION_NAME_OP_WORD_operator( \
        symbol, word) \
    /* use ## instead of PP_CAT here for proper macro expansion */ \
    operator_ ## word /* e.g., operator_equal */

#define CONTRACT_AUX_PP_SIGN_FUNCTION_NAME_OP_SYMBOL_operator( \
        symbol, word) \
    operator symbol /* e.g., operator== */

#define CONTRACT_AUX_PP_SIGN_FUNCTION_NAME_WORD(name) \
    BOOST_PP_IF(CONTRACT_AUX_PP_KEYWORD_IS_OPERATOR(name), \
        /* CONTRACT_AUX_PP_SIGN_FUNCTION_NAME_OP_WORD_operator() */ \
        BOOST_PP_CAT(CONTRACT_AUX_PP_SIGN_FUNCTION_NAME_OP_WORD_, \
                name) \
    , /* else */ \
        name \
    ) /* endif */

#define CONTRACT_AUX_PP_SIGN_FUNCTION_NAME_SYMBOLIC(name) \
    BOOST_PP_IF(CONTRACT_AUX_PP_KEYWORD_IS_OPERATOR(name), \
        /* CONTRACT_AUX_PP_SIGN_FUNCTION_NAME_OP_SYMBOL_operator() */ \
        BOOST_PP_CAT(CONTRACT_AUX_PP_SIGN_FUNCTION_NAME_OP_SYMBOL_, \
                name) \
    , /* else */ \
        name \
    ) /* endif */

#define CONTRACT_AUX_PP_SIGN_FUNCTION_NAME(sign) \
    CONTRACT_AUX_PP_SIGN_FUNCTION_NAME_WORD(BOOST_PP_SEQ_ELEM( \
            CONTRACT_AUX_PP_SIGN_SEQ_FUNCTION_NAME_INDEX, sign))

#define CONTRACT_AUX_PP_SIGN_FUNCTION_NAME_SYMBOL(sign) \
    CONTRACT_AUX_PP_SIGN_FUNCTION_NAME_SYMBOLIC(BOOST_PP_SEQ_ELEM( \
            CONTRACT_AUX_PP_SIGN_SEQ_FUNCTION_NAME_INDEX, sign))

#endif // #include guard

