
#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_PAREN_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_PAREN_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/paren/front.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>

/* PUBLIC */
   
// Expand decl = `[keyword[(,,,)]] ...`   to `(..., [(,,,)] EMPTY)`.
// Precondition: `...` in decl cannot be EMPTY() (so expanded 2-tuple is valid).
// NOTE: Both keyword without (,,,) and no keyword at all expand to EMPTY trait.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_PAREN_TRAITS_PARSE( \
        decl, is_keyword_macro, remove_keyword_macro) \
    BOOST_PP_IIF(is_keyword_macro(decl), \
        BOOST_CONTRACT_EXT_PP_KEYWORD_PAREN_TRAITS_ \
    , \
        BOOST_CONTRACT_EXT_PP_KEYWORD_PAREN_TRAITS_NO_ \
    )(decl, remove_keyword_macro)

/* PRIVATE */

// Precondition: decl = `keyword ...`
#define BOOST_CONTRACT_EXT_PP_KEYWORD_PAREN_TRAITS_( \
        decl, remove_keyword_macro) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_PAREN_TRAITS_CHECK_( \
            remove_keyword_macro(decl))

#define BOOST_CONTRACT_EXT_PP_KEYWORD_PAREN_TRAITS_CHECK_(decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_KEYWORD_PAREN_TRAITS_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_KEYWORD_PAREN_TRAITS_NO_ \
    )(decl, ~)

// Precondition: decl = `(,,,) ...`.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_PAREN_TRAITS_YES_(decl, unused) \
    (BOOST_PP_TUPLE_EAT(0) decl, \
            BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl) BOOST_PP_EMPTY)
        
#define BOOST_CONTRACT_EXT_PP_KEYWORD_PAREN_TRAITS_NO_(decl, unused) \
    (decl, BOOST_PP_EMPTY)

#endif // #include guard

