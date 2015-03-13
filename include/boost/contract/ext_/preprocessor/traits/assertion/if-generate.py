
import os
import sys

LIMIT = 64

def code():
    result = ''
    for n in range(1, LIMIT + 1):
        result = result + '''
/* PUBLIC ({0}) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_{0}(d, l, decl) \\
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_{0}_(d, l, 0, 0, decl)

#define BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_{0}( \\
        d, l, decl) \\
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_{0}_(d, l, 1, 0, decl)

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_{0}( \\
        d, l, decl) \\
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_{0}_(d, l, 0, 1, decl)

#define BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_{0}( \\
        d, l, decl) \\
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_{0}_(d, l, 1, 1, decl)

// Parse else assertions for both if and static-if.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_{0}(\\
        d, l, decl_traits) \\
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_{0}_( \\
            d, l, 0, decl_traits)

// Parse else post-assertions for both if and static-if.
#define \\
BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_{0}( \\
        d, l, decl_traits) \\
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_{0}_( \\
            d, l, 1, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_{0}( \\
        d, l, is_static, decl_traits) \\
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_{0}_(d, l, is_static, \\
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \\
            BOOST_PP_IIF(is_static, \\
                BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT \\
            , \\
                BOOST_PP_TUPLE_REM(1) \\
            )(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \\
        ), \\
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \\
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_{0}( \\
        d, l, is_post, decl_traits) \\
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_{0}_(d, l, is_post, \\
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \\
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \\
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_{0}( \\
        d, l, is_post, decl_traits) \\
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_{0}_(d, l, is_post, \\
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \\
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \\
    )

/* PRIVATE ({0}) */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_{0}_( \\
        d, l, is_post, is_static, decl) \\
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \\
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L_{0}( \\
            d, l, is_post, \\
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L_{0}( \\
            d, l, is_post, \\
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L_{0}( \\
            d, l, is_static, \\
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KEY_PARSE( \\
            BOOST_PP_EXPR_IIF(is_static, static) if, \\
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \\
        decl BOOST_PP_NIL \\
    ))))))

#define \\
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_{0}_( \\
        d, l, is_post, decl_traits) \\
    BOOST_PP_IIF( \\
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \\
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \\
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \\
            ) \\
        ) \\
    , \\
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_{0}_\\
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_{0}_ \\
    )(d, l, is_post, decl_traits)

#define \\
BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_{0}_( \\
        d, l, is_post, decl_traits) \\
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_{0}_(d, l, is_post, \\
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \\
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \\
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \\
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_{0}_(\\
        d, l, is_post, decl_traits) \\
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \\
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_{0}_( \\
        d, l, is_static, decl, traits) \\
    ( \\
        BOOST_PP_TUPLE_EAT(0) decl, \\
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \\
            traits, \\
            BOOST_PP_TUPLE_ELEM(2, 1, \\
                BOOST_PP_IIF(is_static, \\
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_{0}_ \\
                , \\
                    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_{0}_ \\
                )(d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \\
            ) \\
        ) \\
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_{0}_(d, l, decl) \\
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \\
            BOOST_PP_TUPLE_ELEM(0, decl)), \\
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_{0}_ \\
    , \\
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_{0}_ \\
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_{0}_(d, l, decl) \\
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \\
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_{0}_(d, l, decl) \\
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_{0}_( \\
        d, l, is_post, decl, traits) \\
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \\
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_{0}_ \\
    , \\
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_{0}_ \\
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_{0}_( \\
        d, l, is_post, decl, traits) \\
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \\
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_{0}_ \\
    , \\
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_{0}_ \\
    )(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_{0}_( \\
        d, l, is_post, decl, traits) \\
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_{0}_(d, l, is_post, \\
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_{0}_( \\
        d, l, is_post, decl, traits) \\
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \\
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_{0}_ \\
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \\
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_{0}_ \\
    , \\
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_{0}_ \\
    ))(d, l, is_post, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_{0}_( \\
        d, l, is_post, decl, traits) \\
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_{0}_( \\
        d, l, is_post, decl, traits) \\
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_PUSH_BACK_{0}_(d, l, \\
        BOOST_PP_IIF(is_post, \\
            BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_{1} \\
        , \\
            BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_{1} \\
        )(d, l, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK(decl)), \\
        traits \\
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_PUSH_BACK_{0}_( \\
        d, l, decl_assertion, traits) \\
    ( \\
        BOOST_PP_TUPLE_ELEM(2, 0, decl_assertion), \\
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \\
                ( BOOST_PP_TUPLE_ELEM(2, 1, decl_assertion) ) BOOST_PP_EMPTY) \\
    )

// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_{0}_( \\
        d, l, is_post, decl, traits) \\
    BOOST_PP_IIF(is_post, \\
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_{0}_ \\
    , \\
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_{0}_ \\
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_POST_{0}_( \\
        d, l, decl, traits) \\
    ( \\
        BOOST_PP_TUPLE_EAT(0) decl, \\
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \\
            traits, \\
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_{0}_( \\
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \\
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \\
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_{1}, \\
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_{1}, \\
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_{1} \\
                ) \\
            ) \\
        ) \\
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NOT_POST_{0}_( \\
        d, l, decl, traits) \\
    ( \\
        BOOST_PP_TUPLE_EAT(0) decl, \\
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \\
            traits, \\
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_{0}_( \\
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_ ## l(d, \\
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \\
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_{1}, \\
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_{1}, \\
  BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_{1} \\
                ) \\
            ) \\
        ) \\
    )

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_{0}_( \\
        decl_traits) \\
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)
'''.format(n, n + 1)
    return result

script = os.path.basename(sys.argv[0])
path = sys.argv[0].replace('-generate.py', '', 1) + ".hpp"
file = open(path, 'w')

file.write('''
#ifndef BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run related generation script "{0}".

#include <boost/contract/ext_/preprocessor/traits/assertion/if/cond.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/if/thens.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/if/elses.hpp>
#include <boost/contract/ext_/preprocessor/keyword/else.hpp>
#include <boost/contract/ext_/preprocessor/keyword/static.hpp>

/* PUBLIC */

// NOTE: This same file provides APIs to parse both if-assertion and
// static-if-assertion traits (because the code re-uses same implementation
// macros and because the traits inspection public macros are the same).

// Maximum number of nested if and static-if assertions that can be parsed
// (before pp errors).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_LIMIT {1}

// ASSERTION_TRAITS_KEY(traits) expands to `if` for if-assertion and to
// `static if` for static-if-assertion (this can be checked in "one step" using
// the ..._STATIC_IF_..._IS macro below).

#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(tokens) \\
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_STATIC_FRONT(tokens), \\
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS_ \\
    , \\
        0 BOOST_PP_TUPLE_EAT(1) \\
    )(tokens)

/* PRIVATE */

// Precondition: tokens = `static ...`.
#define BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS_(tokens) \\
    BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT( \\
        BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT( \\
            tokens BOOST_PP_NIL \\
        ) \\
    )
{2}
#endif // #include guard

'''.format(script, LIMIT, code()))

file.close()
print "Written:", path

