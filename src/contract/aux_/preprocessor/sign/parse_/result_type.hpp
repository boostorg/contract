// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_RESULT_TYPE_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_RESULT_TYPE_HPP_

#include "utility/required.hpp"
#include "utility/append_traits.hpp"
#include "utility/match_not.hpp"
#include "../../keyword/is_void.hpp"

#define CONTRACT_AUX_PP_SIGN_PARSE_RESULT_TYPE(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_REQUIRED( \
            seq_sign_err, CONTRACT_ERROR_missing_result_type)
    
#define CONTRACT_AUX_PP_SIGN_PARSE_NO_RESULT_TYPE(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_APPEND_TRAITS( (void), \
            CONTRACT_AUX_PP_SIGN_PARSE_MATCH_NOT( \
                    CONTRACT_AUX_PP_KEYWORD_IS_VOID, \
                    CONTRACT_ERROR_cannot_specify_result_type_not_even_void_within_this_context, \
                    seq_sign_err))

#endif // #include guard

