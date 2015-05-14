
#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_HPP_

/** @cond */
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/variadic/size.hpp>
/** @endcond */

/* PUBLIC */

// Precondition: A macro named `cat_to_comma_prefix ## token-to-check` must be
//               #defined to expand to `,`.
// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token).
#define BOOST_CONTRACT_AUX_PP_KEYWORD_UTILITY_IS(cat_to_comma_prefix, tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_AUX_PP_KEYWORD_UTILITY_IS_, \
            BOOST_PP_VARIADIC_SIZE(BOOST_PP_CAT(cat_to_comma_prefix, tokens)))

/* PRIVATE */

#define BOOST_CONTRACT_AUX_PP_KEYWORD_UTILITY_IS_1 0
#define BOOST_CONTRACT_AUX_PP_KEYWORD_UTILITY_IS_2 1

#endif // #include guard

