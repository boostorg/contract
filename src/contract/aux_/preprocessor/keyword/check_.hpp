// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_KEYWORD_CHECK_HPP_
#define CONTRACT_AUX_PP_KEYWORD_CHECK_HPP_

// IMPORTANT: The contents of this file are implementation specific
// and they should NOT be used from files outside the ones in this
// directory.

#include <boost/preprocessor.hpp>

// From the Boost mailing list, P. Mensonides (author of
// Boost.Preprocessor) mentioned that BOOST_PP_IS_UNARY is in
// "detail/" because it does not work with older versions of the
// Borland C++ compiler. Technically, this is part of the private API
// of Boost.Preprocessor (and it should not be used) but also
// P. Mensonides suggests to use this macro if its functionality were
// needed (as the macro is defined to be work on different compilers
// as much as possible) keeping in mind that it might not work on 
// some compilers, like older Borland, that do not fully implement 
// the C++ preprocessor ISO standard. This library uses this macro.
#include <boost/preprocessor/detail/is_unary.hpp>

// Expand to true iff keyword_prefix ## token is #defined, e.g.:
//  #define K_VOID_void (1) // Can be 1 or any non-empty token.
//  #define IS_VOID(tok) CONTRACT_AUX_PP_KEYWORD_CHECK(K_VOID_, tok)
//  IS_VOID(void) // Expand to 1.
//  IS_VOID(abcd) // Expand to 0.
#define CONTRACT_AUX_PP_KEYWORD_CHECK(keyword_prefix, token) \
    BOOST_PP_IS_UNARY(BOOST_PP_CAT(keyword_prefix, token))

#endif // #include guard

