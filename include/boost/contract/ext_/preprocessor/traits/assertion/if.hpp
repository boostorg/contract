
#ifndef BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/assertion/if/cond.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/if/thens.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/if/elses.hpp>
#include <boost/contract/ext_/preprocessor/keyword/else.hpp>

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L(d, l, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L(d, l, \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L(d, l, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE(if, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L( \
        d, l, decl_traits) \
    BOOST_PP_IIF( \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_ \
    )(d, l, decl_traits)

// Precondition: decl = `if( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_PARSE_D_L( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_(d, l, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IF_REMOVE_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_PARSE_D_L( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_(d, l, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Precondition: decl = `else ( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_PARSE_D_L( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_(d, l, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_YES_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_(d, l, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

// If trying to replace else statements of a if that already had some, threat
// replacement `else ...` as a bool assertion (so it will eventually error).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_NO_( \
        d, l, decl_traits) \
    (bool(BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) BOOST_PP_NIL, \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits))

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_ARGS_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_( \
                    d, l, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl) \
                ) \
            ) \
        ) \
    )

// Precondition: decl = `( ,,, )`.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_(d, l, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_TUPLE_ELEM(0, decl)), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_ \
    )(d, l, decl)

// Precondition: decl = `(const( ,,, ) ...)` (so need to remove parens).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_CONST_(d, l, decl)\
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, \
            BOOST_PP_TUPLE_REM_CTOR(1, decl))

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_BOOL_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS_( \
        d, l, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_ARGS_( \
        d, l, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_ \
    )(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_YES_( \
        d, l, decl, traits) \
    BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_(d, l, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_ELSE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_( \
        d, l, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_ \
    , \
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_ \
    ))(d, l, decl, traits)

#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_NO_( \
        d, l, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
     
// Precondition: decl = `assertion BOOST_PP_NIL` (single assertion).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTION_YES_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_2(d, l, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    decl \
                ))) \
            ) BOOST_PP_EMPTY \
        ) \
    )

// TODO: I should NOT parse return and old-of here unless for postconditions...
// Precondition: decl = `( assertions,,, ) ...` (multiple assertions).
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ASSERTIONS_YES_( \
        d, l, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_( \
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
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_EXPAND_TRAITS_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

#endif // #include guard

