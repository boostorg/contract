// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_FUNCTION_NAME_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_FUNCTION_NAME_HPP_

#include "utility/required.hpp"

#define CONTRACT_AUX_PP_SIGN_PARSE_FUNCTION_NAME(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_REQUIRED( \
            seq_sign_err, CONTRACT_ERROR_missing_function_name)
    
#endif // #include guard

