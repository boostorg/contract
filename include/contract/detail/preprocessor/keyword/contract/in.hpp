
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_KEYWORD_IN_HPP_
#define CONTRACT_DETAIL_PP_KEYWORD_IN_HPP_

#include <contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define CONTRACT_DETAIL_PP_KEYWORD_IN_IS_in (1) /* unary */
#define in_CONTRACT_DETAIL_PP_KEYWORD_IN_IS (1) /* unary */
#define CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE_in /* nothing */
#define in_CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE /* nothing */

// PUBLIC //

// Is.

#define CONTRACT_DETAIL_PP_KEYWORD_IS_IN_FRONT(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            CONTRACT_DETAIL_PP_KEYWORD_IN_IS_)

#define CONTRACT_DETAIL_PP_KEYWORD_IS_IN_BACK(token) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _CONTRACT_DETAIL_PP_KEYWORD_IN_IS)

// Remove.

#define CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE_FRONT(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_IN_FRONT, \
            CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE_)

#define CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE_BACK(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_IN_BACK, \
            _CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE)

// Add.

#define CONTRACT_DETAIL_PP_KEYWORD_IN_ADD_FRONT(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_IN_FRONT, in)

#define CONTRACT_DETAIL_PP_KEYWORD_IN_ADD_BACK(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_IN_BACK, in)

#endif // #include guard

