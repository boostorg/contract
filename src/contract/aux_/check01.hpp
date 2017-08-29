// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_CHECK01_HPP_
#define CONTRACT_AUX_CHECK01_HPP_

// These are equivalent to CONTRACT_CHECK_XYZ macro symbols but they
// are always defined to 0 or 1 instead of being #defined or
// #undefined. They are used internally because Boost.Preprocessor
// macros do not work on #undefined symbols directly.

#if defined CONTRACT_CHECK_BLOCK_INVARIANT
#   define CONTRACT_AUX_CHECK_BLOCK_INVARIANT_01 1
#else
#   define CONTRACT_AUX_CHECK_BLOCK_INVARIANT_01 0
#endif

#if defined CONTRACT_CHECK_CLASS_INVARIANT
#   define CONTRACT_AUX_CHECK_CLASS_INVARIANT_01 1
#else
#   define CONTRACT_AUX_CHECK_CLASS_INVARIANT_01 0
#endif

#if defined CONTRACT_CHECK_PRECONDITION
#   define CONTRACT_AUX_CHECK_PRECONDITION_01 1
#else
#   define CONTRACT_AUX_CHECK_PRECONDITION_01 0
#endif

#if defined CONTRACT_CHECK_POSTCONDITION
#   define CONTRACT_AUX_CHECK_POSTCONDITION_01 1
#else
#   define CONTRACT_AUX_CHECK_POSTCONDITION_01 0
#endif

#if defined CONTRACT_CHECK_CLASS_INVARIANT || \
        defined CONTRACT_CHECK_PRECONDITION || \
        defined CONTRACT_CHECK_POSTCONDITION
#   define CONTRACT_AUX_CHECK_CLASS_01 1
#else
#   define CONTRACT_AUX_CHECK_CLASS_01 0
#endif

#endif // #include guard

