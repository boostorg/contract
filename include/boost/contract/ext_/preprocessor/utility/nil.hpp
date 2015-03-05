
#ifndef BOOST_CONTRACT_EXT_PP_NIL_HPP_
#define BOOST_CONTRACT_EXT_PP_NIL_HPP_

#include <boost/contract/ext_/preprocessor/keyword/utility/is.hpp>
#include <boost/contract/ext_/preprocessor/keyword/utility/remove.hpp>

/* PUBLIC */

// This macro name must NOT be #defined (used here like a "keyword"). The
// Boost.Preprocessor doc indicates the purpose of BOOST_PP_NIL is to NOT be
// a macro (i.e., to be #undefined, according with its usage here).
#ifdef BOOST_PP_NIL
#   error "reserved macro name must not be #defined"
#endif

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_FRONT( \
            BOOST_CONTRACT_EXT_PP_NIL_CAT_TO_COMMA, tokens)

// Precondition: tokens must end with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_IS_NIL_BACK(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_BACK( \
            BOOST_CONTRACT_EXT_PP_NIL_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `BOOST_PP_NIL` (this can be
//               checked with `..._IS_NIL_FRONT` macro above).
#define BOOST_CONTRACT_EXT_PP_NIL_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REMOVE_FRONT( \
            BOOST_CONTRACT_EXT_PP_NIL_CAT_TO_EMPTY, tokens)

// Precondition: tokens must end with `BOOST_PP_NIL` (this can be
//               checked with `..._IS_NIL_BACK` macro above).
#define BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REMOVE_BACK( \
            BOOST_CONTRACT_EXT_PP_NIL_CAT_TO_EMPTY, tokens)

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_NIL_CAT_TO_COMMABOOST_PP_NIL ,
#define BOOST_PP_NILBOOST_CONTRACT_EXT_PP_NIL_CAT_TO_COMMA ,
// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_NIL_CAT_TO_EMPTYBOOST_PP_NIL
#define BOOST_PP_NILBOOST_CONTRACT_EXT_PP_NIL_CAT_TO_EMPTY

#endif // #include guard

