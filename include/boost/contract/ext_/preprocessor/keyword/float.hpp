
#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_FLOAT_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_FLOAT_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run related generation script "keyword-generate.py".

#include <boost/contract/ext_/preprocessor/keyword/utility/is.hpp>
#include <boost/contract/ext_/preprocessor/keyword/utility/remove.hpp>

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_FLOAT_FRONT(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_FRONT( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_FLOAT_CAT_TO_COMMA, tokens)

// Precondition: tokens must end with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_FLOAT_BACK(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_BACK( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_FLOAT_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `float` (this can be
//               checked with `..._IS_FLOAT_FRONT` macro above).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_FLOAT_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REMOVE_FRONT( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_FLOAT_CAT_TO_EMPTY, tokens)

// Precondition: tokens must end with `float` (this can be
//               checked with `..._IS_FLOAT_BACK` macro above).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_FLOAT_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REMOVE_BACK( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_FLOAT_CAT_TO_EMPTY, tokens)

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_FLOAT_CAT_TO_COMMAfloat ,
#define floatBOOST_CONTRACT_EXT_PP_KEYWORD_FLOAT_CAT_TO_COMMA ,

// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_FLOAT_CAT_TO_EMPTYfloat
#define floatBOOST_CONTRACT_EXT_PP_KEYWORD_FLOAT_CAT_TO_EMPTY

#endif // #include guard

