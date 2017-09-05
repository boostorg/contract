
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_KEYWORD_XOR_HPP_
#define CONTRACT_DETAIL_PP_KEYWORD_XOR_HPP_

#include <contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define CONTRACT_DETAIL_PP_KEYWORD_XOR_IS_xor (1) /* unary */
#define xor_CONTRACT_DETAIL_PP_KEYWORD_XOR_IS (1) /* unary */
#define CONTRACT_DETAIL_PP_KEYWORD_XOR_REMOVE_xor /* nothing */
#define xor_CONTRACT_DETAIL_PP_KEYWORD_XOR_REMOVE /* nothing */

// PUBLIC //

// Is.

#define CONTRACT_DETAIL_PP_KEYWORD_IS_XOR_FRONT(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            CONTRACT_DETAIL_PP_KEYWORD_XOR_IS_)

#define CONTRACT_DETAIL_PP_KEYWORD_IS_XOR_BACK(token) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _CONTRACT_DETAIL_PP_KEYWORD_XOR_IS)

// Remove.

#define CONTRACT_DETAIL_PP_KEYWORD_XOR_REMOVE_FRONT(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_XOR_FRONT, \
            CONTRACT_DETAIL_PP_KEYWORD_XOR_REMOVE_)

#define CONTRACT_DETAIL_PP_KEYWORD_XOR_REMOVE_BACK(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_XOR_BACK, \
            _CONTRACT_DETAIL_PP_KEYWORD_XOR_REMOVE)

// Add.

#define CONTRACT_DETAIL_PP_KEYWORD_XOR_ADD_FRONT(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_XOR_FRONT, xor)

#define CONTRACT_DETAIL_PP_KEYWORD_XOR_ADD_BACK(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_XOR_BACK, xor)

#endif // #include guard

