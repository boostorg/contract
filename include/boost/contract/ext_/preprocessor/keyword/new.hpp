
#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_NEW_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_NEW_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run related generation script "keyword-generate.py".

#include <boost/contract/ext_/preprocessor/keyword/utility/is.hpp>
#include <boost/contract/ext_/preprocessor/keyword/utility/remove.hpp>

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_NEW_CAT_TO_COMMAnew ,
#define newBOOST_CONTRACT_EXT_PP_KEYWORD_NEW_CAT_TO_COMMA ,

// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_NEW_CAT_TO_EMPTYnew
#define newBOOST_CONTRACT_EXT_PP_KEYWORD_NEW_CAT_TO_EMPTY

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NEW_FRONT(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_FRONT( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_NEW_CAT_TO_COMMA, tokens)

// Precondition: tokens must end with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NEW_BACK(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_BACK( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_NEW_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `new` (this can be
//               checked with `..._IS_NEW_FRONT` macro above).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_NEW_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REMOVE_FRONT( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_NEW_CAT_TO_EMPTY, tokens)

// Precondition: tokens must end with `new` (this can be
//               checked with `..._IS_NEW_BACK` macro above).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_NEW_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REMOVE_BACK( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_NEW_CAT_TO_EMPTY, tokens)

#endif // #include guard

