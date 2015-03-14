
#ifndef BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HPP_
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run related generation script "list-generate.py".

#include <boost/contract/ext_/preprocessor/traits/param.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/keyword/void.hpp>
#include <boost/contract/ext_/preprocessor/utility/empty.hpp>
#include <boost/contract/ext_/preprocessor/variadic/to_seq.hpp>
#include <boost/contract/ext_/preprocessor/variadic/enum_to_seq.hpp>
#include <boost/preprocessor/comparison/not_equal.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/push_front.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

/* PUBLIC */

// Maximum number of nested lists that can be parsed (before pp errors).
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_LIMIT 64

// Usage:
//  ..._LIST_PARSE_D_ ## l(d, decl, parse_elem_macro, is_replacement_macro,
//          replace_elem_macro)
// Expand decl = `( ,,, ) | ( )` (pp-tuple or empty tuple) to `[pp-seq] EMPTY`
// of element traits as parsed by `parse_elem_macro(d, l, decl)`, or replaced
// by `replace_elem_macro(d, l, decl)` when `is_replacement_macro(d, l, decl)`
// expands to 1.
// Expand to `EMPTY` if decl is empty tuple `( )`.
// Expanded pp-seq of traits to be inspected using ..._TRAITS macros associated
// to parse_elem_macro and replace_elem_macro.
// Note: no-void, yes-replace, no-enum (e.g., for template params).

// Usage:
//  ..._VOID_LIST_PARSE_D_ ## l(d, decl, parse_elem_macro,
//          is_replacement_macro, replace_elem_macro)
// Expand decl = `( ,,, ) | ( ) | ( void )` (pp-tuple, empty tuple, or void
// tuple) to `[pp-seq] EMPTY` of element traits as parsed by
// `parse_elem_macro(d, l, decl)`, or replaced by
// `replace_elem_macro(d, l, decl)` when `is_replacement_macro(d, l, decl)`
// expand to 1.
// Expand to `EMPTY` if decl is empty `( )` or void `( void )` tuple.
// Expanded pp-seq of traits to be inspected using ..._TRAITS macros associated
// to parse_elem_macro and replace_elem_macro.
// Note: yes-void, yes-replace, no-enum (e.g., for function params).

// Usage:
//  ..._FIXED_LIST_PARSE_D_ ## l(d, decl, parse_elem_macro)
// Expand decl = `( ,,, ) | ( )` (pp-tuple or empty tuple) to `[pp-seq] EMPTY`
// of element traits as parsed by `parse_elem_macro(d, l, decl)`.
// Expand to `EMPTY` if decl is empty tuple `( )`.
// Expanded pp-seq of traits to be inspected using ..._TRAITS macros associated
// to parse_elem_macro.
// Note: no-void, no-replace, no-enum (e.g., for captures).

// Usage:
//  ..._ENUM_LIST_PARSE_D_ ## l(d, decl, parse_elem_macro,
//          is_replacement_macro, replace_elem_macro)
// Expand decl = `( ,,, [,] ) | ( )` (pp-tuple, or enumeration tuple with extra
// trailing comma `,`, or empty tuple) to `[pp-seq] EMPTY` of element traits as
// parsed by `parse_elem_macro(d, l, decl)`, or replaced by
// `replace_elem_macro(d, l, decl)` when `is_replacement_macro(d, l, decl)`
// expands to 1.
// Expand to `EMPTY` if decl is empty tuple `( )`.
// Expanded pp-seq of traits to be inspected using ..._TRAITS macros associated
// to parse_elem_macro and replace_elem_macro.
// Note: no-void, yes-replace, yes-enum (e.g., for assertions).

/* PUBLIC (1) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_1( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_1_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_1( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_1_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_1( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_1_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_1( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_1_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (1) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_1_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_1_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_1_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_1_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_1_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_1_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_1_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_1_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_1_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_1_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_1_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_1_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_1_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_1_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 2, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_1_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_1_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_1_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_1_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 2, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_1_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_1_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 2, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_1_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (2) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_2( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_2_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_2( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_2_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_2( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_2_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_2( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_2_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (2) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_2_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_2_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_2_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_2_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_2_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_2_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_2_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_2_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_2_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_2_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_2_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_2_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_2_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_2_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 3, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_2_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_2_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_2_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_2_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 3, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_2_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_2_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 3, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_2_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (3) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_3( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_3_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_3( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_3_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_3( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_3_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_3( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_3_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (3) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_3_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_3_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_3_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_3_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_3_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_3_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_3_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_3_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_3_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_3_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_3_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_3_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_3_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_3_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 4, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_3_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_3_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_3_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_3_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 4, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_3_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_3_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 4, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_3_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (4) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_4( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_4_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_4( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_4_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_4( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_4_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_4( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_4_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (4) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_4_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_4_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_4_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_4_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_4_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_4_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_4_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_4_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_4_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_4_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_4_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_4_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_4_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_4_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 5, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_4_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_4_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_4_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_4_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 5, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_4_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_4_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 5, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_4_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (5) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_5( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_5_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_5( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_5_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_5( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_5_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_5( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_5_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (5) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_5_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_5_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_5_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_5_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_5_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_5_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_5_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_5_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_5_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_5_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_5_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_5_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_5_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_5_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 6, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_5_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_5_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_5_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_5_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 6, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_5_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_5_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 6, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_5_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (6) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_6( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_6_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_6( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_6_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_6( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_6_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_6( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_6_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (6) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_6_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_6_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_6_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_6_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_6_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_6_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_6_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_6_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_6_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_6_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_6_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_6_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_6_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_6_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 7, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_6_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_6_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_6_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_6_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 7, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_6_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_6_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 7, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_6_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (7) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_7( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_7_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_7( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_7_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_7( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_7_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_7( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_7_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (7) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_7_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_7_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_7_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_7_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_7_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_7_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_7_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_7_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_7_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_7_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_7_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_7_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_7_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_7_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 8, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_7_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_7_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_7_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_7_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 8, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_7_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_7_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 8, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_7_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (8) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_8( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_8_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_8( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_8_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_8( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_8_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_8( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_8_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (8) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_8_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_8_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_8_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_8_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_8_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_8_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_8_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_8_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_8_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_8_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_8_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_8_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_8_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_8_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 9, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_8_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_8_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_8_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_8_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 9, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_8_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_8_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 9, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_8_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (9) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_9( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_9_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_9( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_9_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_9( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_9_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_9( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_9_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (9) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_9_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_9_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_9_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_9_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_9_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_9_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_9_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_9_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_9_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_9_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_9_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_9_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_9_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_9_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 10, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_9_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_9_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_9_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_9_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 10, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_9_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_9_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 10, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_9_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (10) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_10( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_10_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_10( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_10_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_10( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_10_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_10( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_10_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (10) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_10_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_10_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_10_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_10_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_10_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_10_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_10_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_10_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_10_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_10_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_10_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_10_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_10_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_10_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 11, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_10_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_10_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_10_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_10_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 11, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_10_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_10_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 11, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_10_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (11) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_11( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_11_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_11( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_11_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_11( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_11_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_11( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_11_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (11) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_11_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_11_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_11_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_11_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_11_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_11_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_11_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_11_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_11_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_11_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_11_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_11_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_11_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_11_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 12, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_11_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_11_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_11_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_11_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 12, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_11_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_11_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 12, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_11_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (12) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_12( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_12_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_12( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_12_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_12( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_12_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_12( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_12_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (12) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_12_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_12_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_12_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_12_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_12_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_12_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_12_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_12_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_12_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_12_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_12_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_12_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_12_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_12_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 13, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_12_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_12_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_12_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_12_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 13, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_12_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_12_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 13, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_12_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (13) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_13( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_13_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_13( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_13_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_13( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_13_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_13( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_13_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (13) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_13_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_13_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_13_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_13_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_13_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_13_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_13_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_13_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_13_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_13_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_13_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_13_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_13_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_13_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 14, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_13_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_13_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_13_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_13_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 14, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_13_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_13_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 14, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_13_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (14) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_14( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_14_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_14( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_14_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_14( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_14_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_14( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_14_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (14) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_14_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_14_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_14_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_14_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_14_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_14_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_14_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_14_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_14_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_14_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_14_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_14_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_14_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_14_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 15, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_14_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_14_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_14_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_14_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 15, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_14_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_14_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 15, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_14_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (15) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_15( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_15_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_15( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_15_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_15( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_15_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_15( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_15_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (15) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_15_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_15_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_15_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_15_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_15_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_15_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_15_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_15_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_15_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_15_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_15_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_15_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_15_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_15_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 16, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_15_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_15_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_15_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_15_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 16, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_15_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_15_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 16, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_15_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (16) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_16( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_16_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_16( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_16_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_16( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_16_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_16( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_16_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (16) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_16_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_16_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_16_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_16_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_16_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_16_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_16_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_16_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_16_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_16_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_16_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_16_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_16_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_16_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 17, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_16_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_16_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_16_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_16_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 17, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_16_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_16_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 17, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_16_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (17) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_17( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_17_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_17( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_17_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_17( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_17_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_17( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_17_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (17) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_17_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_17_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_17_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_17_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_17_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_17_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_17_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_17_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_17_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_17_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_17_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_17_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_17_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_17_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 18, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_17_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_17_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_17_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_17_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 18, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_17_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_17_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 18, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_17_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (18) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_18( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_18_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_18( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_18_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_18( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_18_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_18( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_18_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (18) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_18_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_18_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_18_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_18_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_18_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_18_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_18_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_18_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_18_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_18_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_18_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_18_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_18_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_18_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 19, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_18_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_18_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_18_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_18_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 19, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_18_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_18_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 19, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_18_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (19) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_19( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_19_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_19( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_19_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_19( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_19_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_19( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_19_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (19) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_19_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_19_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_19_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_19_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_19_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_19_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_19_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_19_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_19_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_19_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_19_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_19_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_19_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_19_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 20, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_19_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_19_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_19_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_19_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 20, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_19_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_19_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 20, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_19_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (20) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_20( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_20_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_20( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_20_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_20( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_20_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_20( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_20_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (20) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_20_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_20_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_20_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_20_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_20_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_20_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_20_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_20_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_20_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_20_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_20_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_20_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_20_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_20_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 21, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_20_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_20_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_20_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_20_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 21, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_20_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_20_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 21, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_20_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (21) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_21( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_21_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_21( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_21_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_21( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_21_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_21( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_21_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (21) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_21_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_21_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_21_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_21_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_21_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_21_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_21_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_21_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_21_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_21_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_21_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_21_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_21_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_21_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 22, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_21_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_21_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_21_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_21_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 22, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_21_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_21_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 22, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_21_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (22) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_22( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_22_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_22( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_22_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_22( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_22_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_22( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_22_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (22) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_22_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_22_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_22_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_22_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_22_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_22_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_22_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_22_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_22_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_22_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_22_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_22_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_22_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_22_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 23, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_22_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_22_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_22_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_22_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 23, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_22_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_22_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 23, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_22_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (23) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_23( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_23_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_23( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_23_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_23( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_23_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_23( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_23_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (23) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_23_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_23_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_23_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_23_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_23_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_23_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_23_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_23_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_23_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_23_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_23_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_23_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_23_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_23_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 24, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_23_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_23_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_23_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_23_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 24, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_23_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_23_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 24, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_23_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (24) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_24( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_24_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_24( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_24_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_24( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_24_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_24( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_24_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (24) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_24_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_24_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_24_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_24_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_24_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_24_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_24_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_24_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_24_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_24_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_24_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_24_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_24_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_24_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 25, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_24_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_24_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_24_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_24_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 25, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_24_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_24_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 25, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_24_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (25) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_25( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_25_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_25( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_25_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_25( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_25_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_25( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_25_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (25) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_25_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_25_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_25_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_25_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_25_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_25_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_25_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_25_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_25_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_25_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_25_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_25_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_25_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_25_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 26, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_25_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_25_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_25_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_25_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 26, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_25_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_25_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 26, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_25_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (26) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_26( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_26_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_26( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_26_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_26( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_26_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_26( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_26_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (26) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_26_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_26_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_26_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_26_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_26_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_26_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_26_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_26_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_26_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_26_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_26_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_26_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_26_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_26_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 27, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_26_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_26_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_26_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_26_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 27, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_26_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_26_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 27, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_26_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (27) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_27( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_27_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_27( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_27_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_27( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_27_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_27( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_27_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (27) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_27_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_27_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_27_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_27_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_27_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_27_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_27_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_27_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_27_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_27_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_27_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_27_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_27_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_27_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 28, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_27_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_27_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_27_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_27_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 28, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_27_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_27_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 28, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_27_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (28) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_28( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_28_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_28( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_28_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_28( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_28_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_28( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_28_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (28) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_28_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_28_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_28_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_28_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_28_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_28_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_28_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_28_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_28_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_28_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_28_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_28_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_28_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_28_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 29, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_28_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_28_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_28_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_28_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 29, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_28_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_28_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 29, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_28_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (29) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_29( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_29_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_29( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_29_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_29( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_29_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_29( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_29_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (29) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_29_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_29_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_29_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_29_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_29_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_29_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_29_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_29_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_29_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_29_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_29_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_29_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_29_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_29_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 30, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_29_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_29_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_29_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_29_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 30, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_29_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_29_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 30, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_29_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (30) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_30( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_30_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_30( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_30_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_30( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_30_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_30( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_30_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (30) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_30_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_30_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_30_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_30_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_30_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_30_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_30_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_30_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_30_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_30_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_30_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_30_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_30_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_30_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 31, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_30_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_30_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_30_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_30_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 31, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_30_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_30_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 31, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_30_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (31) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_31( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_31_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_31( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_31_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_31( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_31_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_31( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_31_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (31) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_31_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_31_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_31_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_31_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_31_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_31_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_31_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_31_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_31_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_31_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_31_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_31_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_31_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_31_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 32, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_31_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_31_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_31_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_31_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 32, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_31_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_31_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 32, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_31_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (32) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_32( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_32_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_32( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_32_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_32( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_32_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_32( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_32_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (32) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_32_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_32_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_32_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_32_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_32_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_32_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_32_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_32_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_32_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_32_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_32_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_32_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_32_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_32_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 33, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_32_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_32_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_32_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_32_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 33, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_32_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_32_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 33, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_32_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (33) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_33( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_33_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_33( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_33_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_33( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_33_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_33( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_33_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (33) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_33_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_33_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_33_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_33_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_33_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_33_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_33_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_33_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_33_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_33_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_33_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_33_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_33_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_33_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 34, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_33_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_33_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_33_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_33_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 34, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_33_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_33_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 34, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_33_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (34) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_34( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_34_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_34( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_34_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_34( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_34_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_34( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_34_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (34) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_34_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_34_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_34_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_34_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_34_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_34_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_34_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_34_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_34_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_34_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_34_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_34_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_34_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_34_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 35, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_34_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_34_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_34_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_34_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 35, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_34_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_34_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 35, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_34_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (35) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_35( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_35_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_35( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_35_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_35( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_35_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_35( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_35_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (35) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_35_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_35_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_35_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_35_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_35_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_35_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_35_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_35_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_35_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_35_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_35_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_35_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_35_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_35_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 36, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_35_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_35_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_35_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_35_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 36, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_35_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_35_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 36, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_35_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (36) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_36( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_36_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_36( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_36_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_36( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_36_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_36( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_36_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (36) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_36_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_36_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_36_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_36_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_36_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_36_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_36_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_36_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_36_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_36_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_36_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_36_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_36_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_36_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 37, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_36_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_36_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_36_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_36_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 37, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_36_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_36_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 37, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_36_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (37) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_37( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_37_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_37( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_37_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_37( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_37_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_37( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_37_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (37) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_37_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_37_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_37_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_37_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_37_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_37_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_37_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_37_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_37_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_37_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_37_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_37_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_37_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_37_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 38, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_37_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_37_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_37_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_37_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 38, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_37_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_37_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 38, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_37_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (38) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_38( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_38_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_38( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_38_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_38( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_38_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_38( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_38_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (38) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_38_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_38_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_38_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_38_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_38_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_38_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_38_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_38_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_38_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_38_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_38_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_38_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_38_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_38_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 39, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_38_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_38_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_38_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_38_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 39, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_38_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_38_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 39, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_38_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (39) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_39( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_39_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_39( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_39_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_39( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_39_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_39( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_39_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (39) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_39_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_39_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_39_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_39_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_39_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_39_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_39_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_39_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_39_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_39_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_39_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_39_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_39_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_39_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 40, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_39_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_39_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_39_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_39_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 40, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_39_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_39_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 40, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_39_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (40) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_40( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_40_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_40( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_40_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_40( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_40_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_40( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_40_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (40) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_40_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_40_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_40_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_40_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_40_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_40_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_40_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_40_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_40_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_40_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_40_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_40_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_40_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_40_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 41, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_40_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_40_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_40_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_40_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 41, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_40_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_40_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 41, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_40_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (41) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_41( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_41_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_41( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_41_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_41( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_41_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_41( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_41_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (41) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_41_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_41_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_41_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_41_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_41_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_41_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_41_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_41_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_41_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_41_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_41_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_41_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_41_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_41_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 42, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_41_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_41_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_41_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_41_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 42, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_41_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_41_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 42, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_41_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (42) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_42( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_42_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_42( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_42_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_42( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_42_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_42( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_42_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (42) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_42_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_42_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_42_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_42_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_42_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_42_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_42_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_42_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_42_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_42_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_42_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_42_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_42_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_42_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 43, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_42_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_42_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_42_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_42_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 43, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_42_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_42_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 43, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_42_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (43) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_43( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_43_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_43( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_43_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_43( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_43_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_43( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_43_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (43) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_43_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_43_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_43_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_43_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_43_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_43_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_43_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_43_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_43_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_43_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_43_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_43_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_43_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_43_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 44, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_43_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_43_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_43_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_43_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 44, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_43_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_43_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 44, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_43_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (44) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_44( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_44_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_44( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_44_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_44( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_44_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_44( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_44_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (44) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_44_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_44_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_44_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_44_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_44_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_44_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_44_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_44_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_44_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_44_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_44_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_44_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_44_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_44_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 45, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_44_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_44_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_44_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_44_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 45, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_44_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_44_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 45, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_44_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (45) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_45( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_45_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_45( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_45_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_45( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_45_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_45( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_45_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (45) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_45_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_45_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_45_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_45_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_45_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_45_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_45_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_45_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_45_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_45_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_45_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_45_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_45_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_45_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 46, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_45_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_45_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_45_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_45_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 46, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_45_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_45_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 46, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_45_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (46) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_46( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_46_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_46( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_46_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_46( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_46_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_46( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_46_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (46) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_46_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_46_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_46_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_46_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_46_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_46_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_46_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_46_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_46_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_46_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_46_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_46_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_46_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_46_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 47, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_46_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_46_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_46_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_46_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 47, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_46_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_46_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 47, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_46_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (47) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_47( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_47_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_47( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_47_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_47( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_47_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_47( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_47_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (47) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_47_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_47_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_47_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_47_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_47_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_47_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_47_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_47_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_47_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_47_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_47_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_47_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_47_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_47_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 48, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_47_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_47_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_47_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_47_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 48, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_47_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_47_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 48, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_47_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (48) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_48( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_48_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_48( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_48_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_48( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_48_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_48( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_48_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (48) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_48_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_48_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_48_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_48_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_48_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_48_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_48_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_48_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_48_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_48_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_48_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_48_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_48_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_48_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 49, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_48_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_48_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_48_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_48_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 49, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_48_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_48_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 49, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_48_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (49) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_49( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_49_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_49( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_49_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_49( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_49_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_49( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_49_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (49) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_49_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_49_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_49_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_49_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_49_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_49_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_49_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_49_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_49_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_49_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_49_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_49_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_49_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_49_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 50, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_49_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_49_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_49_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_49_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 50, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_49_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_49_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 50, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_49_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (50) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_50( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_50_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_50( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_50_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_50( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_50_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_50( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_50_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (50) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_50_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_50_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_50_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_50_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_50_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_50_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_50_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_50_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_50_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_50_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_50_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_50_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_50_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_50_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 51, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_50_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_50_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_50_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_50_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 51, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_50_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_50_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 51, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_50_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (51) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_51( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_51_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_51( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_51_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_51( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_51_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_51( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_51_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (51) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_51_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_51_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_51_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_51_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_51_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_51_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_51_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_51_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_51_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_51_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_51_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_51_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_51_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_51_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 52, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_51_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_51_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_51_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_51_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 52, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_51_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_51_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 52, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_51_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (52) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_52( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_52_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_52( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_52_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_52( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_52_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_52( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_52_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (52) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_52_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_52_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_52_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_52_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_52_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_52_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_52_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_52_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_52_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_52_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_52_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_52_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_52_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_52_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 53, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_52_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_52_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_52_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_52_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 53, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_52_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_52_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 53, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_52_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (53) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_53( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_53_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_53( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_53_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_53( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_53_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_53( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_53_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (53) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_53_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_53_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_53_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_53_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_53_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_53_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_53_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_53_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_53_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_53_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_53_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_53_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_53_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_53_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 54, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_53_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_53_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_53_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_53_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 54, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_53_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_53_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 54, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_53_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (54) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_54( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_54_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_54( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_54_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_54( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_54_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_54( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_54_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (54) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_54_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_54_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_54_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_54_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_54_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_54_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_54_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_54_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_54_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_54_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_54_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_54_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_54_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_54_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 55, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_54_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_54_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_54_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_54_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 55, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_54_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_54_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 55, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_54_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (55) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_55( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_55_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_55( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_55_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_55( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_55_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_55( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_55_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (55) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_55_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_55_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_55_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_55_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_55_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_55_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_55_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_55_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_55_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_55_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_55_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_55_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_55_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_55_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 56, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_55_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_55_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_55_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_55_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 56, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_55_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_55_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 56, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_55_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (56) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_56( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_56_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_56( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_56_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_56( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_56_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_56( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_56_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (56) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_56_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_56_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_56_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_56_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_56_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_56_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_56_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_56_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_56_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_56_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_56_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_56_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_56_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_56_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 57, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_56_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_56_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_56_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_56_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 57, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_56_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_56_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 57, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_56_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (57) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_57( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_57_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_57( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_57_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_57( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_57_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_57( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_57_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (57) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_57_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_57_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_57_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_57_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_57_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_57_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_57_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_57_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_57_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_57_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_57_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_57_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_57_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_57_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 58, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_57_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_57_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_57_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_57_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 58, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_57_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_57_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 58, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_57_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (58) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_58( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_58_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_58( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_58_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_58( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_58_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_58( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_58_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (58) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_58_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_58_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_58_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_58_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_58_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_58_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_58_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_58_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_58_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_58_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_58_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_58_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_58_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_58_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 59, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_58_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_58_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_58_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_58_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 59, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_58_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_58_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 59, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_58_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (59) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_59( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_59_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_59( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_59_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_59( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_59_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_59( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_59_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (59) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_59_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_59_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_59_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_59_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_59_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_59_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_59_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_59_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_59_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_59_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_59_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_59_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_59_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_59_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 60, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_59_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_59_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_59_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_59_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 60, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_59_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_59_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 60, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_59_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (60) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_60( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_60_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_60( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_60_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_60( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_60_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_60( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_60_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (60) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_60_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_60_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_60_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_60_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_60_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_60_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_60_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_60_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_60_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_60_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_60_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_60_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_60_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_60_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 61, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_60_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_60_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_60_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_60_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 61, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_60_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_60_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 61, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_60_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (61) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_61( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_61_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_61( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_61_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_61( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_61_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_61( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_61_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (61) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_61_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_61_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_61_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_61_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_61_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_61_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_61_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_61_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_61_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_61_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_61_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_61_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_61_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_61_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 62, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_61_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_61_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_61_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_61_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 62, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_61_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_61_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 62, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_61_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (62) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_62( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_62_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_62( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_62_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_62( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_62_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_62( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_62_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (62) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_62_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_62_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_62_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_62_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_62_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_62_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_62_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_62_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_62_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_62_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_62_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_62_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_62_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_62_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 63, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_62_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_62_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_62_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_62_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 63, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_62_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_62_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 63, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_62_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (63) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_63( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_63_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_63( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_63_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_63( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_63_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_63( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_63_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (63) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_63_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_63_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_63_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_63_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_63_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_63_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_63_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_63_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_63_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_63_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_63_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_63_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_63_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_63_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 64, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_63_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_63_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_63_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_63_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 64, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_63_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_63_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 64, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_63_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (64) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_64( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_64_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_64( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_64_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_64( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_64_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_64( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_64_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (64) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_64_(d, allow_void, \
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_64_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_64_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_64_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_64_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_64_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_64_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_64_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_64_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_64_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_64_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_64_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_64_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_64_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 65, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_64_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_64_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_64_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_64_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 65, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_64_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_64_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 65, (BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_64_(d, \
    decl_seq, traits, elemdecl_elemtraits, \
    parse_elem_macro, is_replacement_macro, replace_elem_macro \
) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#endif // #include guard

