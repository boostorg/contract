
#ifndef BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_HPP_
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_HPP_

#include <boost/contract/ext_/preprocessor/functional/invoke.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/* PRIVATE */

// Precondition: decl = `keyword ...`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_YES_( \
        decl, keyword, remove_keyword_macro) \
    (remove_keyword_macro(decl), keyword)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_NO_(decl, unsued1, unused2) \
    (decl, BOOST_PP_EMPTY())

/* PUBLIC */

// Expand:
//  decl = `keyword ...`    to `(..., keyword)`.
//  decl = `...`            to `(..., EMPTY())`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD1( \
    decl, \
    keyword1, is_keyword1_macro, remove_keyword1_macro \
) \
    BOOST_PP_EXPAND( \
        BOOST_CONTRACT_EXT_PP_INVOKE3 \
        BOOST_PP_IIF(is_keyword1_macro(decl), \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_YES_, decl, \
            keyword1, remove_keyword1_macro) \
        , \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_NO_, decl, ~, ~) \
        ) \
    )

// Expand:
//  decl = `keyword ...`    to `(..., keyword)`.
//  decl = `...`            to `(..., EMPTY())`.
// Where keyword can be one among 2 possible keywords.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2( \
    decl, \
    keyword1, is_keyword1_macro, remove_keyword1_macro, \
    keyword2, is_keyword2_macro, remove_keyword2_macro \
) \
    BOOST_PP_EXPAND( \
        BOOST_CONTRACT_EXT_PP_INVOKE3 \
        BOOST_PP_IIF(is_keyword1_macro(decl), \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_YES_, decl, \
            keyword1, remove_keyword1_macro) \
        , BOOST_PP_IIF(is_keyword2_macro(decl), \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_YES_, decl, \
            keyword2, remove_keyword2_macro) \
        , \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_NO_, decl, ~, ~) \
        )) \
    )

// Expand:
//  decl = `keyword ...`    to `(..., keyword)`.
//  decl = `...`            to `(..., EMPTY())`.
// Where keyword can be one among 3 possible keywords.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD3( \
    decl, \
    keyword1, is_keyword1_macro, remove_keyword1_macro, \
    keyword2, is_keyword2_macro, remove_keyword2_macro, \
    keyword3, is_keyword3_macro, remove_keyword3_macro \
) \
    BOOST_PP_EXPAND( \
        BOOST_CONTRACT_EXT_PP_INVOKE3 \
        BOOST_PP_IIF(is_keyword1_macro(decl), \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_YES_, decl, \
            keyword1, remove_keyword1_macro) \
        , BOOST_PP_IIF(is_keyword2_macro(decl), \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_YES_, decl, \
            keyword2, remove_keyword2_macro) \
        , BOOST_PP_IIF(is_keyword3_macro(decl), \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_YES_, decl, \
            keyword3, remove_keyword3_macro) \
        , \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_NO_, decl, ~, ~) \
        ))) \
    )

#endif // #include guard

