
#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_NOT_EQ_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_NOT_EQ_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run the related generation script "generate.py".

#include <boost/contract/ext_/preprocessor/keyword/utility/is.hpp>
#include <boost/preprocessor/cat.hpp>

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_NOT_EQ_CAT_TO_COMMAnot_eq ,
#define not_eqBOOST_CONTRACT_EXT_PP_KEYWORD_NOT_EQ_CAT_TO_COMMA ,
// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_NOT_EQ_CAT_TO_EMPTYnot_eq
#define not_eqBOOST_CONTRACT_EXT_PP_KEYWORD_NOT_EQ_CAT_TO_EMPTY

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NOT_EQ_FRONT(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_FRONT( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_NOT_EQ_CAT_TO_COMMA, tokens)

// Precondition: tokens must end with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NOT_EQ_BACK(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_BACK( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_NOT_EQ_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `not_eq` (this can be
//               checked with `..._IS_NOT_EQ_FRONT` macro above).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_NOT_EQ_REMOVE_FRONT(tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_EXT_PP_KEYWORD_NOT_EQ_CAT_TO_EMPTY, tokens)

// Precondition: tokens must end with `not_eq` (this can be
//               checked with `..._IS_NOT_EQ_BACK` macro above).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_NOT_EQ_REMOVE_BACK(tokens) \
    BOOST_PP_CAT(tokens, BOOST_CONTRACT_EXT_PP_KEYWORD_NOT_EQ_CAT_TO_EMPTY)

#endif // #include guard

