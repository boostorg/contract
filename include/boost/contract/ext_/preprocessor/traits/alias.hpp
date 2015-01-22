
#ifndef BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/alias/parse/typedef.hpp>
#include <boost/contract/ext_/preprocessor/traits/alias/parse/using.hpp>
#include <boost/contract/ext_/preprocessor/traits/alias/parse/namespace.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/namespace.hpp>
#include <boost/contract/ext_/preprocessor/keyword/using.hpp>
#include <boost/contract/ext_/preprocessor/keyword/template.hpp>
#include <boost/contract/ext_/preprocessor/keyword/typedef.hpp>
#include <boost/contract/ext_/preprocessor/functional/invoke.hpp>
#include <boost/contract/ext_/preprocessor/paren/has.hpp>
#include <boost/contract/ext_/preprocessor/utility/expand.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_D_(d, parse_macro, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE(parse_macro(d, \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT(decl)))

#define BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_(unsued, parse_macro, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE(parse_macro( \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT(decl)))

// Implementation: This must expand to empty.
#define BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_EMPTY_(unsued1, unused2, unsued3)

// Precondition: decl = `(,,,) ...`
#define BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_IS_USING_TEMPLATE_PAREN_(decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_USING_FRONT( \
            BOOST_PP_TUPLE_EAT(0) decl), 1, 0)

// Precondition: decl = `template ...`
#define BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_IS_USING_TEMPLATE_(decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT(decl)), \
        BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_IS_USING_TEMPLATE_PAREN_ \
    , \
        0 BOOST_PP_TUPLE_EAT(1) \
    )(BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT(decl))

// Expand to 1 if decl = `[template(,,,)] using ...`, otherwise to 0.
// Implementation: EXPAND needed for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_IS_USING_(decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_USING_FRONT(decl), \
        1 BOOST_PP_TUPLE_EAT(1) \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_IS_USING_TEMPLATE_ \
    , \
        0 BOOST_PP_TUPLE_EAT(1) \
    ))(decl)

/* PUBLIC */

// Expand to EMPTY() if decl is not an alias declaration, otherwise expand to
// alias traits.
#define BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_D(d, decl) \
    BOOST_CONTRACT_EXT_PP_EXPAND_ONCE( \
        BOOST_CONTRACT_EXT_PP_INVOKE3 \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
            (BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_, ~, \
            BOOST_CONTRACT_EXT_PP_NAMESPACE_ALIAS_TRAITS_PARSE, decl) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_IS_USING_(decl), \
            (BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_, ~, \
            BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_PARSE, decl) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
            (BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_D_, d, \
            BOOST_CONTRACT_EXT_PP_TYPEDEF_ALIAS_TRAITS_PARSE_D, decl) \
        , \
            (BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_EMPTY_, ~, ~, ~) \
        ))) \
    )

#endif // #include guard

