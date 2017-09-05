// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_CLASS_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_CLASS_HPP_

#include "utility/optional.hpp"
#include "../../keyword/is_class.hpp"

#define CONTRACT_AUX_PP_SIGN_PARSE_CLASS(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_OPTIONAL( \
            seq_sign_err, CONTRACT_AUX_PP_KEYWORD_IS_CLASS)

#endif // #include guard

