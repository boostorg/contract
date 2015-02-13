
#ifndef BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/assertion/oldof/assign.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/oldof/type.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/oldof/expr.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/bool/expr.hpp>

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_FRONT( \
            BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `..._TRAITS_ODLOF` (this can be
//               checked with `..._TRAITS_IS_OLDOF_FRONT` macro above).
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_OPERATOR_REMOVE_FRONT( \
        tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_CAT_TO_EMPTY, \
            tokens)

// This is the operator that decl. syntax must use to prefix old-of expressions:
// `{auto | wrapper-type} var = ..._OPERATOR exr`.
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_OPERATOR \
    , BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_OPERATOR_

// Precondition: oldofdecl_booltraits =
// `(OLDOF expr, (bool) (auto-wrapped-type assign =)` (which is here transformed
// to the parsalbe decl = `(OLDOF expr) auto-wrapped-type assign =`).
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D( \
        d, oldofdecl_booltraits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_DONE_( \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_ASSIGN_PARSE( \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_TYPE_PARSE_D(d, \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_EXPR_PARSE( \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
        BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_OPERATOR_, \
        ( \
            (BOOST_PP_TUPLE_ELEM(2, 0, oldofdecl_booltraits)) \
            BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_EXPR( \
                    BOOST_PP_TUPLE_ELEM(2, 1, oldofdecl_booltraits)) \
            BOOST_PP_NIL, \
            BOOST_CONTRACT_EXT_PP_TRAITS_INIT \
        ) \
    )))))

/* PRIVATE */
      
// This macro name must NOT be #defined (used like a "keyword").
#ifdef BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_OPERATOR_
#   error "#definition of reserved macro name"
#endif

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_CAT_TO_COMMABOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_OPERATOR_ ,
// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_CAT_TO_EMPTYBOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_OPERATOR_

#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_DONE_(decl_traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

#endif // #include guard

