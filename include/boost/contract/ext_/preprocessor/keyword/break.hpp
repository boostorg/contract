
#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_BREAK_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_BREAK_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run the related generation script "generate.py".

#include <boost/contract/ext_/preprocessor/keyword/utility/is.hpp>
#include <boost/contract/ext_/preprocessor/keyword/utility/remove.hpp>

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_BREAK_CAT_TO_COMMAbreak ,
#define breakBOOST_CONTRACT_EXT_PP_KEYWORD_BREAK_CAT_TO_COMMA ,

// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_BREAK_CAT_TO_EMPTYbreak
#define breakBOOST_CONTRACT_EXT_PP_KEYWORD_BREAK_CAT_TO_EMPTY

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_BREAK_FRONT(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_FRONT( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_BREAK_CAT_TO_COMMA, tokens)

// Precondition: tokens must end with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_BREAK_BACK(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_BACK( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_BREAK_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `break` (this can be
//               checked with `..._IS_BREAK_FRONT` macro above).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_BREAK_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REMOVE_FRONT( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_BREAK_CAT_TO_EMPTY, tokens)

// Precondition: tokens must end with `break` (this can be
//               checked with `..._IS_BREAK_BACK` macro above).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_BREAK_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REMOVE_BACK( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_BREAK_CAT_TO_EMPTY, tokens)

#endif // #include guard

