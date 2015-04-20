
#ifndef BOOST_CONTRACT_AUX_PP_KEYWORD_PROTECTED_HPP_
#define BOOST_CONTRACT_AUX_PP_KEYWORD_PROTECTED_HPP_

#include <boost/contract/aux_/preprocessor/keyword/utility/is.hpp>
#include <boost/preprocessor/cat.hpp>

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token).
#define BOOST_CONTRACT_AUX_PP_KEYWORD_IS_PROTECTED(tokens) \
    BOOST_CONTRACT_AUX_PP_KEYWORD_UTILITY_IS( \
            BOOST_CONTRACT_AUX_PP_KEYWORD_PROTECTED_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `protected` (this can be
//               checked with `..._IS_PROTECTED` macro above).
#define BOOST_CONTRACT_AUX_PP_KEYWORD_REMOVE_PROTECTED(tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_AUX_PP_KEYWORD_PROTECTED_CAT_TO_EMPTY, tokens)

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_AUX_PP_KEYWORD_PROTECTED_CAT_TO_COMMAprotected ,
// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_AUX_PP_KEYWORD_PROTECTED_CAT_TO_EMPTYprotected

#endif // #include guard

