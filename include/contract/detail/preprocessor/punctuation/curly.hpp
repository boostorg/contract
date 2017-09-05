
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_CURLY_HPP_
#define CONTRACT_DETAIL_PP_CURLY_HPP_

#include <contract/detail/preprocessor/keyword/facilities/is.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_IS_CURLY_CONTRACT_DETAIL_PP_LCURLY (1) /* unary */
#define CONTRACT_DETAIL_PP_IS_CURLY_CONTRACT_DETAIL_PP_RCURLY (1) /* unary */

// PUBLIC //

// Curly parenthesis macros.

#define CONTRACT_DETAIL_PP_LCURLY() {

#define CONTRACT_DETAIL_PP_RCURLY() }

// Detect curly parenthesis macros (not curly paren but actual macro names).

#define CONTRACT_DETAIL_PP_IS_LCURLY_MACRO(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            CONTRACT_DETAIL_PP_IS_CURLY_)

#define CONTRACT_DETAIL_PP_IS_RCURLY_MACRO(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            CONTRACT_DETAIL_PP_IS_CURLY_)

#endif // #include guard

