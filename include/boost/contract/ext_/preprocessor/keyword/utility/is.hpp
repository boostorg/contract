
#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_HPP_

#include <boost/contract/ext_/preprocessor/paren/has.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/variadic/size.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_1 0
#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_2 1
        
#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_CHECK_(a, b) \
    BOOST_PP_CAT(BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_, \
            BOOST_PP_VARIADIC_SIZE(BOOST_PP_CAT(a, b)))

/* PUBLIC */

// Precondition: A macro named `cat_to_comma_prefix ## token-to-check` must be
//               #defined to expand to `,`.
// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis (i.e.,
//               leading parenthesis are allowed).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_FRONT( \
        cat_to_comma_prefix, tokens) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(tokens), \
        0 BOOST_PP_TUPLE_EAT(2) \
    , \
        BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_CHECK_ \
    )(cat_to_comma_prefix, tokens)

// Precondition: A macro named `token-to-check ## cat_to_comma_postfix` must be
//               #defined to expand to `,`.
// Precondition: tokens must end with a token concatenable to a macro name
//               (e.g., a literal or integral token) and trailing parenthesis
//               are NOT allowed.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_BACK( \
        cat_to_comma_postfix, tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_CHECK_( \
            tokens, cat_to_comma_postfix)

#endif // #include guard

