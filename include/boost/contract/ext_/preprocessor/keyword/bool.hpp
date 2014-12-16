
#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_BOOL_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_BOOL_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run the related generation script "generate.py".

#include <boost/contract/ext_/preprocessor/keyword/utility/is.hpp>
#include <boost/preprocessor/cat.hpp>

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_BOOL_CAT_TO_COMMAbool ,
#define boolBOOST_CONTRACT_EXT_PP_KEYWORD_BOOL_CAT_TO_COMMA ,
// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_BOOL_CAT_TO_EMPTYbool
#define boolBOOST_CONTRACT_EXT_PP_KEYWORD_BOOL_CAT_TO_EMPTY

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_BOOL_FRONT(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_FRONT( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_BOOL_CAT_TO_COMMA, tokens)

// Precondition: tokens must end with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_BOOL_BACK(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_BACK( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_BOOL_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `bool` (this can be
//               checked with `..._IS_BOOL_FRONT` macro above).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_BOOL_REMOVE_FRONT(tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_EXT_PP_KEYWORD_BOOL_CAT_TO_EMPTY, tokens)

// Precondition: tokens must end with `bool` (this can be
//               checked with `..._IS_BOOL_BACK` macro above).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_BOOL_REMOVE_BACK(tokens) \
    BOOST_PP_CAT(tokens, BOOST_CONTRACT_EXT_PP_KEYWORD_BOOL_CAT_TO_EMPTY)

#endif // #include guard

