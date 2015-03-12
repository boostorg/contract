
#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_HPP_

#include <boost/contract/ext_/preprocessor/paren/has.hpp>
#include <boost/contract/ext_/preprocessor/utility/empty.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/variadic/size.hpp>

// NOTE: These macros could also check that tokens are not empty (not just that
// they do not have parenthesis) before checking the tokens match the keyword.
// However, the extra check for emptiness was measured to significantly slow
// down preprocessing (because the keyword macros are intensively used by this
// library). Furthermore, while it is essentially necessary to check that
// tokens do not have parenthesis (because this library declaration traits'
// syntax is essentially a mix of keywords and parenthesis), the emptiness
// check is not always needed. Therefore, it is left up to the users of the
// keyword macros to explicitly check tokes for emptiness when that is required.

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

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_FRONT_PAREN_( \
        cat_to_comma_prefix, tokens) \

#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_CHECK_(a, b) \
    BOOST_PP_CAT(BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_, \
            BOOST_PP_VARIADIC_SIZE(BOOST_PP_CAT(a, b)))

#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_1 0
#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_2 1

#endif // #include guard

