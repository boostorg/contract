
#ifndef BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run related generation script "if-generate.py".

#include <boost/contract/ext_/preprocessor/traits/assertion/if/cond.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/if/thens.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/if/elses.hpp>
#include <boost/contract/ext_/preprocessor/keyword/else.hpp>
#include <boost/contract/ext_/preprocessor/keyword/static.hpp>

/* PUBLIC */

// Maximum number of nested if-assertions that can be parsed (before pp errors).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_LIMIT 64

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(tokens) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_STATIC_FRONT(tokens), \
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS_ \
    , \
        0 BOOST_PP_TUPLE_EAT(1) \
    )(tokens)

/* PRIVATE */

// Precondition: tokens = `static ...`.
#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS_(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT( \
            tokens BOOST_PP_NIL \
        ) \
    )

/* PUBLIC (1) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_1(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_1_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_1( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_1_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_1( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_1_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_1( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_1_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_1(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_1_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_1( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_1_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_1( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_1_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_1( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_1_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_1( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_1_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (1) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_1_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_1( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_1( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_1( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_1_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_1_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_1_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_1_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_1_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_1_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_1_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_1_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_1_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_1_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_1_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_1_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_1_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_1_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_1_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_1_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_1_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_1_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_1_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_1_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_1_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_1_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_1_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_1_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_1_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_1_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_1_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_1_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_1_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_1_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_1_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_1_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_2( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_1_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_1_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_2(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_1_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_1_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_1_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_1_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_1_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_2, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_2, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_2 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_1_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_1_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_2, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_2, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_2 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_1_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (2) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_2(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_2_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_2( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_2_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_2( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_2_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_2( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_2_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_2(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_2_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_2( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_2_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_2( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_2_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_2( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_2_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_2( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_2_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (2) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_2_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_2( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_2( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_2( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_2_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_2_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_2_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_2_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_2_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_2_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_2_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_2_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_2_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_2_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_2_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_2_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_2_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_2_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_2_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_2_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_2_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_2_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_2_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_2_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_2_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_2_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_2_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_2_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_2_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_2_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_2_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_2_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_2_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_2_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_2_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_2_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_3( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_2_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_2_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_3(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_2_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_2_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_2_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_2_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_2_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_3, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_3, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_3 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_2_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_2_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_3, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_3, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_3 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_2_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (3) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_3(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_3_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_3( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_3_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_3( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_3_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_3( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_3_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_3(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_3_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_3( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_3_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_3( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_3_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_3( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_3_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_3( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_3_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (3) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_3_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_3( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_3( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_3( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_3_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_3_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_3_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_3_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_3_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_3_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_3_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_3_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_3_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_3_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_3_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_3_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_3_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_3_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_3_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_3_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_3_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_3_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_3_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_3_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_3_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_3_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_3_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_3_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_3_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_3_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_3_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_3_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_3_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_3_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_3_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_3_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_4( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_3_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_3_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_4(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_3_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_3_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_3_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_3_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_3_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_4, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_4, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_4 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_3_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_3_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_4, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_4, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_4 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_3_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (4) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_4(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_4_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_4( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_4_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_4( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_4_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_4( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_4_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_4(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_4_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_4( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_4_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_4( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_4_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_4( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_4_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_4( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_4_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (4) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_4_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_4( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_4( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_4( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_4_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_4_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_4_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_4_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_4_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_4_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_4_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_4_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_4_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_4_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_4_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_4_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_4_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_4_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_4_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_4_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_4_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_4_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_4_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_4_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_4_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_4_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_4_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_4_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_4_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_4_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_4_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_4_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_4_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_4_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_4_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_4_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_5( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_4_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_4_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_5(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_4_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_4_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_4_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_4_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_4_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_5, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_5, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_5 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_4_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_4_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_5, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_5, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_5 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_4_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (5) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_5(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_5_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_5( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_5_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_5( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_5_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_5( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_5_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_5(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_5_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_5( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_5_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_5( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_5_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_5( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_5_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_5( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_5_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (5) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_5_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_5( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_5( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_5( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_5_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_5_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_5_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_5_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_5_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_5_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_5_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_5_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_5_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_5_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_5_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_5_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_5_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_5_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_5_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_5_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_5_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_5_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_5_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_5_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_5_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_5_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_5_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_5_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_5_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_5_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_5_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_5_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_5_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_5_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_5_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_5_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_6( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_5_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_5_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_6(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_5_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_5_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_5_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_5_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_5_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_6, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_6, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_6 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_5_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_5_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_6, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_6, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_6 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_5_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (6) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_6(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_6_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_6( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_6_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_6( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_6_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_6( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_6_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_6(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_6_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_6( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_6_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_6( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_6_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_6( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_6_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_6( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_6_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (6) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_6_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_6( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_6( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_6( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_6_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_6_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_6_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_6_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_6_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_6_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_6_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_6_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_6_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_6_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_6_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_6_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_6_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_6_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_6_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_6_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_6_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_6_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_6_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_6_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_6_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_6_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_6_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_6_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_6_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_6_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_6_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_6_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_6_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_6_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_6_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_6_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_7( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_6_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_6_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_7(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_6_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_6_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_6_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_6_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_6_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_7, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_7, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_7 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_6_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_6_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_7, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_7, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_7 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_6_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (7) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_7(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_7_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_7( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_7_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_7( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_7_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_7( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_7_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_7(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_7_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_7( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_7_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_7( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_7_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_7( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_7_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_7( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_7_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (7) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_7_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_7( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_7( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_7( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_7_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_7_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_7_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_7_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_7_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_7_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_7_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_7_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_7_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_7_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_7_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_7_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_7_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_7_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_7_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_7_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_7_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_7_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_7_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_7_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_7_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_7_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_7_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_7_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_7_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_7_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_7_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_7_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_7_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_7_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_7_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_7_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_8( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_7_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_7_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_8(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_7_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_7_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_7_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_7_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_7_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_8, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_8, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_8 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_7_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_7_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_8, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_8, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_8 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_7_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (8) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_8(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_8_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_8( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_8_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_8( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_8_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_8( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_8_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_8(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_8_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_8( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_8_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_8( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_8_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_8( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_8_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_8( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_8_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (8) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_8_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_8( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_8( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_8( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_8_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_8_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_8_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_8_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_8_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_8_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_8_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_8_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_8_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_8_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_8_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_8_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_8_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_8_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_8_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_8_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_8_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_8_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_8_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_8_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_8_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_8_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_8_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_8_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_8_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_8_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_8_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_8_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_8_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_8_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_8_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_8_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_9( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_8_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_8_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_9(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_8_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_8_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_8_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_8_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_8_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_9, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_9, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_9 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_8_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_8_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_9, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_9, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_9 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_8_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (9) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_9(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_9_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_9( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_9_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_9( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_9_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_9( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_9_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_9(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_9_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_9( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_9_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_9( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_9_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_9( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_9_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_9( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_9_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (9) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_9_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_9( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_9( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_9( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_9_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_9_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_9_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_9_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_9_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_9_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_9_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_9_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_9_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_9_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_9_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_9_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_9_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_9_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_9_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_9_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_9_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_9_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_9_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_9_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_9_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_9_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_9_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_9_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_9_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_9_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_9_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_9_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_9_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_9_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_9_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_9_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_10( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_9_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_9_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_10(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_9_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_9_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_9_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_9_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_9_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_10, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_10, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_10 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_9_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_9_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_10, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_10, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_10 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_9_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (10) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_10(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_10_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_10( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_10_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_10( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_10_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_10( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_10_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_10(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_10_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_10( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_10_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_10( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_10_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_10( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_10_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_10( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_10_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (10) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_10_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_10( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_10( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_10( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_10_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_10_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_10_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_10_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_10_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_10_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_10_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_10_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_10_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_10_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_10_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_10_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_10_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_10_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_10_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_10_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_10_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_10_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_10_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_10_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_10_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_10_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_10_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_10_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_10_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_10_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_10_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_10_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_10_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_10_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_10_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_10_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_11( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_10_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_10_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_11(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_10_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_10_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_10_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_10_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_10_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_11, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_11, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_11 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_10_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_10_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_11, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_11, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_11 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_10_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (11) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_11(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_11_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_11( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_11_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_11( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_11_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_11( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_11_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_11(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_11_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_11( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_11_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_11( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_11_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_11( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_11_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_11( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_11_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (11) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_11_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_11( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_11( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_11( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_11_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_11_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_11_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_11_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_11_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_11_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_11_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_11_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_11_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_11_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_11_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_11_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_11_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_11_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_11_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_11_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_11_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_11_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_11_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_11_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_11_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_11_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_11_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_11_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_11_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_11_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_11_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_11_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_11_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_11_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_11_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_11_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_12( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_11_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_11_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_12(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_11_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_11_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_11_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_11_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_11_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_12, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_12, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_12 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_11_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_11_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_12, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_12, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_12 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_11_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (12) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_12(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_12_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_12( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_12_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_12( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_12_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_12( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_12_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_12(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_12_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_12( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_12_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_12( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_12_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_12( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_12_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_12( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_12_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (12) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_12_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_12( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_12( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_12( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_12_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_12_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_12_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_12_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_12_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_12_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_12_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_12_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_12_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_12_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_12_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_12_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_12_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_12_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_12_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_12_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_12_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_12_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_12_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_12_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_12_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_12_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_12_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_12_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_12_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_12_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_12_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_12_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_12_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_12_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_12_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_12_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_13( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_12_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_12_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_13(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_12_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_12_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_12_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_12_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_12_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_13, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_13, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_13 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_12_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_12_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_13, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_13, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_13 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_12_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (13) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_13(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_13_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_13( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_13_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_13( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_13_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_13( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_13_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_13(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_13_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_13( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_13_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_13( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_13_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_13( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_13_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_13( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_13_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (13) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_13_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_13( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_13( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_13( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_13_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_13_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_13_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_13_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_13_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_13_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_13_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_13_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_13_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_13_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_13_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_13_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_13_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_13_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_13_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_13_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_13_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_13_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_13_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_13_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_13_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_13_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_13_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_13_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_13_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_13_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_13_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_13_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_13_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_13_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_13_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_13_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_14( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_13_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_13_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_14(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_13_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_13_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_13_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_13_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_13_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_14, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_14, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_14 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_13_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_13_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_14, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_14, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_14 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_13_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (14) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_14(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_14_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_14( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_14_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_14( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_14_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_14( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_14_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_14(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_14_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_14( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_14_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_14( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_14_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_14( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_14_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_14( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_14_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (14) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_14_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_14( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_14( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_14( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_14_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_14_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_14_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_14_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_14_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_14_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_14_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_14_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_14_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_14_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_14_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_14_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_14_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_14_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_14_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_14_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_14_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_14_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_14_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_14_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_14_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_14_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_14_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_14_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_14_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_14_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_14_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_14_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_14_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_14_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_14_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_14_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_15( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_14_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_14_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_15(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_14_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_14_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_14_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_14_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_14_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_15, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_15, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_15 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_14_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_14_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_15, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_15, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_15 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_14_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (15) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_15(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_15_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_15( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_15_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_15( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_15_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_15( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_15_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_15(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_15_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_15( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_15_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_15( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_15_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_15( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_15_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_15( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_15_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (15) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_15_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_15( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_15( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_15( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_15_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_15_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_15_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_15_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_15_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_15_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_15_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_15_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_15_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_15_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_15_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_15_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_15_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_15_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_15_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_15_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_15_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_15_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_15_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_15_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_15_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_15_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_15_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_15_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_15_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_15_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_15_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_15_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_15_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_15_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_15_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_15_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_16( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_15_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_15_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_16(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_15_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_15_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_15_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_15_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_15_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_16, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_16, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_16 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_15_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_15_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_16, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_16, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_16 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_15_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (16) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_16(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_16_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_16( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_16_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_16( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_16_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_16( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_16_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_16(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_16_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_16( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_16_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_16( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_16_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_16( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_16_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_16( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_16_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (16) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_16_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_16( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_16( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_16( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_16_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_16_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_16_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_16_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_16_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_16_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_16_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_16_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_16_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_16_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_16_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_16_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_16_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_16_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_16_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_16_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_16_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_16_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_16_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_16_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_16_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_16_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_16_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_16_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_16_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_16_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_16_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_16_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_16_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_16_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_16_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_16_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_17( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_16_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_16_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_17(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_16_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_16_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_16_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_16_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_16_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_17, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_17, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_17 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_16_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_16_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_17, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_17, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_17 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_16_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (17) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_17(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_17_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_17( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_17_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_17( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_17_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_17( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_17_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_17(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_17_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_17( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_17_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_17( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_17_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_17( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_17_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_17( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_17_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (17) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_17_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_17( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_17( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_17( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_17_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_17_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_17_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_17_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_17_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_17_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_17_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_17_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_17_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_17_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_17_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_17_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_17_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_17_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_17_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_17_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_17_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_17_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_17_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_17_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_17_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_17_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_17_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_17_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_17_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_17_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_17_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_17_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_17_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_17_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_17_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_17_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_18( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_17_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_17_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_18(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_17_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_17_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_17_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_17_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_17_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_18, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_18, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_18 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_17_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_17_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_18, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_18, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_18 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_17_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (18) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_18(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_18_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_18( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_18_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_18( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_18_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_18( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_18_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_18(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_18_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_18( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_18_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_18( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_18_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_18( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_18_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_18( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_18_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (18) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_18_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_18( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_18( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_18( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_18_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_18_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_18_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_18_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_18_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_18_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_18_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_18_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_18_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_18_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_18_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_18_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_18_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_18_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_18_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_18_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_18_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_18_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_18_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_18_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_18_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_18_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_18_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_18_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_18_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_18_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_18_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_18_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_18_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_18_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_18_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_18_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_19( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_18_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_18_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_19(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_18_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_18_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_18_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_18_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_18_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_19, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_19, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_19 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_18_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_18_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_19, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_19, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_19 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_18_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (19) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_19(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_19_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_19( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_19_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_19( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_19_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_19( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_19_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_19(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_19_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_19( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_19_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_19( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_19_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_19( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_19_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_19( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_19_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (19) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_19_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_19( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_19( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_19( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_19_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_19_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_19_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_19_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_19_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_19_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_19_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_19_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_19_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_19_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_19_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_19_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_19_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_19_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_19_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_19_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_19_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_19_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_19_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_19_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_19_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_19_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_19_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_19_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_19_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_19_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_19_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_19_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_19_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_19_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_19_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_19_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_20( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_19_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_19_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_20(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_19_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_19_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_19_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_19_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_19_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_20, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_20, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_20 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_19_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_19_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_20, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_20, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_20 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_19_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (20) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_20(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_20_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_20( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_20_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_20( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_20_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_20( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_20_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_20(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_20_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_20( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_20_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_20( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_20_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_20( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_20_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_20( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_20_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (20) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_20_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_20( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_20( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_20( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_20_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_20_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_20_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_20_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_20_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_20_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_20_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_20_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_20_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_20_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_20_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_20_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_20_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_20_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_20_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_20_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_20_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_20_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_20_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_20_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_20_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_20_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_20_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_20_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_20_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_20_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_20_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_20_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_20_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_20_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_20_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_20_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_21( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_20_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_20_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_21(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_20_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_20_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_20_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_20_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_20_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_21, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_21, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_21 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_20_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_20_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_21, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_21, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_21 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_20_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (21) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_21(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_21_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_21( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_21_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_21( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_21_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_21( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_21_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_21(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_21_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_21( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_21_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_21( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_21_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_21( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_21_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_21( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_21_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (21) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_21_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_21( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_21( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_21( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_21_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_21_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_21_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_21_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_21_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_21_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_21_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_21_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_21_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_21_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_21_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_21_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_21_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_21_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_21_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_21_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_21_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_21_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_21_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_21_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_21_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_21_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_21_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_21_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_21_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_21_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_21_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_21_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_21_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_21_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_21_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_21_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_22( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_21_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_21_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_22(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_21_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_21_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_21_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_21_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_21_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_22, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_22, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_22 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_21_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_21_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_22, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_22, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_22 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_21_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (22) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_22(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_22_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_22( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_22_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_22( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_22_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_22( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_22_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_22(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_22_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_22( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_22_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_22( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_22_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_22( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_22_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_22( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_22_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (22) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_22_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_22( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_22( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_22( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_22_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_22_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_22_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_22_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_22_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_22_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_22_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_22_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_22_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_22_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_22_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_22_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_22_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_22_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_22_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_22_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_22_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_22_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_22_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_22_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_22_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_22_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_22_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_22_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_22_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_22_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_22_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_22_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_22_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_22_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_22_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_22_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_23( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_22_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_22_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_23(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_22_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_22_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_22_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_22_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_22_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_23, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_23, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_23 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_22_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_22_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_23, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_23, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_23 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_22_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (23) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_23(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_23_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_23( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_23_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_23( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_23_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_23( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_23_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_23(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_23_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_23( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_23_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_23( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_23_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_23( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_23_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_23( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_23_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (23) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_23_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_23( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_23( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_23( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_23_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_23_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_23_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_23_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_23_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_23_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_23_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_23_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_23_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_23_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_23_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_23_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_23_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_23_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_23_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_23_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_23_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_23_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_23_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_23_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_23_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_23_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_23_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_23_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_23_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_23_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_23_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_23_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_23_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_23_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_23_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_23_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_24( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_23_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_23_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_24(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_23_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_23_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_23_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_23_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_23_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_24, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_24, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_24 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_23_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_23_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_24, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_24, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_24 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_23_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (24) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_24(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_24_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_24( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_24_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_24( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_24_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_24( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_24_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_24(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_24_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_24( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_24_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_24( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_24_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_24( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_24_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_24( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_24_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (24) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_24_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_24( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_24( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_24( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_24_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_24_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_24_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_24_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_24_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_24_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_24_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_24_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_24_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_24_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_24_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_24_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_24_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_24_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_24_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_24_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_24_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_24_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_24_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_24_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_24_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_24_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_24_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_24_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_24_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_24_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_24_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_24_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_24_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_24_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_24_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_24_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_25( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_24_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_24_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_25(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_24_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_24_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_24_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_24_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_24_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_25, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_25, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_25 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_24_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_24_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_25, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_25, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_25 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_24_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (25) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_25(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_25_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_25( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_25_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_25( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_25_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_25( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_25_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_25(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_25_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_25( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_25_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_25( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_25_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_25( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_25_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_25( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_25_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (25) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_25_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_25( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_25( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_25( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_25_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_25_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_25_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_25_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_25_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_25_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_25_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_25_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_25_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_25_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_25_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_25_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_25_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_25_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_25_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_25_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_25_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_25_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_25_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_25_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_25_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_25_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_25_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_25_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_25_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_25_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_25_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_25_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_25_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_25_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_25_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_25_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_26( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_25_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_25_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_26(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_25_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_25_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_25_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_25_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_25_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_26, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_26, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_26 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_25_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_25_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_26, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_26, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_26 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_25_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (26) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_26(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_26_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_26( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_26_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_26( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_26_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_26( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_26_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_26(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_26_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_26( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_26_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_26( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_26_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_26( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_26_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_26( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_26_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (26) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_26_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_26( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_26( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_26( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_26_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_26_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_26_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_26_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_26_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_26_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_26_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_26_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_26_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_26_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_26_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_26_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_26_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_26_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_26_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_26_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_26_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_26_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_26_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_26_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_26_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_26_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_26_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_26_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_26_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_26_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_26_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_26_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_26_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_26_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_26_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_26_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_27( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_26_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_26_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_27(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_26_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_26_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_26_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_26_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_26_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_27, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_27, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_27 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_26_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_26_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_27, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_27, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_27 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_26_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (27) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_27(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_27_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_27( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_27_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_27( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_27_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_27( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_27_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_27(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_27_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_27( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_27_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_27( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_27_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_27( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_27_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_27( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_27_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (27) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_27_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_27( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_27( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_27( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_27_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_27_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_27_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_27_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_27_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_27_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_27_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_27_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_27_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_27_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_27_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_27_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_27_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_27_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_27_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_27_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_27_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_27_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_27_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_27_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_27_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_27_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_27_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_27_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_27_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_27_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_27_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_27_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_27_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_27_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_27_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_27_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_28( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_27_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_27_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_28(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_27_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_27_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_27_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_27_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_27_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_28, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_28, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_28 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_27_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_27_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_28, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_28, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_28 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_27_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (28) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_28(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_28_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_28( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_28_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_28( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_28_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_28( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_28_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_28(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_28_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_28( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_28_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_28( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_28_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_28( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_28_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_28( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_28_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (28) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_28_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_28( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_28( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_28( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_28_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_28_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_28_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_28_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_28_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_28_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_28_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_28_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_28_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_28_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_28_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_28_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_28_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_28_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_28_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_28_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_28_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_28_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_28_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_28_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_28_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_28_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_28_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_28_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_28_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_28_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_28_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_28_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_28_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_28_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_28_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_28_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_29( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_28_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_28_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_29(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_28_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_28_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_28_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_28_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_28_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_29, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_29, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_29 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_28_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_28_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_29, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_29, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_29 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_28_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (29) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_29(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_29_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_29( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_29_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_29( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_29_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_29( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_29_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_29(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_29_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_29( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_29_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_29( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_29_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_29( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_29_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_29( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_29_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (29) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_29_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_29( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_29( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_29( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_29_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_29_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_29_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_29_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_29_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_29_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_29_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_29_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_29_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_29_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_29_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_29_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_29_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_29_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_29_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_29_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_29_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_29_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_29_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_29_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_29_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_29_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_29_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_29_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_29_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_29_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_29_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_29_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_29_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_29_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_29_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_29_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_30( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_29_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_29_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_30(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_29_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_29_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_29_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_29_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_29_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_30, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_30, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_30 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_29_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_29_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_30, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_30, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_30 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_29_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (30) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_30(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_30_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_30( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_30_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_30( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_30_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_30( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_30_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_30(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_30_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_30( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_30_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_30( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_30_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_30( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_30_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_30( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_30_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (30) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_30_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_30( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_30( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_30( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_30_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_30_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_30_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_30_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_30_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_30_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_30_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_30_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_30_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_30_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_30_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_30_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_30_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_30_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_30_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_30_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_30_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_30_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_30_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_30_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_30_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_30_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_30_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_30_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_30_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_30_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_30_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_30_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_30_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_30_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_30_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_30_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_31( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_30_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_30_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_31(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_30_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_30_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_30_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_30_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_30_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_31, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_31, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_31 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_30_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_30_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_31, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_31, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_31 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_30_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (31) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_31(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_31_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_31( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_31_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_31( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_31_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_31( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_31_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_31(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_31_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_31( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_31_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_31( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_31_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_31( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_31_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_31( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_31_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (31) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_31_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_31( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_31( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_31( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_31_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_31_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_31_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_31_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_31_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_31_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_31_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_31_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_31_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_31_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_31_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_31_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_31_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_31_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_31_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_31_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_31_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_31_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_31_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_31_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_31_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_31_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_31_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_31_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_31_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_31_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_31_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_31_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_31_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_31_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_31_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_31_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_32( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_31_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_31_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_32(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_31_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_31_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_31_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_31_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_31_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_32, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_32, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_32 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_31_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_31_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_32, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_32, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_32 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_31_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (32) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_32(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_32_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_32( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_32_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_32( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_32_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_32( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_32_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_32(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_32_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_32( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_32_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_32( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_32_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_32( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_32_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_32( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_32_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (32) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_32_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_32( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_32( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_32( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_32_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_32_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_32_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_32_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_32_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_32_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_32_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_32_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_32_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_32_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_32_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_32_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_32_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_32_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_32_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_32_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_32_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_32_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_32_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_32_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_32_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_32_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_32_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_32_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_32_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_32_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_32_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_32_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_32_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_32_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_32_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_32_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_33( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_32_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_32_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_33(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_32_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_32_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_32_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_32_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_32_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_33, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_33, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_33 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_32_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_32_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_33, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_33, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_33 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_32_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (33) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_33(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_33_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_33( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_33_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_33( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_33_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_33( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_33_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_33(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_33_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_33( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_33_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_33( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_33_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_33( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_33_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_33( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_33_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (33) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_33_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_33( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_33( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_33( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_33_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_33_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_33_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_33_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_33_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_33_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_33_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_33_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_33_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_33_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_33_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_33_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_33_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_33_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_33_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_33_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_33_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_33_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_33_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_33_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_33_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_33_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_33_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_33_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_33_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_33_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_33_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_33_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_33_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_33_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_33_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_33_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_34( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_33_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_33_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_34(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_33_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_33_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_33_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_33_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_33_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_34, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_34, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_34 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_33_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_33_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_34, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_34, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_34 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_33_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (34) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_34(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_34_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_34( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_34_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_34( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_34_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_34( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_34_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_34(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_34_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_34( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_34_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_34( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_34_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_34( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_34_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_34( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_34_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (34) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_34_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_34( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_34( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_34( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_34_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_34_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_34_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_34_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_34_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_34_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_34_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_34_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_34_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_34_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_34_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_34_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_34_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_34_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_34_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_34_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_34_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_34_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_34_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_34_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_34_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_34_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_34_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_34_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_34_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_34_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_34_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_34_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_34_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_34_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_34_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_34_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_35( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_34_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_34_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_35(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_34_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_34_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_34_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_34_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_34_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_35, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_35, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_35 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_34_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_34_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_35, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_35, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_35 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_34_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (35) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_35(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_35_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_35( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_35_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_35( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_35_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_35( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_35_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_35(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_35_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_35( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_35_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_35( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_35_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_35( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_35_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_35( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_35_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (35) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_35_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_35( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_35( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_35( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_35_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_35_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_35_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_35_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_35_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_35_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_35_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_35_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_35_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_35_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_35_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_35_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_35_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_35_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_35_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_35_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_35_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_35_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_35_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_35_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_35_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_35_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_35_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_35_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_35_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_35_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_35_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_35_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_35_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_35_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_35_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_35_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_36( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_35_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_35_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_36(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_35_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_35_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_35_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_35_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_35_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_36, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_36, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_36 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_35_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_35_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_36, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_36, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_36 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_35_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (36) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_36(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_36_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_36( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_36_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_36( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_36_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_36( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_36_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_36(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_36_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_36( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_36_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_36( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_36_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_36( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_36_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_36( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_36_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (36) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_36_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_36( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_36( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_36( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_36_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_36_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_36_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_36_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_36_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_36_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_36_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_36_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_36_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_36_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_36_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_36_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_36_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_36_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_36_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_36_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_36_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_36_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_36_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_36_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_36_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_36_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_36_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_36_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_36_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_36_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_36_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_36_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_36_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_36_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_36_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_36_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_37( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_36_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_36_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_37(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_36_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_36_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_36_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_36_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_36_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_37, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_37, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_37 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_36_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_36_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_37, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_37, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_37 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_36_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (37) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_37(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_37_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_37( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_37_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_37( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_37_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_37( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_37_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_37(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_37_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_37( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_37_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_37( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_37_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_37( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_37_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_37( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_37_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (37) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_37_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_37( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_37( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_37( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_37_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_37_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_37_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_37_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_37_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_37_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_37_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_37_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_37_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_37_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_37_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_37_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_37_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_37_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_37_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_37_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_37_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_37_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_37_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_37_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_37_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_37_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_37_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_37_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_37_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_37_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_37_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_37_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_37_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_37_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_37_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_37_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_38( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_37_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_37_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_38(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_37_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_37_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_37_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_37_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_37_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_38, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_38, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_38 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_37_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_37_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_38, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_38, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_38 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_37_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (38) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_38(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_38_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_38( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_38_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_38( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_38_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_38( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_38_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_38(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_38_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_38( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_38_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_38( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_38_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_38( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_38_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_38( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_38_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (38) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_38_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_38( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_38( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_38( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_38_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_38_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_38_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_38_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_38_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_38_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_38_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_38_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_38_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_38_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_38_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_38_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_38_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_38_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_38_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_38_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_38_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_38_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_38_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_38_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_38_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_38_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_38_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_38_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_38_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_38_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_38_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_38_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_38_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_38_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_38_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_38_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_39( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_38_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_38_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_39(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_38_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_38_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_38_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_38_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_38_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_39, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_39, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_39 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_38_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_38_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_39, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_39, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_39 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_38_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (39) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_39(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_39_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_39( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_39_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_39( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_39_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_39( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_39_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_39(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_39_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_39( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_39_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_39( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_39_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_39( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_39_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_39( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_39_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (39) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_39_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_39( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_39( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_39( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_39_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_39_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_39_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_39_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_39_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_39_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_39_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_39_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_39_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_39_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_39_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_39_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_39_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_39_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_39_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_39_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_39_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_39_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_39_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_39_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_39_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_39_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_39_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_39_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_39_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_39_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_39_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_39_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_39_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_39_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_39_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_39_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_40( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_39_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_39_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_40(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_39_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_39_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_39_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_39_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_39_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_40, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_40, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_40 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_39_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_39_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_40, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_40, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_40 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_39_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (40) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_40(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_40_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_40( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_40_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_40( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_40_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_40( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_40_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_40(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_40_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_40( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_40_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_40( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_40_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_40( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_40_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_40( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_40_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (40) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_40_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_40( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_40( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_40( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_40_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_40_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_40_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_40_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_40_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_40_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_40_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_40_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_40_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_40_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_40_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_40_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_40_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_40_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_40_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_40_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_40_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_40_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_40_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_40_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_40_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_40_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_40_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_40_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_40_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_40_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_40_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_40_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_40_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_40_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_40_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_40_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_41( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_40_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_40_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_41(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_40_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_40_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_40_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_40_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_40_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_41, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_41, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_41 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_40_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_40_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_41, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_41, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_41 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_40_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (41) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_41(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_41_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_41( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_41_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_41( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_41_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_41( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_41_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_41(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_41_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_41( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_41_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_41( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_41_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_41( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_41_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_41( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_41_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (41) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_41_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_41( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_41( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_41( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_41_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_41_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_41_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_41_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_41_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_41_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_41_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_41_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_41_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_41_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_41_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_41_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_41_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_41_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_41_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_41_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_41_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_41_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_41_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_41_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_41_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_41_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_41_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_41_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_41_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_41_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_41_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_41_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_41_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_41_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_41_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_41_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_42( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_41_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_41_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_42(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_41_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_41_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_41_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_41_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_41_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_42, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_42, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_42 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_41_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_41_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_42, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_42, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_42 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_41_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (42) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_42(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_42_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_42( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_42_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_42( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_42_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_42( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_42_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_42(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_42_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_42( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_42_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_42( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_42_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_42( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_42_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_42( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_42_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (42) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_42_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_42( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_42( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_42( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_42_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_42_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_42_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_42_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_42_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_42_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_42_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_42_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_42_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_42_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_42_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_42_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_42_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_42_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_42_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_42_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_42_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_42_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_42_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_42_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_42_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_42_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_42_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_42_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_42_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_42_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_42_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_42_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_42_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_42_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_42_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_42_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_43( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_42_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_42_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_43(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_42_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_42_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_42_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_42_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_42_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_43, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_43, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_43 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_42_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_42_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_43, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_43, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_43 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_42_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (43) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_43(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_43_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_43( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_43_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_43( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_43_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_43( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_43_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_43(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_43_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_43( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_43_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_43( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_43_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_43( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_43_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_43( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_43_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (43) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_43_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_43( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_43( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_43( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_43_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_43_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_43_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_43_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_43_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_43_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_43_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_43_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_43_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_43_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_43_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_43_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_43_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_43_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_43_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_43_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_43_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_43_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_43_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_43_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_43_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_43_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_43_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_43_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_43_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_43_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_43_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_43_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_43_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_43_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_43_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_43_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_44( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_43_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_43_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_44(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_43_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_43_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_43_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_43_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_43_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_44, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_44, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_44 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_43_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_43_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_44, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_44, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_44 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_43_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (44) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_44(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_44_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_44( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_44_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_44( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_44_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_44( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_44_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_44(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_44_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_44( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_44_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_44( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_44_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_44( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_44_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_44( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_44_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (44) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_44_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_44( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_44( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_44( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_44_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_44_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_44_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_44_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_44_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_44_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_44_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_44_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_44_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_44_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_44_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_44_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_44_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_44_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_44_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_44_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_44_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_44_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_44_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_44_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_44_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_44_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_44_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_44_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_44_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_44_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_44_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_44_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_44_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_44_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_44_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_44_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_45( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_44_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_44_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_45(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_44_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_44_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_44_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_44_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_44_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_45, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_45, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_45 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_44_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_44_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_45, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_45, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_45 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_44_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (45) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_45(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_45_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_45( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_45_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_45( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_45_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_45( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_45_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_45(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_45_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_45( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_45_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_45( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_45_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_45( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_45_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_45( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_45_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (45) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_45_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_45( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_45( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_45( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_45_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_45_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_45_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_45_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_45_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_45_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_45_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_45_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_45_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_45_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_45_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_45_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_45_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_45_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_45_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_45_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_45_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_45_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_45_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_45_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_45_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_45_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_45_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_45_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_45_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_45_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_45_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_45_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_45_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_45_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_45_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_45_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_46( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_45_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_45_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_46(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_45_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_45_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_45_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_45_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_45_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_46, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_46, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_46 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_45_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_45_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_46, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_46, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_46 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_45_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (46) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_46(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_46_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_46( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_46_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_46( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_46_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_46( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_46_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_46(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_46_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_46( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_46_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_46( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_46_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_46( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_46_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_46( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_46_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (46) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_46_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_46( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_46( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_46( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_46_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_46_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_46_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_46_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_46_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_46_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_46_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_46_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_46_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_46_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_46_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_46_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_46_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_46_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_46_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_46_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_46_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_46_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_46_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_46_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_46_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_46_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_46_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_46_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_46_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_46_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_46_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_46_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_46_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_46_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_46_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_46_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_47( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_46_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_46_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_47(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_46_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_46_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_46_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_46_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_46_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_47, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_47, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_47 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_46_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_46_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_47, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_47, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_47 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_46_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (47) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_47(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_47_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_47( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_47_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_47( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_47_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_47( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_47_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_47(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_47_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_47( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_47_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_47( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_47_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_47( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_47_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_47( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_47_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (47) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_47_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_47( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_47( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_47( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_47_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_47_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_47_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_47_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_47_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_47_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_47_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_47_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_47_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_47_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_47_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_47_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_47_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_47_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_47_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_47_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_47_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_47_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_47_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_47_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_47_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_47_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_47_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_47_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_47_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_47_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_47_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_47_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_47_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_47_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_47_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_47_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_48( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_47_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_47_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_48(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_47_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_47_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_47_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_47_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_47_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_48, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_48, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_48 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_47_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_47_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_48, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_48, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_48 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_47_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (48) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_48(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_48_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_48( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_48_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_48( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_48_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_48( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_48_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_48(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_48_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_48( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_48_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_48( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_48_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_48( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_48_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_48( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_48_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (48) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_48_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_48( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_48( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_48( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_48_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_48_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_48_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_48_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_48_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_48_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_48_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_48_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_48_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_48_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_48_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_48_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_48_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_48_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_48_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_48_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_48_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_48_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_48_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_48_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_48_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_48_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_48_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_48_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_48_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_48_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_48_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_48_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_48_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_48_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_48_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_48_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_49( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_48_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_48_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_49(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_48_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_48_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_48_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_48_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_48_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_49, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_49, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_49 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_48_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_48_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_49, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_49, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_49 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_48_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (49) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_49(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_49_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_49( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_49_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_49( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_49_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_49( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_49_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_49(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_49_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_49( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_49_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_49( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_49_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_49( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_49_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_49( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_49_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (49) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_49_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_49( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_49( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_49( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_49_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_49_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_49_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_49_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_49_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_49_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_49_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_49_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_49_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_49_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_49_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_49_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_49_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_49_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_49_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_49_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_49_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_49_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_49_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_49_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_49_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_49_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_49_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_49_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_49_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_49_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_49_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_49_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_49_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_49_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_49_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_49_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_50( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_49_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_49_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_50(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_49_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_49_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_49_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_49_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_49_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_50, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_50, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_50 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_49_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_49_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_50, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_50, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_50 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_49_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (50) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_50(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_50_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_50( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_50_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_50( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_50_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_50( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_50_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_50(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_50_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_50( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_50_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_50( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_50_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_50( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_50_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_50( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_50_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (50) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_50_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_50( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_50( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_50( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_50_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_50_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_50_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_50_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_50_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_50_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_50_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_50_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_50_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_50_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_50_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_50_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_50_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_50_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_50_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_50_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_50_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_50_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_50_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_50_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_50_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_50_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_50_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_50_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_50_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_50_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_50_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_50_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_50_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_50_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_50_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_50_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_51( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_50_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_50_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_51(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_50_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_50_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_50_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_50_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_50_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_51, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_51, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_51 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_50_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_50_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_51, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_51, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_51 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_50_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (51) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_51(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_51_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_51( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_51_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_51( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_51_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_51( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_51_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_51(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_51_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_51( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_51_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_51( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_51_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_51( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_51_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_51( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_51_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (51) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_51_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_51( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_51( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_51( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_51_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_51_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_51_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_51_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_51_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_51_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_51_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_51_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_51_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_51_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_51_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_51_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_51_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_51_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_51_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_51_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_51_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_51_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_51_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_51_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_51_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_51_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_51_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_51_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_51_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_51_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_51_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_51_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_51_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_51_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_51_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_51_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_52( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_51_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_51_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_52(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_51_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_51_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_51_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_51_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_51_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_52, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_52, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_52 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_51_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_51_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_52, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_52, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_52 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_51_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (52) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_52(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_52_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_52( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_52_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_52( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_52_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_52( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_52_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_52(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_52_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_52( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_52_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_52( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_52_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_52( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_52_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_52( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_52_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (52) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_52_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_52( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_52( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_52( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_52_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_52_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_52_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_52_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_52_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_52_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_52_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_52_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_52_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_52_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_52_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_52_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_52_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_52_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_52_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_52_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_52_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_52_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_52_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_52_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_52_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_52_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_52_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_52_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_52_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_52_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_52_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_52_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_52_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_52_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_52_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_52_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_53( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_52_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_52_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_53(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_52_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_52_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_52_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_52_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_52_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_53, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_53, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_53 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_52_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_52_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_53, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_53, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_53 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_52_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (53) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_53(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_53_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_53( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_53_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_53( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_53_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_53( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_53_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_53(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_53_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_53( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_53_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_53( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_53_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_53( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_53_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_53( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_53_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (53) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_53_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_53( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_53( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_53( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_53_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_53_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_53_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_53_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_53_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_53_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_53_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_53_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_53_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_53_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_53_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_53_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_53_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_53_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_53_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_53_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_53_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_53_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_53_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_53_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_53_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_53_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_53_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_53_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_53_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_53_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_53_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_53_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_53_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_53_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_53_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_53_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_54( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_53_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_53_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_54(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_53_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_53_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_53_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_53_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_53_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_54, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_54, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_54 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_53_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_53_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_54, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_54, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_54 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_53_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (54) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_54(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_54_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_54( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_54_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_54( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_54_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_54( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_54_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_54(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_54_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_54( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_54_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_54( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_54_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_54( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_54_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_54( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_54_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (54) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_54_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_54( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_54( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_54( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_54_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_54_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_54_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_54_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_54_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_54_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_54_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_54_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_54_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_54_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_54_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_54_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_54_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_54_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_54_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_54_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_54_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_54_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_54_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_54_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_54_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_54_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_54_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_54_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_54_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_54_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_54_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_54_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_54_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_54_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_54_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_54_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_55( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_54_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_54_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_55(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_54_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_54_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_54_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_54_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_54_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_55, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_55, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_55 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_54_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_54_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_55, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_55, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_55 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_54_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (55) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_55(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_55_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_55( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_55_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_55( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_55_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_55( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_55_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_55(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_55_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_55( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_55_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_55( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_55_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_55( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_55_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_55( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_55_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (55) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_55_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_55( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_55( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_55( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_55_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_55_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_55_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_55_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_55_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_55_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_55_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_55_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_55_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_55_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_55_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_55_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_55_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_55_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_55_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_55_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_55_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_55_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_55_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_55_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_55_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_55_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_55_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_55_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_55_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_55_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_55_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_55_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_55_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_55_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_55_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_55_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_56( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_55_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_55_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_56(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_55_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_55_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_55_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_55_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_55_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_56, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_56, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_56 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_55_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_55_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_56, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_56, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_56 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_55_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (56) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_56(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_56_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_56( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_56_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_56( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_56_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_56( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_56_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_56(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_56_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_56( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_56_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_56( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_56_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_56( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_56_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_56( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_56_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (56) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_56_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_56( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_56( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_56( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_56_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_56_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_56_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_56_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_56_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_56_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_56_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_56_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_56_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_56_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_56_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_56_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_56_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_56_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_56_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_56_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_56_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_56_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_56_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_56_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_56_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_56_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_56_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_56_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_56_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_56_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_56_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_56_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_56_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_56_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_56_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_56_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_57( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_56_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_56_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_57(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_56_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_56_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_56_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_56_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_56_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_57, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_57, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_57 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_56_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_56_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_57, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_57, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_57 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_56_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (57) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_57(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_57_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_57( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_57_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_57( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_57_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_57( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_57_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_57(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_57_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_57( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_57_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_57( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_57_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_57( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_57_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_57( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_57_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (57) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_57_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_57( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_57( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_57( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_57_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_57_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_57_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_57_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_57_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_57_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_57_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_57_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_57_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_57_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_57_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_57_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_57_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_57_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_57_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_57_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_57_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_57_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_57_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_57_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_57_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_57_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_57_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_57_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_57_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_57_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_57_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_57_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_57_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_57_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_57_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_57_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_58( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_57_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_57_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_58(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_57_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_57_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_57_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_57_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_57_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_58, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_58, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_58 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_57_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_57_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_58, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_58, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_58 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_57_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (58) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_58(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_58_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_58( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_58_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_58( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_58_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_58( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_58_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_58(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_58_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_58( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_58_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_58( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_58_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_58( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_58_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_58( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_58_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (58) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_58_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_58( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_58( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_58( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_58_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_58_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_58_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_58_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_58_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_58_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_58_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_58_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_58_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_58_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_58_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_58_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_58_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_58_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_58_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_58_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_58_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_58_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_58_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_58_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_58_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_58_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_58_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_58_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_58_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_58_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_58_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_58_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_58_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_58_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_58_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_58_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_59( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_58_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_58_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_59(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_58_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_58_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_58_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_58_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_58_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_59, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_59, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_59 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_58_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_58_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_59, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_59, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_59 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_58_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (59) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_59(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_59_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_59( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_59_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_59( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_59_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_59( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_59_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_59(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_59_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_59( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_59_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_59( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_59_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_59( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_59_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_59( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_59_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (59) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_59_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_59( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_59( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_59( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_59_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_59_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_59_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_59_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_59_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_59_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_59_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_59_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_59_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_59_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_59_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_59_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_59_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_59_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_59_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_59_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_59_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_59_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_59_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_59_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_59_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_59_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_59_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_59_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_59_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_59_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_59_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_59_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_59_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_59_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_59_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_59_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_60( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_59_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_59_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_60(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_59_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_59_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_59_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_59_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_59_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_60, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_60, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_60 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_59_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_59_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_60, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_60, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_60 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_59_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (60) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_60(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_60_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_60( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_60_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_60( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_60_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_60( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_60_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_60(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_60_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_60( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_60_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_60( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_60_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_60( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_60_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_60( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_60_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (60) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_60_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_60( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_60( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_60( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_60_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_60_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_60_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_60_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_60_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_60_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_60_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_60_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_60_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_60_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_60_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_60_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_60_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_60_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_60_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_60_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_60_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_60_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_60_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_60_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_60_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_60_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_60_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_60_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_60_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_60_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_60_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_60_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_60_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_60_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_60_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_60_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_61( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_60_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_60_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_61(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_60_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_60_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_60_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_60_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_60_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_61, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_61, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_61 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_60_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_60_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_61, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_61, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_61 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_60_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (61) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_61(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_61_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_61( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_61_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_61( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_61_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_61( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_61_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_61(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_61_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_61( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_61_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_61( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_61_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_61( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_61_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_61( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_61_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (61) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_61_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_61( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_61( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_61( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_61_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_61_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_61_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_61_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_61_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_61_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_61_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_61_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_61_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_61_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_61_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_61_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_61_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_61_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_61_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_61_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_61_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_61_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_61_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_61_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_61_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_61_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_61_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_61_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_61_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_61_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_61_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_61_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_61_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_61_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_61_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_61_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_62( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_61_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_61_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_62(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_61_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_61_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_61_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_61_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_61_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_62, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_62, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_62 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_61_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_61_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_62, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_62, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_62 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_61_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (62) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_62(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_62_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_62( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_62_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_62( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_62_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_62( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_62_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_62(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_62_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_62( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_62_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_62( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_62_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_62( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_62_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_62( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_62_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (62) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_62_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_62( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_62( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_62( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_62_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_62_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_62_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_62_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_62_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_62_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_62_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_62_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_62_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_62_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_62_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_62_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_62_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_62_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_62_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_62_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_62_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_62_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_62_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_62_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_62_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_62_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_62_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_62_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_62_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_62_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_62_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_62_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_62_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_62_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_62_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_62_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_63( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_62_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_62_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_63(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_62_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_62_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_62_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_62_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_62_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_63, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_63, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_63 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_62_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_62_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_63, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_63, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_63 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_62_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (63) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_63(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_63_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_63( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_63_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_63( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_63_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_63( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_63_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_63(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_63_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_63( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_63_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_63( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_63_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_63( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_63_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_63( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_63_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (63) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_63_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_63( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_63( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_63( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_63_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_63_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_63_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_63_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_63_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_63_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_63_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_63_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_63_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_63_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_63_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_63_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_63_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_63_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_63_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_63_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_63_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_63_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_63_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_63_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_63_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_63_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_63_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_63_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_63_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_63_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_63_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_63_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_63_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_63_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_63_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_63_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_64( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_63_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_63_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_64(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_63_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_63_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_63_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_63_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_63_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_64, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_64, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_64 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_63_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_63_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_64, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_64, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_64 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_63_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

/* PUBLIC (64) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_64(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_64_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_64( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_64_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_64( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_64_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_64( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_64_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_64(\
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_64_( \
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_64( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_64_( \
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_64( \
        d, l, is_static, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_64_(d, l, is_static, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
            BOOST_PP_IIF(is_static, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_64( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_64_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_64( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_64_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE (64) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_64_( \
        d, l, is_post, is_static, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_64( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_64( \
            d, l, is_post, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_64( \
            d, l, is_static, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
            BOOST_PP_EXPR_IIF(is_static, static) if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_64_( \
        d, l, is_post, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_64_\
    ,         BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_64_ \
    )(d, l, is_post, decl_traits)

#define \
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_64_( \
        d, l, is_post, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_64_(d, l, is_post, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_64_(\
        d, l, is_post, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_64_( \
        d, l, is_static, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_PP_IIF(is_static, \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_64_ \
                , \
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_64_ \
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_64_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_64_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_64_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_64_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_64_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_64_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_64_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_64_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_64_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_64_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_64_ \
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_64_( \
        d, l, is_post, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_64_(d, l, is_post, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_64_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_64_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_64_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_64_ \
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_64_( \
        d, l, is_post, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_64_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_64_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_64_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_POST_64_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_64_( \
                BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_65( \
                        d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_NOT_POST_64_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_64_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_65(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_64_( \
        d, l, is_post, decl, traits) \
    BOOST_PP_IIF(is_post, \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_64_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_64_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_64_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_64_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_65, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_65, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_65 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_64_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_64_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_65, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_65, \
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_65 \
                ) \
            ) \
        ) \
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_64_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

#endif // #include guard

