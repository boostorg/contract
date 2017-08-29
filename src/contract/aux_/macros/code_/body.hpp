// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_CODE_BODY_HPP_
#define CONTRACT_AUX_CODE_BODY_HPP_

#include "function_sign.hpp"
#include <boost/preprocessor.hpp>
    
#define CONTRACT_AUX_CODE_BODY_SIGN(kind, sign) \
    CONTRACT_AUX_CODE_FUNCTION_SIGN(kind, 0, /* no force inline */ \
            CONTRACT_BODY( \
                    CONTRACT_AUX_CODE_FUNCTION_NAME(kind, sign)), \
            sign)

#define CONTRACT_AUX_CODE_BODY(kind, sign) \
    CONTRACT_AUX_CODE_BODY_SIGN(kind, sign) /* signature */ \
    CONTRACT_AUX_PP_SIGN_BODY(sign) /* code block */

#endif // #include guard

