
#ifndef BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run related generation script "assertion-generate.py".

#include <boost/contract/ext_/preprocessor/traits/assertion/bool.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/if.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/const.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/oldof.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/return.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/typedef.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/using.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/namespace.hpp>
#include <boost/contract/ext_/preprocessor/keyword/namespace.hpp>
#include <boost/contract/ext_/preprocessor/keyword/using.hpp>
#include <boost/contract/ext_/preprocessor/keyword/template.hpp>
#include <boost/contract/ext_/preprocessor/keyword/typedef.hpp>
#include <boost/contract/ext_/preprocessor/keyword/return.hpp>
#include <boost/contract/ext_/preprocessor/keyword/const.hpp>
#include <boost/contract/ext_/preprocessor/keyword/if.hpp>
#include <boost/contract/ext_/preprocessor/paren/has.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>

/* PUBLIC (1) */

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_1(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_1_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_1_( \
            decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_1_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_1_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_1_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_1_ \
    ))))))(d, l, decl)

/* PRIVATE (1) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_1_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_1_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_1_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_1_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_1_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// Expand to 1 if decl = `[template(,,,)] using ...`, otherwise to 0.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_1_(decl) \
    BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_USING_FRONT(decl), \
            1 BOOST_PP_TUPLE_EAT(1) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT(decl), \
            BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_TEMPLATE_1_ \
        , \
            0 BOOST_PP_TUPLE_EAT(1) \
        ))(decl) \
    )

// Precondition: decl = `template ...`
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_TEMPLATE_1_(decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT(decl)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_TEMPLATE_PAREN_1_ \
    , \
        0 BOOST_PP_TUPLE_EAT(1) \
    )(BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT(decl))

// Precondition: decl = `(,,,) ...`
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_TEMPLATE_PAREN_1_( \
        decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_USING_FRONT( \
            BOOST_PP_TUPLE_EAT(0) decl), 1, 0)

/* PUBLIC (2) */

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_2(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_2_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_2_( \
            decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_2_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_2_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_2_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_2_ \
    ))))))(d, l, decl)

/* PRIVATE (2) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_2_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_2_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_2_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_2_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_2_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// Expand to 1 if decl = `[template(,,,)] using ...`, otherwise to 0.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_2_(decl) \
    BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_USING_FRONT(decl), \
            1 BOOST_PP_TUPLE_EAT(1) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT(decl), \
            BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_TEMPLATE_2_ \
        , \
            0 BOOST_PP_TUPLE_EAT(1) \
        ))(decl) \
    )

// Precondition: decl = `template ...`
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_TEMPLATE_2_(decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT(decl)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_TEMPLATE_PAREN_2_ \
    , \
        0 BOOST_PP_TUPLE_EAT(1) \
    )(BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT(decl))

// Precondition: decl = `(,,,) ...`
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_TEMPLATE_PAREN_2_( \
        decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_USING_FRONT( \
            BOOST_PP_TUPLE_EAT(0) decl), 1, 0)

#endif // #include guard

