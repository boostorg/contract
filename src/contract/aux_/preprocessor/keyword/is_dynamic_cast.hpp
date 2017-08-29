// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_KEYWORD_IS_DYNAMIC_CAST_HPP_
#define CONTRACT_AUX_PP_KEYWORD_IS_DYNAMIC_CAST_HPP_

#include "check_.hpp"

// Do NOT #undef this macro (mixed capital because postfix must match
// keyword, but not a local macro). The 1 can be any non-empty token.
#define CONTRACT_AUX_PP_KEYWORD_DYNAMIC_CAST_dynamic_cast (1)

#define CONTRACT_AUX_PP_KEYWORD_IS_DYNAMIC_CAST(token) \
    CONTRACT_AUX_PP_KEYWORD_CHECK( \
            CONTRACT_AUX_PP_KEYWORD_DYNAMIC_CAST_, token)

#endif // #include guard

