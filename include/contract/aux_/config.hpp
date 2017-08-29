
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CONFIG_HPP_
#define CONTRACT_AUX_CONFIG_HPP_

#include <contract/config.hpp>
#include <boost/config.hpp>

// Internal option to enable debug prints to `clog` (programmers should never
// need to access this).
#ifdef CONTRACT_AUX_CONFIG_DEBUG
#   define CONTRACT_AUX_CONFIG_DEBUG_01 1
#else
#   define CONTRACT_AUX_CONFIG_DEBUG_01 0
#endif

// Internal option to change named parameter tag namespace (programmers
// should never need to access this).
#ifndef CONTRACT_AUX_CONFIG_NAMED_PARAMETER_TAG_NAMESPACE_DEFAULT
#   define CONTRACT_AUX_CONFIG_NAMED_PARAMETER_TAG_NAMESPACE_DEFAULT \
        CONTRACT_AUX_SYMBOL( (params) )
#endif

#ifdef CONTRACT_CONFIG_THREAD_SAFE
#   define CONTRACT_AUX_CONFIG_THREAD_SAFE_01 1
#else
#   define CONTRACT_AUX_CONFIG_THREAD_SAFE_01 0
#endif

#ifdef CONTRACT_CONFIG_NO_PRECONDITIONS
#   define CONTRACT_AUX_CONFIG_PRECONDITIONS_01 0
#else
#   define CONTRACT_AUX_CONFIG_PRECONDITIONS_01 1
#endif

#ifdef CONTRACT_CONFIG_NO_POSTCONDITIONS
#   define CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 0
#else
#   define CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 1
#endif

#ifdef CONTRACT_CONFIG_NO_CLASS_INVARIANTS
#   define CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 0
#else
#   define CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 1
#endif

#ifdef CONTRACT_CONFIG_NO_BLOCK_INVARIANTS
#   define CONTRACT_AUX_CONFIG_BLOCK_INVARIANTS_01 0
#else
#   define CONTRACT_AUX_CONFIG_BLOCK_INVARIANTS_01 1
#endif

#ifdef CONTRACT_CONFIG_NO_LOOP_VARIANTS
#   define CONTRACT_AUX_CONFIG_LOOP_VARIANTS_01 0
#else
#   define CONTRACT_AUX_CONFIG_LOOP_VARIANTS_01 1
#endif

#ifdef CONTRACT_CONFIG_DO_NOT_OVERRIDE_PRECONDITIONS
#   define CONTRACT_AUX_CONFIG_PRECONDITION_OVERRIDE_01 0
#else
#   define CONTRACT_AUX_CONFIG_PRECONDITION_OVERRIDE_01 1
#endif

#ifdef CONTRACT_CONFIG_REPORT_OVERRIDDEN_PRECONDITION_FAILURE
#   define CONTRACT_AUX_CONFIG_REPORT_OVERRIDDEN_PRECONDITION_FAILURE_01 1
#else
#   define CONTRACT_AUX_CONFIG_REPORT_OVERRIDDEN_PRECONDITION_FAILURE_01 0
#endif

#ifdef CONTRACT_CONFIG_PRECONDITIONS_DISABLE_NO_ASSERTION
#   define CONTRACT_AUX_CONFIG_PRECONDITIONS_DISABLE_NO_ASSERTION_01 1
#else
#   define CONTRACT_AUX_CONFIG_PRECONDITIONS_DISABLE_NO_ASSERTION_01 0
#endif

#endif // #include guard

