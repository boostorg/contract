
#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_ALIGNAS_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_ALIGNAS_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run the related generation script "generate.py".

#include <boost/contract/ext_/preprocessor/keyword/utility/is.hpp>
#include <boost/contract/ext_/preprocessor/keyword/utility/remove.hpp>

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_ALIGNAS_CAT_TO_COMMAalignas ,
#define alignasBOOST_CONTRACT_EXT_PP_KEYWORD_ALIGNAS_CAT_TO_COMMA ,

// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_ALIGNAS_CAT_TO_EMPTYalignas
#define alignasBOOST_CONTRACT_EXT_PP_KEYWORD_ALIGNAS_CAT_TO_EMPTY

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ALIGNAS_FRONT(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_FRONT( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ALIGNAS_CAT_TO_COMMA, tokens)

// Precondition: tokens must end with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ALIGNAS_BACK(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_BACK( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ALIGNAS_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `alignas` (this can be
//               checked with `..._IS_ALIGNAS_FRONT` macro above).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_ALIGNAS_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REMOVE_FRONT( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ALIGNAS_CAT_TO_EMPTY, tokens)

// Precondition: tokens must end with `alignas` (this can be
//               checked with `..._IS_ALIGNAS_BACK` macro above).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_ALIGNAS_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REMOVE_BACK( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ALIGNAS_CAT_TO_EMPTY, tokens)

#endif // #include guard

