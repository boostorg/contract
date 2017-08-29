// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_BLOCK_HPP_
#define CONTRACT_BLOCK_HPP_

#include "old.hpp"
#include "assert.hpp"
#include <limits>

// Block Invariant //

// Block invarinats apply to any code block (same of Eiffel's check).
    
#ifdef CONTRACT_CHECK_BLOCK_INVARIANT
#define CONTRACT_ASSERT_BLOCK_INVARIANT_MSG(boolean_condition, \
        string_description) \
    try { \
        CONTRACT_AUX_DEBUG(dbg << "Checking block invariant '" \
                << string_description << "'"); \
        CONTRACT_ASSERT_MSG(boolean_condition, string_description) \
    } catch (...) { \
        ::contract::block_invariant_failed(::contract::FROM_BLOCK); \
    }
#else // check block invariants
#   define CONTRACT_ASSERT_BLOCK_INVARIANT_MSG(boolean_condition, \
        string_description) /* expand to nothing */
#endif // check block invariants

#define CONTRACT_ASSERT_BLOCK_INVARIANT(boolean_condition) \
    /* Do not use BOOST_PP_STRINGIZE() so condition NOT expanded */ \
    CONTRACT_ASSERT_BLOCK_INVARIANT_MSG(boolean_condition, \
            # boolean_condition)

// Loop Variant //

// Loops are blocks that are iterated so block invariants are used as
// loop invariants and also to check loop variants.

#ifdef CONTRACT_CHECK_BLOCK_INVARIANT
#define CONTRACT_INIT_LOOP_VARIANT \
    ::contract::loop_variant_type \
            CONTRACT_OLDOF(CONTRACT_CONFIG_VARIANT_VARIABLE_) = \
            std::numeric_limits< ::contract::loop_variant_type \
            >::quiet_NaN() \
            /* must NOT terminate with `;` to use it in for() loop */
#else // check block invariants
#define CONTRACT_INIT_LOOP_VARIANT /* expand to nothing */
#endif // check block invariants
        
#ifdef CONTRACT_CHECK_BLOCK_INVARIANT
#define CONTRACT_ASSERT_LOOP_VARIANT_MSG(integer_expression, \
        string_description) \
    ::contract::loop_variant_type \
            /* extra `()` to force variant expression evaluation */ \
            CONTRACT_CONFIG_VARIANT_VARIABLE_ = (integer_expression); \
    CONTRACT_ASSERT_BLOCK_INVARIANT_MSG( /* variant >= 0 */ \
            CONTRACT_CONFIG_VARIANT_VARIABLE_ >= 0, \
            string_description " >= 0" ); \
    CONTRACT_ASSERT_BLOCK_INVARIANT_MSG( /* variant < old variant */ \
            /* NaN used to skip variant check at entry */ \
            (CONTRACT_OLDOF(CONTRACT_CONFIG_VARIANT_VARIABLE_) == \
                    std::numeric_limits< \
                    ::contract::loop_variant_type >::quiet_NaN()) \
            || (CONTRACT_CONFIG_VARIANT_VARIABLE_ < CONTRACT_OLDOF( \
                    CONTRACT_CONFIG_VARIANT_VARIABLE_)), \
            string_description " < oldof " string_description ); \
    CONTRACT_OLDOF(CONTRACT_CONFIG_VARIANT_VARIABLE_) = \
            CONTRACT_CONFIG_VARIANT_VARIABLE_;
#else // check block invariants
#define CONTRACT_ASSERT_LOOP_VARIANT_MSG(integer_expression, \
        string_description) /* expand to nothing */
#endif // check block invariants

#define CONTRACT_ASSERT_LOOP_VARIANT(integer_expression) \
    /* Do not use BOOST_PP_STRINGIZE() so condition NOT expanded */ \
    CONTRACT_ASSERT_LOOP_VARIANT_MSG(integer_expression, \
            # integer_expression)

namespace contract {

// Do not used `unsigned` here bacause C++ implicitly converts singed
// to unsgined integers (instead, assert variant >= 0).
typedef long loop_variant_type;

} // namespace

#endif // #include guard

