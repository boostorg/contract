
#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_HPP_

#include <boost/contract/ext_/preprocessor/paren/has.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// PRIVATE //

#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_(a, b) \
    BOOST_CONTRACT_EXT_PP_HAS_PAREN(BOOST_PP_CAT(a, b))

// PUBLIC //

// Precondition: A macro `<checking_prefix><keyword-to-check>` must be #defined
// to expand to unary (e.g., `(1)`).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_FRONT( \
        tokens, checking_prefix) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(tokens), \
        0 BOOST_PP_TUPLE_EAT(2) \
    , \
        BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_ \
    )(checking_prefix, tokens)

// Precondition: A macro `<keyword-to-check><checking_postfix>` must be #defined
// to expand to unary (e.g., `(1)`).
// WARNING: This check only works if `token` is a single token, it will always
// expand to 0 with no errors if token is multiple tokens
// (e.g., `const *this`). Also, this check will expand to 0 with no error if
// `token` starts with a non-alphanumeric symbol (e.g., `*this`).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_BACK( \
        token, checking_postfix) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_(token, checking_postfix)

#endif // #include guard

