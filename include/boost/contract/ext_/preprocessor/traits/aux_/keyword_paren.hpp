
#ifndef BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_HPP_
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_HPP_

#include <boost/contract/ext_/preprocessor/paren/front.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_FRONT_(tokens) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(tokens), \
        BOOST_CONTRACT_EXT_PP_PAREN_FRONT \
    , \
        BOOST_PP_TUPLE_EAT(1) \
    )(tokens)

// Precondition: tokens = `keyword ...`
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_( \
        tokens, remove_keyword_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_FRONT_( \
            remove_keyword_macro(tokens))

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_SKIP_EAT_(tokens) \
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(tokens), \
        BOOST_PP_TUPLE_EAT(0) \
    ) \
    tokens

// Precondition: tokens = `keyword ...`
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_SKIP_( \
        tokens, remove_keyword_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_SKIP_EAT_( \
            remove_keyword_macro(tokens))

/* PUBLIC */
   
// If tokens = `keyword(,,,) ...` expand to `(,,,)`, otherwise (i.e., both no
// keyword `(,,,) ...` and keyword with no parenthesis `keyword ...`) expand to
// EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN( \
        tokens, is_keyword_macro, remove_keyword_macro) \
    BOOST_PP_IIF(is_keyword_macro(tokens), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_ \
    , \
        BOOST_PP_TUPLE_EAT(2) \
    )(tokens, remove_keyword_macro)

// Expand tokens = `keyword(,,,) ...` and `keyword ...` to `...`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_SKIP( \
        tokens, is_keyword_macro, remove_keyword_macro) \
    BOOST_PP_IIF(is_keyword_macro(tokens), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_SKIP_ \
    , \
        tokens BOOST_PP_TUPLE_EAT(2) \
    )(tokens, remove_keyword_macro)

#endif // #include guard

