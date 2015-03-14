
#ifndef BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_LIST_HPP_
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_LIST_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>
#include <boost/contract/ext_/preprocessor/paren/front.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PUBLIC */

// Expand `[keyword(,,,)] ...` to decl `...` and append traits with
// `[keyword] EMPTY` (but only if keyword macro param below != EMPTY()) always
// followed by `list_parse_macro(,,,)`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_LIST_PARSE_D(d, decl_traits, \
        keyword, is_keyword_macro, remove_keyword_macro, list_parse_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_LIST_PARSE_ARGS_(d, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits), \
        keyword, \
        is_keyword_macro, \
        remove_keyword_macro, \
        list_parse_macro \
    )

// Precondition: decl = `(,,,) ...` from `[keyword](,,,) ...` originally in
// decl (keyword can be EMPTY() to append only parsed list, see macro above).
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_LIST_PUSH_BACK_PARSE_D( \
        d, decl, traits, keyword, list_parse_macro) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PUSH_BACK( \
            BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(keyword), \
                traits BOOST_PP_TUPLE_EAT(2) \
            , \
                BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PUSH_BACK \
            )(traits, keyword BOOST_PP_EMPTY), \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_LIST_EXPAND_TRAITS_( \
                list_parse_macro(d, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_LIST_PARSE_ARGS_( \
    d, decl, traits, \
    keyword, is_keyword_macro, remove_keyword_macro, list_parse_macro \
) \
    BOOST_PP_IIF(is_keyword_macro(decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_LIST_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_LIST_NO_ \
    )(d, decl, traits, keyword, remove_keyword_macro, list_parse_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_LIST_NO_( \
        d, decl, traits, keyword, remove_keyword_macro, list_parse_macro) \
    ( \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PUSH_BACK( \
            BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(keyword), \
                traits BOOST_PP_TUPLE_EAT(2) \
            , \
                BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PUSH_BACK \
            )(traits, BOOST_PP_EMPTY), \
            BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `keyword(,,,) ...`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_LIST_YES_( \
        d, decl, traits, keyword, remove_keyword_macro, list_parse_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_LIST_PUSH_BACK_PARSE_D(d, \
            remove_keyword_macro(decl), traits, keyword, list_parse_macro)

// Extra level of indirection needed for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_LIST_EXPAND_TRAITS_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

#endif // #include guard

