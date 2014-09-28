
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REM_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REM_HPP_

#include <boost/preprocessor/cat.hpp>

// PRIVATE //

// Adapted from BOOST_PP_EXPAND.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REMOVE_EXPAND_I_(tokens) \
    tokens
#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REM_EXPAND_(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REMOVE_EXPAND_I_(tokens)

// PUBLIC //

// `removing_prefix ## <keyword-to-remove>` must expand to nothing, else 0.
// Precondition: Tokens start with keyword to remove (see KEYWORD_UTILITY_IS).
// IMPLEMENTATION: Below without EXPAND doesn't expand on MSVC.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REM(tokens, removing_prefix) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REM_EXPAND_( \
            BOOST_PP_CAT(removing_prefix, tokens))

#endif // #include guard

