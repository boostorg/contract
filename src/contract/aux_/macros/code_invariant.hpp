// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_CODE_INVARIANT_HPP_
#define CONTRACT_AUX_CODE_INVARIANT_HPP_

#include "../../config.hpp"
#include "../check01.hpp"
#include <boost/preprocessor.hpp>

#define CONTRACT_AUX_CODE_INVARIANT( \
        static_invariants_code_block, invariants_code_block) \
    /* assumes within a private section of a class */ \
    BOOST_PP_EXPR_IF(CONTRACT_AUX_CHECK_CLASS_01, \
        /* friendship needed for object access */ \
        friend class ::contract::state; \
        mutable ::contract::state CONTRACT_CONFIG_STATE_VARIABLE_; \
    ) /* endif check any */ \
    BOOST_PP_EXPR_IF(CONTRACT_AUX_CHECK_CLASS_INVARIANT_01, \
        static void CONTRACT_CONFIG_STATIC_INVARIANT_FUNCTION_() \
            static_invariants_code_block \
        void CONTRACT_CONFIG_INVARIANT_FUNCTION_() const \
            invariants_code_block \
    ) /* endif check invariants */

#endif // #include guard

