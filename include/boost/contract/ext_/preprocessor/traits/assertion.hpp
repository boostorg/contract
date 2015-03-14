
#ifndef BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run related generation script "assertion-generate.py".

#include <boost/contract/ext_/preprocessor/traits/assertion/bool.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/const.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/if.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/oldof.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/return.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/typedef.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/using.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/namespace.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/type.hpp>
#include <boost/contract/ext_/preprocessor/keyword/namespace.hpp>
#include <boost/contract/ext_/preprocessor/keyword/using.hpp>
#include <boost/contract/ext_/preprocessor/keyword/template.hpp>
#include <boost/contract/ext_/preprocessor/keyword/typedef.hpp>
#include <boost/contract/ext_/preprocessor/keyword/return.hpp>
#include <boost/contract/ext_/preprocessor/keyword/const.hpp>
#include <boost/contract/ext_/preprocessor/keyword/if.hpp>
#include <boost/contract/ext_/preprocessor/keyword/else.hpp>
#include <boost/contract/ext_/preprocessor/paren/has.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>

/* PUBLIC */

// Maximum number of nested assertions that can be parsed (before pp errors).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_LIMIT 64

/* PRIVATE */

// Expand to 1 if decl = `[template(,,,)] using ...`, otherwise to 0.
// EXPAND for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_USING_FRONT(\
            decl), \
        1 BOOST_PP_TUPLE_EAT(1) \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_TEMPLATE_ \
    , \
        0 BOOST_PP_TUPLE_EAT(1) \
    ))(decl))

// Precondition: decl = `template ...`
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_TEMPLATE_(decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT(decl)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_TEMPLATE_PAREN_ \
    , \
        0 BOOST_PP_TUPLE_EAT(1) \
    )(BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT(decl))

// Precondition: decl = `(,,,) ...`
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_TEMPLATE_PAREN_( \
        decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_USING_FRONT( \
            BOOST_PP_TUPLE_EAT(0) decl), 1, 0)

/* PUBLIC (1) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_1(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_1_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_1_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_1_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_1 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_1_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_1(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_1_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_1_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_1_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_1 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_1_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_1( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_1( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_1( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_1( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_1( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_1\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_1_ \
    )(d, l, decl_traits)

/* PRIVATE (1) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_1_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
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

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_1_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_1_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_1_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_1_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_1_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_1_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_1_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_1_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_1_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_1_ \
    )(d, l, decl)


/* PUBLIC (2) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_2(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_2_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_2_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_2_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_2 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_2 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_2_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_2(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_2_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_2_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_2_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_2 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_2 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_2_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_2( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_2( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_2( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_2( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_2( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_2\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_2_ \
    )(d, l, decl_traits)

/* PRIVATE (2) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_2_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
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

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_2_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_2_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_2_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_2_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_2_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_2_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_2_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_2_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_2_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_2_ \
    )(d, l, decl)


/* PUBLIC (3) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_3(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_3_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_3_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_3_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_3 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_3 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_3_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_3(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_3_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_3_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_3_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_3 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_3 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_3_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_3( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_3( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_3( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_3( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_3( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_3\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_3_ \
    )(d, l, decl_traits)

/* PRIVATE (3) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_3_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_3_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_3_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_3_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_3_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_3_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_3_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_3_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_3_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_3_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_3_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_3_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_3_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_3_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_3_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_3_ \
    )(d, l, decl)


/* PUBLIC (4) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_4(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_4_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_4_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_4_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_4 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_4 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_4_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_4(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_4_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_4_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_4_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_4 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_4 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_4_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_4( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_4( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_4( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_4( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_4( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_4\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_4_ \
    )(d, l, decl_traits)

/* PRIVATE (4) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_4_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_4_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_4_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_4_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_4_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_4_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_4_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_4_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_4_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_4_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_4_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_4_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_4_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_4_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_4_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_4_ \
    )(d, l, decl)


/* PUBLIC (5) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_5(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_5_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_5_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_5_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_5 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_5 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_5_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_5(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_5_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_5_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_5_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_5 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_5 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_5_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_5( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_5( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_5( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_5( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_5( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_5\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_5_ \
    )(d, l, decl_traits)

/* PRIVATE (5) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_5_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_5_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_5_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_5_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_5_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_5_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_5_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_5_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_5_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_5_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_5_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_5_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_5_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_5_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_5_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_5_ \
    )(d, l, decl)


/* PUBLIC (6) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_6(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_6_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_6_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_6_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_6 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_6 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_6_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_6(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_6_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_6_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_6_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_6 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_6 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_6_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_6( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_6( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_6( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_6( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_6( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_6\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_6_ \
    )(d, l, decl_traits)

/* PRIVATE (6) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_6_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_6_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_6_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_6_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_6_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_6_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_6_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_6_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_6_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_6_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_6_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_6_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_6_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_6_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_6_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_6_ \
    )(d, l, decl)


/* PUBLIC (7) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_7(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_7_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_7_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_7_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_7 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_7 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_7_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_7(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_7_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_7_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_7_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_7 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_7 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_7_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_7( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_7( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_7( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_7( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_7( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_7\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_7_ \
    )(d, l, decl_traits)

/* PRIVATE (7) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_7_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_7_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_7_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_7_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_7_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_7_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_7_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_7_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_7_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_7_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_7_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_7_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_7_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_7_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_7_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_7_ \
    )(d, l, decl)


/* PUBLIC (8) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_8(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_8_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_8_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_8_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_8 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_8 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_8_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_8(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_8_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_8_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_8_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_8 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_8 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_8_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_8( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_8( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_8( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_8( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_8( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_8\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_8_ \
    )(d, l, decl_traits)

/* PRIVATE (8) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_8_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_8_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_8_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_8_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_8_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_8_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_8_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_8_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_8_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_8_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_8_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_8_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_8_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_8_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_8_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_8_ \
    )(d, l, decl)


/* PUBLIC (9) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_9(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_9_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_9_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_9_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_9 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_9 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_9_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_9(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_9_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_9_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_9_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_9 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_9 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_9_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_9( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_9( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_9( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_9( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_9( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_9\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_9_ \
    )(d, l, decl_traits)

/* PRIVATE (9) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_9_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_9_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_9_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_9_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_9_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_9_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_9_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_9_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_9_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_9_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_9_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_9_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_9_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_9_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_9_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_9_ \
    )(d, l, decl)


/* PUBLIC (10) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_10(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_10_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_10_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_10_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_10 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_10 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_10_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_10(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_10_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_10_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_10_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_10 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_10 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_10_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_10( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_10( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_10( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_10( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_10( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_10\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_10_ \
    )(d, l, decl_traits)

/* PRIVATE (10) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_10_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_10_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_10_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_10_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_10_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_10_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_10_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_10_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_10_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_10_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_10_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_10_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_10_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_10_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_10_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_10_ \
    )(d, l, decl)


/* PUBLIC (11) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_11(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_11_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_11_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_11_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_11 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_11 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_11_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_11(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_11_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_11_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_11_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_11 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_11 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_11_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_11( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_11( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_11( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_11( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_11( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_11\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_11_ \
    )(d, l, decl_traits)

/* PRIVATE (11) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_11_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_11_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_11_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_11_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_11_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_11_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_11_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_11_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_11_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_11_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_11_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_11_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_11_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_11_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_11_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_11_ \
    )(d, l, decl)


/* PUBLIC (12) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_12(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_12_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_12_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_12_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_12 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_12 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_12_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_12(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_12_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_12_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_12_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_12 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_12 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_12_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_12( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_12( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_12( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_12( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_12( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_12\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_12_ \
    )(d, l, decl_traits)

/* PRIVATE (12) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_12_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_12_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_12_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_12_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_12_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_12_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_12_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_12_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_12_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_12_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_12_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_12_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_12_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_12_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_12_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_12_ \
    )(d, l, decl)


/* PUBLIC (13) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_13(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_13_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_13_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_13_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_13 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_13 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_13_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_13(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_13_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_13_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_13_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_13 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_13 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_13_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_13( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_13( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_13( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_13( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_13( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_13\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_13_ \
    )(d, l, decl_traits)

/* PRIVATE (13) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_13_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_13_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_13_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_13_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_13_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_13_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_13_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_13_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_13_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_13_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_13_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_13_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_13_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_13_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_13_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_13_ \
    )(d, l, decl)


/* PUBLIC (14) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_14(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_14_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_14_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_14_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_14 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_14 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_14_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_14(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_14_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_14_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_14_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_14 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_14 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_14_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_14( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_14( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_14( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_14( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_14( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_14\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_14_ \
    )(d, l, decl_traits)

/* PRIVATE (14) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_14_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_14_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_14_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_14_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_14_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_14_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_14_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_14_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_14_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_14_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_14_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_14_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_14_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_14_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_14_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_14_ \
    )(d, l, decl)


/* PUBLIC (15) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_15(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_15_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_15_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_15_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_15 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_15 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_15_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_15(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_15_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_15_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_15_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_15 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_15 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_15_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_15( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_15( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_15( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_15( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_15( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_15\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_15_ \
    )(d, l, decl_traits)

/* PRIVATE (15) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_15_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_15_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_15_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_15_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_15_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_15_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_15_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_15_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_15_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_15_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_15_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_15_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_15_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_15_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_15_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_15_ \
    )(d, l, decl)


/* PUBLIC (16) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_16(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_16_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_16_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_16_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_16 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_16 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_16_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_16(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_16_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_16_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_16_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_16 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_16 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_16_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_16( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_16( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_16( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_16( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_16( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_16\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_16_ \
    )(d, l, decl_traits)

/* PRIVATE (16) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_16_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_16_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_16_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_16_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_16_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_16_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_16_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_16_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_16_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_16_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_16_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_16_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_16_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_16_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_16_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_16_ \
    )(d, l, decl)


/* PUBLIC (17) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_17(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_17_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_17_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_17_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_17 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_17 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_17_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_17(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_17_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_17_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_17_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_17 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_17 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_17_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_17( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_17( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_17( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_17( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_17( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_17\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_17_ \
    )(d, l, decl_traits)

/* PRIVATE (17) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_17_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_17_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_17_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_17_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_17_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_17_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_17_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_17_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_17_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_17_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_17_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_17_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_17_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_17_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_17_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_17_ \
    )(d, l, decl)


/* PUBLIC (18) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_18(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_18_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_18_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_18_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_18 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_18 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_18_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_18(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_18_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_18_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_18_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_18 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_18 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_18_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_18( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_18( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_18( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_18( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_18( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_18\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_18_ \
    )(d, l, decl_traits)

/* PRIVATE (18) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_18_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_18_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_18_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_18_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_18_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_18_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_18_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_18_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_18_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_18_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_18_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_18_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_18_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_18_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_18_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_18_ \
    )(d, l, decl)


/* PUBLIC (19) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_19(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_19_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_19_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_19_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_19 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_19 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_19_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_19(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_19_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_19_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_19_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_19 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_19 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_19_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_19( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_19( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_19( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_19( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_19( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_19\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_19_ \
    )(d, l, decl_traits)

/* PRIVATE (19) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_19_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_19_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_19_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_19_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_19_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_19_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_19_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_19_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_19_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_19_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_19_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_19_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_19_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_19_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_19_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_19_ \
    )(d, l, decl)


/* PUBLIC (20) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_20(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_20_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_20_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_20_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_20 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_20 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_20_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_20(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_20_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_20_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_20_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_20 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_20 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_20_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_20( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_20( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_20( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_20( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_20( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_20\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_20_ \
    )(d, l, decl_traits)

/* PRIVATE (20) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_20_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_20_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_20_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_20_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_20_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_20_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_20_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_20_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_20_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_20_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_20_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_20_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_20_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_20_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_20_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_20_ \
    )(d, l, decl)


/* PUBLIC (21) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_21(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_21_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_21_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_21_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_21 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_21 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_21_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_21(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_21_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_21_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_21_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_21 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_21 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_21_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_21( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_21( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_21( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_21( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_21( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_21\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_21_ \
    )(d, l, decl_traits)

/* PRIVATE (21) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_21_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_21_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_21_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_21_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_21_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_21_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_21_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_21_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_21_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_21_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_21_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_21_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_21_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_21_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_21_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_21_ \
    )(d, l, decl)


/* PUBLIC (22) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_22(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_22_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_22_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_22_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_22 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_22 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_22_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_22(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_22_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_22_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_22_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_22 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_22 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_22_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_22( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_22( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_22( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_22( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_22( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_22\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_22_ \
    )(d, l, decl_traits)

/* PRIVATE (22) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_22_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_22_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_22_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_22_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_22_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_22_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_22_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_22_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_22_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_22_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_22_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_22_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_22_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_22_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_22_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_22_ \
    )(d, l, decl)


/* PUBLIC (23) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_23(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_23_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_23_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_23_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_23 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_23 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_23_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_23(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_23_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_23_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_23_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_23 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_23 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_23_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_23( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_23( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_23( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_23( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_23( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_23\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_23_ \
    )(d, l, decl_traits)

/* PRIVATE (23) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_23_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_23_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_23_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_23_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_23_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_23_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_23_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_23_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_23_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_23_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_23_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_23_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_23_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_23_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_23_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_23_ \
    )(d, l, decl)


/* PUBLIC (24) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_24(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_24_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_24_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_24_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_24 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_24 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_24_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_24(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_24_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_24_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_24_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_24 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_24 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_24_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_24( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_24( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_24( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_24( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_24( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_24\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_24_ \
    )(d, l, decl_traits)

/* PRIVATE (24) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_24_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_24_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_24_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_24_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_24_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_24_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_24_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_24_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_24_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_24_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_24_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_24_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_24_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_24_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_24_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_24_ \
    )(d, l, decl)


/* PUBLIC (25) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_25(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_25_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_25_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_25_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_25 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_25 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_25_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_25(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_25_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_25_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_25_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_25 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_25 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_25_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_25( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_25( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_25( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_25( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_25( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_25\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_25_ \
    )(d, l, decl_traits)

/* PRIVATE (25) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_25_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_25_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_25_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_25_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_25_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_25_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_25_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_25_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_25_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_25_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_25_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_25_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_25_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_25_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_25_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_25_ \
    )(d, l, decl)


/* PUBLIC (26) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_26(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_26_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_26_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_26_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_26 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_26 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_26_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_26(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_26_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_26_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_26_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_26 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_26 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_26_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_26( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_26( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_26( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_26( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_26( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_26\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_26_ \
    )(d, l, decl_traits)

/* PRIVATE (26) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_26_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_26_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_26_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_26_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_26_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_26_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_26_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_26_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_26_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_26_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_26_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_26_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_26_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_26_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_26_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_26_ \
    )(d, l, decl)


/* PUBLIC (27) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_27(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_27_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_27_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_27_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_27 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_27 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_27_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_27(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_27_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_27_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_27_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_27 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_27 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_27_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_27( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_27( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_27( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_27( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_27( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_27\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_27_ \
    )(d, l, decl_traits)

/* PRIVATE (27) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_27_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_27_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_27_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_27_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_27_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_27_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_27_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_27_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_27_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_27_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_27_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_27_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_27_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_27_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_27_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_27_ \
    )(d, l, decl)


/* PUBLIC (28) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_28(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_28_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_28_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_28_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_28 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_28 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_28_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_28(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_28_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_28_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_28_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_28 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_28 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_28_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_28( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_28( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_28( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_28( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_28( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_28\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_28_ \
    )(d, l, decl_traits)

/* PRIVATE (28) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_28_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_28_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_28_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_28_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_28_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_28_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_28_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_28_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_28_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_28_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_28_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_28_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_28_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_28_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_28_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_28_ \
    )(d, l, decl)


/* PUBLIC (29) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_29(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_29_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_29_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_29_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_29 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_29 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_29_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_29(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_29_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_29_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_29_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_29 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_29 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_29_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_29( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_29( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_29( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_29( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_29( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_29\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_29_ \
    )(d, l, decl_traits)

/* PRIVATE (29) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_29_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_29_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_29_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_29_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_29_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_29_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_29_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_29_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_29_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_29_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_29_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_29_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_29_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_29_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_29_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_29_ \
    )(d, l, decl)


/* PUBLIC (30) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_30(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_30_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_30_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_30_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_30 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_30 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_30_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_30(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_30_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_30_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_30_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_30 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_30 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_30_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_30( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_30( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_30( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_30( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_30( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_30\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_30_ \
    )(d, l, decl_traits)

/* PRIVATE (30) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_30_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_30_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_30_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_30_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_30_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_30_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_30_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_30_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_30_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_30_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_30_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_30_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_30_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_30_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_30_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_30_ \
    )(d, l, decl)


/* PUBLIC (31) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_31(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_31_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_31_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_31_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_31 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_31 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_31_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_31(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_31_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_31_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_31_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_31 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_31 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_31_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_31( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_31( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_31( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_31( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_31( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_31\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_31_ \
    )(d, l, decl_traits)

/* PRIVATE (31) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_31_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_31_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_31_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_31_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_31_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_31_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_31_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_31_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_31_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_31_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_31_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_31_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_31_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_31_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_31_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_31_ \
    )(d, l, decl)


/* PUBLIC (32) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_32(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_32_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_32_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_32_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_32 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_32 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_32_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_32(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_32_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_32_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_32_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_32 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_32 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_32_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_32( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_32( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_32( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_32( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_32( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_32\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_32_ \
    )(d, l, decl_traits)

/* PRIVATE (32) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_32_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_32_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_32_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_32_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_32_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_32_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_32_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_32_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_32_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_32_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_32_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_32_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_32_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_32_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_32_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_32_ \
    )(d, l, decl)


/* PUBLIC (33) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_33(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_33_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_33_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_33_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_33 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_33 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_33_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_33(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_33_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_33_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_33_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_33 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_33 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_33_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_33( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_33( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_33( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_33( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_33( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_33\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_33_ \
    )(d, l, decl_traits)

/* PRIVATE (33) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_33_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_33_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_33_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_33_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_33_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_33_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_33_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_33_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_33_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_33_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_33_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_33_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_33_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_33_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_33_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_33_ \
    )(d, l, decl)


/* PUBLIC (34) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_34(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_34_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_34_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_34_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_34 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_34 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_34_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_34(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_34_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_34_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_34_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_34 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_34 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_34_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_34( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_34( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_34( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_34( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_34( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_34\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_34_ \
    )(d, l, decl_traits)

/* PRIVATE (34) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_34_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_34_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_34_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_34_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_34_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_34_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_34_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_34_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_34_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_34_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_34_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_34_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_34_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_34_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_34_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_34_ \
    )(d, l, decl)


/* PUBLIC (35) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_35(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_35_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_35_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_35_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_35 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_35 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_35_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_35(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_35_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_35_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_35_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_35 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_35 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_35_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_35( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_35( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_35( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_35( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_35( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_35\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_35_ \
    )(d, l, decl_traits)

/* PRIVATE (35) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_35_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_35_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_35_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_35_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_35_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_35_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_35_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_35_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_35_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_35_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_35_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_35_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_35_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_35_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_35_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_35_ \
    )(d, l, decl)


/* PUBLIC (36) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_36(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_36_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_36_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_36_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_36 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_36 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_36_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_36(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_36_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_36_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_36_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_36 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_36 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_36_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_36( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_36( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_36( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_36( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_36( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_36\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_36_ \
    )(d, l, decl_traits)

/* PRIVATE (36) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_36_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_36_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_36_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_36_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_36_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_36_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_36_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_36_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_36_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_36_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_36_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_36_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_36_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_36_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_36_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_36_ \
    )(d, l, decl)


/* PUBLIC (37) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_37(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_37_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_37_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_37_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_37 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_37 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_37_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_37(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_37_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_37_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_37_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_37 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_37 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_37_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_37( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_37( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_37( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_37( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_37( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_37\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_37_ \
    )(d, l, decl_traits)

/* PRIVATE (37) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_37_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_37_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_37_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_37_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_37_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_37_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_37_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_37_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_37_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_37_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_37_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_37_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_37_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_37_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_37_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_37_ \
    )(d, l, decl)


/* PUBLIC (38) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_38(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_38_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_38_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_38_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_38 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_38 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_38_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_38(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_38_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_38_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_38_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_38 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_38 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_38_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_38( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_38( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_38( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_38( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_38( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_38\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_38_ \
    )(d, l, decl_traits)

/* PRIVATE (38) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_38_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_38_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_38_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_38_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_38_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_38_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_38_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_38_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_38_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_38_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_38_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_38_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_38_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_38_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_38_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_38_ \
    )(d, l, decl)


/* PUBLIC (39) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_39(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_39_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_39_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_39_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_39 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_39 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_39_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_39(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_39_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_39_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_39_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_39 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_39 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_39_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_39( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_39( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_39( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_39( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_39( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_39\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_39_ \
    )(d, l, decl_traits)

/* PRIVATE (39) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_39_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_39_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_39_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_39_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_39_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_39_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_39_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_39_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_39_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_39_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_39_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_39_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_39_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_39_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_39_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_39_ \
    )(d, l, decl)


/* PUBLIC (40) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_40(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_40_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_40_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_40_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_40 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_40 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_40_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_40(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_40_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_40_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_40_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_40 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_40 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_40_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_40( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_40( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_40( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_40( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_40( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_40\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_40_ \
    )(d, l, decl_traits)

/* PRIVATE (40) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_40_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_40_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_40_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_40_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_40_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_40_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_40_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_40_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_40_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_40_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_40_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_40_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_40_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_40_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_40_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_40_ \
    )(d, l, decl)


/* PUBLIC (41) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_41(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_41_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_41_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_41_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_41 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_41 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_41_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_41(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_41_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_41_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_41_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_41 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_41 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_41_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_41( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_41( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_41( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_41( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_41( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_41\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_41_ \
    )(d, l, decl_traits)

/* PRIVATE (41) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_41_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_41_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_41_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_41_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_41_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_41_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_41_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_41_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_41_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_41_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_41_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_41_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_41_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_41_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_41_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_41_ \
    )(d, l, decl)


/* PUBLIC (42) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_42(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_42_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_42_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_42_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_42 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_42 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_42_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_42(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_42_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_42_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_42_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_42 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_42 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_42_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_42( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_42( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_42( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_42( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_42( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_42\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_42_ \
    )(d, l, decl_traits)

/* PRIVATE (42) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_42_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_42_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_42_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_42_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_42_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_42_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_42_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_42_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_42_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_42_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_42_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_42_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_42_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_42_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_42_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_42_ \
    )(d, l, decl)


/* PUBLIC (43) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_43(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_43_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_43_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_43_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_43 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_43 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_43_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_43(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_43_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_43_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_43_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_43 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_43 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_43_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_43( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_43( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_43( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_43( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_43( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_43\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_43_ \
    )(d, l, decl_traits)

/* PRIVATE (43) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_43_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_43_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_43_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_43_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_43_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_43_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_43_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_43_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_43_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_43_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_43_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_43_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_43_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_43_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_43_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_43_ \
    )(d, l, decl)


/* PUBLIC (44) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_44(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_44_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_44_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_44_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_44 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_44 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_44_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_44(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_44_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_44_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_44_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_44 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_44 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_44_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_44( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_44( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_44( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_44( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_44( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_44\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_44_ \
    )(d, l, decl_traits)

/* PRIVATE (44) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_44_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_44_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_44_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_44_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_44_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_44_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_44_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_44_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_44_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_44_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_44_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_44_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_44_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_44_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_44_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_44_ \
    )(d, l, decl)


/* PUBLIC (45) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_45(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_45_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_45_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_45_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_45 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_45 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_45_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_45(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_45_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_45_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_45_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_45 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_45 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_45_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_45( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_45( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_45( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_45( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_45( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_45\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_45_ \
    )(d, l, decl_traits)

/* PRIVATE (45) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_45_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_45_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_45_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_45_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_45_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_45_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_45_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_45_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_45_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_45_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_45_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_45_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_45_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_45_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_45_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_45_ \
    )(d, l, decl)


/* PUBLIC (46) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_46(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_46_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_46_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_46_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_46 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_46 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_46_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_46(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_46_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_46_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_46_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_46 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_46 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_46_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_46( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_46( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_46( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_46( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_46( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_46\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_46_ \
    )(d, l, decl_traits)

/* PRIVATE (46) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_46_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_46_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_46_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_46_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_46_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_46_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_46_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_46_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_46_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_46_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_46_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_46_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_46_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_46_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_46_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_46_ \
    )(d, l, decl)


/* PUBLIC (47) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_47(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_47_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_47_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_47_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_47 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_47 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_47_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_47(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_47_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_47_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_47_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_47 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_47 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_47_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_47( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_47( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_47( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_47( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_47( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_47\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_47_ \
    )(d, l, decl_traits)

/* PRIVATE (47) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_47_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_47_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_47_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_47_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_47_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_47_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_47_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_47_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_47_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_47_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_47_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_47_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_47_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_47_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_47_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_47_ \
    )(d, l, decl)


/* PUBLIC (48) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_48(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_48_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_48_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_48_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_48 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_48 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_48_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_48(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_48_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_48_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_48_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_48 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_48 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_48_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_48( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_48( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_48( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_48( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_48( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_48\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_48_ \
    )(d, l, decl_traits)

/* PRIVATE (48) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_48_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_48_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_48_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_48_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_48_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_48_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_48_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_48_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_48_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_48_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_48_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_48_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_48_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_48_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_48_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_48_ \
    )(d, l, decl)


/* PUBLIC (49) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_49(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_49_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_49_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_49_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_49 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_49 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_49_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_49(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_49_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_49_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_49_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_49 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_49 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_49_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_49( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_49( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_49( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_49( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_49( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_49\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_49_ \
    )(d, l, decl_traits)

/* PRIVATE (49) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_49_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_49_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_49_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_49_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_49_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_49_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_49_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_49_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_49_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_49_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_49_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_49_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_49_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_49_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_49_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_49_ \
    )(d, l, decl)


/* PUBLIC (50) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_50(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_50_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_50_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_50_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_50 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_50 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_50_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_50(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_50_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_50_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_50_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_50 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_50 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_50_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_50( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_50( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_50( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_50( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_50( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_50\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_50_ \
    )(d, l, decl_traits)

/* PRIVATE (50) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_50_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_50_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_50_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_50_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_50_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_50_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_50_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_50_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_50_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_50_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_50_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_50_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_50_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_50_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_50_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_50_ \
    )(d, l, decl)


/* PUBLIC (51) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_51(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_51_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_51_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_51_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_51 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_51 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_51_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_51(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_51_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_51_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_51_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_51 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_51 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_51_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_51( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_51( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_51( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_51( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_51( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_51\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_51_ \
    )(d, l, decl_traits)

/* PRIVATE (51) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_51_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_51_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_51_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_51_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_51_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_51_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_51_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_51_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_51_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_51_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_51_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_51_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_51_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_51_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_51_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_51_ \
    )(d, l, decl)


/* PUBLIC (52) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_52(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_52_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_52_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_52_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_52 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_52 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_52_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_52(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_52_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_52_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_52_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_52 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_52 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_52_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_52( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_52( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_52( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_52( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_52( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_52\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_52_ \
    )(d, l, decl_traits)

/* PRIVATE (52) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_52_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_52_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_52_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_52_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_52_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_52_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_52_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_52_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_52_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_52_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_52_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_52_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_52_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_52_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_52_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_52_ \
    )(d, l, decl)


/* PUBLIC (53) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_53(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_53_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_53_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_53_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_53 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_53 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_53_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_53(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_53_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_53_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_53_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_53 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_53 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_53_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_53( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_53( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_53( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_53( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_53( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_53\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_53_ \
    )(d, l, decl_traits)

/* PRIVATE (53) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_53_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_53_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_53_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_53_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_53_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_53_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_53_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_53_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_53_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_53_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_53_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_53_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_53_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_53_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_53_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_53_ \
    )(d, l, decl)


/* PUBLIC (54) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_54(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_54_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_54_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_54_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_54 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_54 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_54_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_54(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_54_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_54_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_54_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_54 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_54 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_54_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_54( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_54( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_54( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_54( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_54( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_54\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_54_ \
    )(d, l, decl_traits)

/* PRIVATE (54) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_54_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_54_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_54_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_54_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_54_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_54_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_54_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_54_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_54_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_54_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_54_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_54_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_54_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_54_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_54_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_54_ \
    )(d, l, decl)


/* PUBLIC (55) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_55(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_55_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_55_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_55_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_55 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_55 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_55_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_55(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_55_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_55_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_55_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_55 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_55 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_55_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_55( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_55( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_55( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_55( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_55( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_55\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_55_ \
    )(d, l, decl_traits)

/* PRIVATE (55) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_55_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_55_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_55_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_55_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_55_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_55_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_55_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_55_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_55_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_55_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_55_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_55_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_55_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_55_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_55_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_55_ \
    )(d, l, decl)


/* PUBLIC (56) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_56(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_56_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_56_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_56_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_56 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_56 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_56_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_56(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_56_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_56_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_56_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_56 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_56 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_56_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_56( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_56( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_56( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_56( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_56( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_56\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_56_ \
    )(d, l, decl_traits)

/* PRIVATE (56) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_56_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_56_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_56_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_56_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_56_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_56_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_56_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_56_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_56_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_56_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_56_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_56_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_56_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_56_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_56_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_56_ \
    )(d, l, decl)


/* PUBLIC (57) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_57(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_57_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_57_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_57_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_57 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_57 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_57_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_57(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_57_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_57_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_57_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_57 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_57 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_57_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_57( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_57( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_57( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_57( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_57( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_57\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_57_ \
    )(d, l, decl_traits)

/* PRIVATE (57) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_57_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_57_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_57_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_57_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_57_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_57_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_57_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_57_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_57_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_57_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_57_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_57_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_57_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_57_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_57_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_57_ \
    )(d, l, decl)


/* PUBLIC (58) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_58(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_58_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_58_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_58_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_58 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_58 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_58_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_58(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_58_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_58_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_58_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_58 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_58 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_58_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_58( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_58( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_58( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_58( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_58( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_58\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_58_ \
    )(d, l, decl_traits)

/* PRIVATE (58) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_58_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_58_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_58_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_58_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_58_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_58_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_58_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_58_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_58_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_58_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_58_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_58_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_58_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_58_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_58_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_58_ \
    )(d, l, decl)


/* PUBLIC (59) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_59(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_59_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_59_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_59_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_59 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_59 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_59_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_59(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_59_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_59_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_59_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_59 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_59 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_59_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_59( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_59( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_59( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_59( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_59( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_59\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_59_ \
    )(d, l, decl_traits)

/* PRIVATE (59) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_59_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_59_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_59_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_59_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_59_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_59_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_59_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_59_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_59_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_59_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_59_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_59_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_59_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_59_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_59_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_59_ \
    )(d, l, decl)


/* PUBLIC (60) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_60(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_60_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_60_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_60_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_60 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_60 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_60_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_60(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_60_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_60_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_60_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_60 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_60 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_60_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_60( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_60( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_60( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_60( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_60( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_60\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_60_ \
    )(d, l, decl_traits)

/* PRIVATE (60) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_60_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_60_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_60_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_60_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_60_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_60_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_60_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_60_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_60_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_60_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_60_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_60_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_60_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_60_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_60_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_60_ \
    )(d, l, decl)


/* PUBLIC (61) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_61(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_61_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_61_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_61_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_61 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_61 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_61_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_61(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_61_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_61_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_61_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_61 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_61 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_61_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_61( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_61( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_61( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_61( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_61( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_61\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_61_ \
    )(d, l, decl_traits)

/* PRIVATE (61) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_61_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_61_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_61_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_61_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_61_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_61_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_61_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_61_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_61_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_61_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_61_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_61_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_61_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_61_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_61_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_61_ \
    )(d, l, decl)


/* PUBLIC (62) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_62(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_62_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_62_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_62_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_62 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_62 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_62_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_62(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_62_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_62_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_62_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_62 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_62 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_62_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_62( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_62( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_62( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_62( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_62( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_62\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_62_ \
    )(d, l, decl_traits)

/* PRIVATE (62) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_62_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_62_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_62_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_62_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_62_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_62_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_62_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_62_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_62_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_62_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_62_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_62_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_62_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_62_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_62_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_62_ \
    )(d, l, decl)


/* PUBLIC (63) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_63(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_63_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_63_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_63_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_63 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_63 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_63_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_63(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_63_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_63_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_63_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_63 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_63 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_63_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_63( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_63( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_63( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_63( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_63( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_63\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_63_ \
    )(d, l, decl_traits)

/* PRIVATE (63) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_63_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_63_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_63_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_63_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_63_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_63_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_63_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_63_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_63_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_63_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_63_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_63_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_63_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_63_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_63_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_63_ \
    )(d, l, decl)


/* PUBLIC (64) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_64(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_64_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_64_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_64_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_64 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_64 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_64_ \
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_64(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_64_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_64_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_64_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_64 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_64 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_64_ \
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_64( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , \
        0 \
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_64( \
        d, l, decl) \
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            decl), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \
        1 \
    , \
        0 \
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_64( \
        d, l, decl_traits) \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_64( \
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_64( \
        d, l, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_64\
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_64_ \
    )(d, l, decl_traits)

/* PRIVATE (64) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_64_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_64_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_64_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_64_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_64_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_64_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_64_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_64_(d, l, \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \
                d, decl BOOST_PP_NIL) \
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_64_( \
        d, l, decl, decl_type) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
            0 \
        , \
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \
        ) \
    ) , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_64_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_64_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_64_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_64_ \
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_64_( \
        d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_64_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_64_ \
    )(d, l, decl)


#endif // #include guard
