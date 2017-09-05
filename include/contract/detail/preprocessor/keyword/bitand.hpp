
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_KEYWORD_BITAND_HPP_
#define CONTRACT_DETAIL_PP_KEYWORD_BITAND_HPP_

#include <contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define CONTRACT_DETAIL_PP_KEYWORD_BITAND_IS_bitand (1) /* unary */
#define bitand_CONTRACT_DETAIL_PP_KEYWORD_BITAND_IS (1) /* unary */
#define CONTRACT_DETAIL_PP_KEYWORD_BITAND_REMOVE_bitand /* nothing */
#define bitand_CONTRACT_DETAIL_PP_KEYWORD_BITAND_REMOVE /* nothing */

// PUBLIC //

// Is.

#define CONTRACT_DETAIL_PP_KEYWORD_IS_BITAND_FRONT(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            CONTRACT_DETAIL_PP_KEYWORD_BITAND_IS_)

#define CONTRACT_DETAIL_PP_KEYWORD_IS_BITAND_BACK(token) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _CONTRACT_DETAIL_PP_KEYWORD_BITAND_IS)

// Remove.

#define CONTRACT_DETAIL_PP_KEYWORD_BITAND_REMOVE_FRONT(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_BITAND_FRONT, \
            CONTRACT_DETAIL_PP_KEYWORD_BITAND_REMOVE_)

#define CONTRACT_DETAIL_PP_KEYWORD_BITAND_REMOVE_BACK(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_BITAND_BACK, \
            _CONTRACT_DETAIL_PP_KEYWORD_BITAND_REMOVE)

// Add.

#define CONTRACT_DETAIL_PP_KEYWORD_BITAND_ADD_FRONT(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_BITAND_FRONT, bitand)

#define CONTRACT_DETAIL_PP_KEYWORD_BITAND_ADD_BACK(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_BITAND_BACK, bitand)

#endif // #include guard

