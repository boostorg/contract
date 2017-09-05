
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_KEYWORD_PRECONDITION_HPP_
#define CONTRACT_DETAIL_PP_KEYWORD_PRECONDITION_HPP_

#include <contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define CONTRACT_DETAIL_PP_KEYWORD_PRECONDITION_IS_precondition (1) /* unary */
#define precondition_CONTRACT_DETAIL_PP_KEYWORD_PRECONDITION_IS (1) /* unary */
#define CONTRACT_DETAIL_PP_KEYWORD_PRECONDITION_REMOVE_precondition /*nothing*/
#define precondition_CONTRACT_DETAIL_PP_KEYWORD_PRECONDITION_REMOVE /*nothing*/

// PUBLIC //

// Is.

#define CONTRACT_DETAIL_PP_KEYWORD_IS_PRECONDITION_FRONT(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            CONTRACT_DETAIL_PP_KEYWORD_PRECONDITION_IS_)

#define CONTRACT_DETAIL_PP_KEYWORD_IS_PRECONDITION_BACK(token) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _CONTRACT_DETAIL_PP_KEYWORD_PRECONDITION_IS)

// Remove.

#define CONTRACT_DETAIL_PP_KEYWORD_PRECONDITION_REMOVE_FRONT(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_PRECONDITION_FRONT, \
            CONTRACT_DETAIL_PP_KEYWORD_PRECONDITION_REMOVE_)

#define CONTRACT_DETAIL_PP_KEYWORD_PRECONDITION_REMOVE_BACK(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_PRECONDITION_BACK, \
            _CONTRACT_DETAIL_PP_KEYWORD_PRECONDITION_REMOVE)

// Add.

#define CONTRACT_DETAIL_PP_KEYWORD_PRECONDITION_ADD_FRONT(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_PRECONDITION_FRONT, precondition)

#define CONTRACT_DETAIL_PP_KEYWORD_PRECONDITION_ADD_BACK(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_PRECONDITION_BACK, precondition)

#endif // #include guard

