
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_BLOCK_INVARIANT_HPP_
#define CONTRACT_AUX_BLOCK_INVARIANT_HPP_

#include <contract/aux_/call/globals.hpp>
#include <contract/aux_/macro/code_/assert.hpp>
#include <contract/detail/preprocessor/traits/assertion.hpp>

// PRIVATE //

#define CONTRACT_AUX_BLOCK_INVARIANT_ASSERTION_FUNC_CALL_( \
        d, id, tpl, unused, a) \
    ERROR_requires_not_allowed_for_block_invariant_assertions \
    (); /* fake function call will generate compiler-error */

#define CONTRACT_AUX_BLOCK_INVARIANT_(id, tpl, assertion_seq) \
    try { \
        ::contract::aux::call_globals<>::is_checking_contract = true; \
        /* following assertion throw contract::broken on failure */ \
        CONTRACT_AUX_CODE_ASSERT(id, tpl, block_invariant, \
                CONTRACT_AUX_BLOCK_INVARIANT_ASSERTION_FUNC_CALL_, ~, \
                CONTRACT_DETAIL_PP_ASSERTION_TRAITS( \
                CONTRACT_DETAIL_PP_SEQ_TO_LIST_NEVER_EMPTY(assertion_seq))) \
        ::contract::aux::call_globals<>::is_checking_contract = false; \
    } catch(...) { \
        ::contract::aux::call_globals<>::is_checking_contract = false; \
        ::contract::block_invariant_broken(::contract::FROM_BODY); \
    }

// PUBLIC //

#define CONTRACT_AUX_BLOCK_INVARIANT(id, tpl, assertion_seq) \
    BOOST_PP_IIF(CONTRACT_AUX_CONFIG_BLOCK_INVARIANTS_01, \
        CONTRACT_AUX_BLOCK_INVARIANT_ \
    , \
        BOOST_PP_TUPLE_EAT(3) \
    )(id, tpl, assertion_seq)

#endif // #include guard

