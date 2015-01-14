
#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_XOR_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_XOR_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run related generation script "keyword-generate.py".

#include <boost/contract/ext_/preprocessor/keyword/utility/is.hpp>
#include <boost/contract/ext_/preprocessor/keyword/utility/remove.hpp>

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_XOR_CAT_TO_COMMAxor ,
#define xorBOOST_CONTRACT_EXT_PP_KEYWORD_XOR_CAT_TO_COMMA ,

// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_XOR_CAT_TO_EMPTYxor
#define xorBOOST_CONTRACT_EXT_PP_KEYWORD_XOR_CAT_TO_EMPTY

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_XOR_FRONT(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_FRONT( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_XOR_CAT_TO_COMMA, tokens)

// Precondition: tokens must end with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_XOR_BACK(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_BACK( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_XOR_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `xor` (this can be
//               checked with `..._IS_XOR_FRONT` macro above).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_XOR_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REMOVE_FRONT( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_XOR_CAT_TO_EMPTY, tokens)

// Precondition: tokens must end with `xor` (this can be
//               checked with `..._IS_XOR_BACK` macro above).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_XOR_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REMOVE_BACK( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_XOR_CAT_TO_EMPTY, tokens)

#endif // #include guard

