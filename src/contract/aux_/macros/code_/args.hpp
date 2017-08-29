// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_CODE_ARGS_HPP_
#define CONTRACT_AUX_CODE_ARGS_HPP_

#include "../../preprocessor/sign/args.hpp"
#include <boost/preprocessor.hpp>

#define CONTRACT_AUX_CODE_ARG_NAME_OP_(z, n, arg) \
    CONTRACT_AUX_PP_SIGN_ARG_NAME(arg)

#define CONTRACT_AUX_CODE_ARG_NAMES(sign) \
    CONTRACT_AUX_PP_SIGN_ARG_ENUM(sign, \
            CONTRACT_AUX_PP_SIGN_HAS_ARGS, \
            CONTRACT_AUX_PP_SIGN_ARGS, \
            CONTRACT_AUX_CODE_ARG_NAME_OP_)

#define CONTRACT_AUX_CODE_ARG_NAMES_TRAILING(sign) \
    CONTRACT_AUX_PP_SIGN_ARG_ENUM_TRAILING(sign, \
            CONTRACT_AUX_PP_SIGN_HAS_ARGS, \
            CONTRACT_AUX_PP_SIGN_ARGS, \
            CONTRACT_AUX_CODE_ARG_NAME_OP_)

#endif // #include guard

