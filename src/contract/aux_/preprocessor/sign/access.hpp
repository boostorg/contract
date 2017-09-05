// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_ACCESS_HPP_
#define CONTRACT_AUX_PP_SIGN_ACCESS_HPP_

#include "seq_.hpp"
#include "../keyword/is_private.hpp"
#include "../keyword/is_protected.hpp"
#include "../keyword/is_public.hpp"
#include <boost/preprocessor.hpp>

#define CONTRACT_AUX_PP_SIGN_ACCESS(sign) \
    BOOST_PP_SEQ_ELEM(CONTRACT_AUX_PP_SIGN_SEQ_ACCESS_INDEX, sign)

#define CONTRACT_AUX_PP_SIGN_IS_PRIVATE(sign) \
    CONTRACT_AUX_PP_KEYWORD_IS_PRIVATE_( \
            CONTRACT_AUX_PP_SIGN_ACCESS(sign))

#define CONTRACT_AUX_PP_SIGN_IS_PROTECTED(sign) \
    CONTRACT_AUX_PP_KEYWORD_IS_PROTECTED_( \
            CONTRACT_AUX_PP_SIGN_ACCESS(sign))

#define CONTRACT_AUX_PP_SIGN_IS_PUBLIC(sign) \
    CONTRACT_AUX_PP_KEYWORD_IS_PUBLIC( \
            CONTRACT_AUX_PP_SIGN_ACCESS(sign))

#endif // #include guard

