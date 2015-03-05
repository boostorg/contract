
#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run related generation script "keyword-generate.py".

#include <boost/contract/ext_/preprocessor/keyword/utility/is.hpp>
#include <boost/contract/ext_/preprocessor/keyword/utility/remove.hpp>

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_SWITCH_FRONT(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_FRONT( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_CAT_TO_COMMA, tokens)

// Precondition: tokens must end with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_SWITCH_BACK(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_BACK( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `switch` (this can be
//               checked with `..._IS_SWITCH_FRONT` macro above).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REMOVE_FRONT( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_CAT_TO_EMPTY, tokens)

// Precondition: tokens must end with `switch` (this can be
//               checked with `..._IS_SWITCH_BACK` macro above).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REMOVE_BACK( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_CAT_TO_EMPTY, tokens)

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_CAT_TO_COMMAswitch ,
#define switchBOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_CAT_TO_COMMA ,

// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_CAT_TO_EMPTYswitch
#define switchBOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_CAT_TO_EMPTY

#endif // #include guard

