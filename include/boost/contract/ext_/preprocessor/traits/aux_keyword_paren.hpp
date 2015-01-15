
#ifndef BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_HPP_
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_HPP_

#include <boost/contract/ext_/preprocessor/paren/front.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>

/* PRIVATE */

// Precondition: decl = `(,,,) ...`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_YES_(decl, unused) \
    (BOOST_PP_TUPLE_EAT(0) decl, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl))
        
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_NO_(decl, unused) \
    (decl, BOOST_PP_EMPTY())

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_CHECK_(decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_NO_ \
    )(decl, ~)

// Precondition: decl = `keyword ...`
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_( \
        decl, remove_keyword_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_CHECK_( \
            remove_keyword_macro(decl))

/* PUBLIC */
   
// Expand:
//  decl = `keyword(,,,) ...`   to `(..., (,,,))`.
//  decl = `keyword ...`        to `(..., EMPTY())`.
//  decl = `...`                to `(..., EMPTY())`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN( \
        decl, is_keyword_macro, remove_keyword_macro) \
    BOOST_PP_IIF(is_keyword_macro(decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_NO_ \
    )(decl, remove_keyword_macro)

#endif // #include guard

