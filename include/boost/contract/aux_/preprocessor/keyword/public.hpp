
#ifndef BOOST_CONTRACT_AUX_PP_KEYWORD_PUBLIC_HPP_
#define BOOST_CONTRACT_AUX_PP_KEYWORD_PUBLIC_HPP_

#include <boost/contract/aux_/preprocessor/keyword/utility/is.hpp>
/** @cond */
#include <boost/preprocessor/cat.hpp>
/** @endcond */

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token).
#define BOOST_CONTRACT_AUX_PP_KEYWORD_IS_PUBLIC(tokens) \
    BOOST_CONTRACT_AUX_PP_KEYWORD_UTILITY_IS( \
            BOOST_CONTRACT_AUX_PP_KEYWORD_PUBLIC_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `public` (this can be
//               checked with `..._IS_PUBLIC` macro above).
#define BOOST_CONTRACT_AUX_PP_KEYWORD_REMOVE_PUBLIC(tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_AUX_PP_KEYWORD_PUBLIC_CAT_TO_EMPTY, tokens)

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_AUX_PP_KEYWORD_PUBLIC_CAT_TO_COMMApublic ,
// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_AUX_PP_KEYWORD_PUBLIC_CAT_TO_EMPTYpublic

#endif // #include guard

