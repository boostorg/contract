
#ifndef BOOST_CONTRACT_EXT_PP_LIST_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_HPP_

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
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// NOTE: This algorithm currently uses WHILE and _D but it could also have been
// implemented using SEQ_FOLD_LEFT and _S (or some other iteration index). _D
// was chose because it is already used by other algorithms of this pp traits
// library (so that quite a few _D values are used by these algorithms but all
// other iteration indexes are free for the users). Furthermore, WHILE is a
// fairly generic iteration mechanism so it will still work if the
// implementation of this algorithm needs to change in the future (while
// keeping the interface of these macros unchanged to _D).

/* PUBLIC */

// NOTE: Versions of public macros `..._ # l` are available for reentrancy.

// Expand decl = `( ,,, ) | ( )` (pp-tuple or empty tuple) to `[pp-seq] EMPTY`
// of element traits as parsed by `parse_elem_macro(d, l, decl)`, or replaced
// by `replace_elem_macro(d, l, decl)` when `is_replacement_macro(d, l, decl)`
// expands to 1.
// Expand to `EMPTY` if decl is empty tuple `( )`.
// Expanded pp-seq of traits to be inspected using ..._TRAITS macros associated
// to parse_elem_macro and replace_elem_macro.
// Note: void = no, replace = yes, enum = no (e.g., template params).
#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_D \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_D_1

// Expand decl = `( ,,, ) | ( ) | ( void )` (pp-tuple, empty tuple, or void
// tuple) to `[pp-seq] EMPTY` of element traits as parsed by
// `parse_elem_macro(d, l, decl)`, or replaced by
// `replace_elem_macro(d, l, decl)` when `is_replacement_macro(d, l, decl)`
// expand to 1.
// Expand to `EMPTY` if decl is empty `( )` or void `( void )` tuple.
// Expanded pp-seq of traits to be inspected using ..._TRAITS macros associated
// to parse_elem_macro and replace_elem_macro.
// Note: void = yes, replace = yes, enum = no (e.g., func params).
#define BOOST_CONTRACT_EXT_PP_VOID_LIST_TRAITS_PARSE_D \
    BOOST_CONTRACT_EXT_PP_VOID_LIST_TRAITS_PARSE_D_1

// Expand decl = `( ,,, ) | ( )` (pp-tuple or empty tuple) to `[pp-seq] EMPTY`
// of element traits as parsed by `parse_elem_macro(d, l, decl)`.
// Expand to `EMPTY` if decl is empty tuple `( )`.
// Expanded pp-seq of traits to be inspected using ..._TRAITS macros associated
// to parse_elem_macro.
// Note: void = no, replace = no, enum = no (e.g., captures).
#define BOOST_CONTRACT_EXT_PP_FIXED_LIST_TRAITS_PARSE_D \
    BOOST_CONTRACT_EXT_PP_FIXED_LIST_TRAITS_PARSE_D_1

// Expand decl = `( ,,, [,] ) | ( )` (pp-tuple, or enumeration tuple with extra
// trailing comma `,`, or empty tuple) to `[pp-seq] EMPTY` of element traits as
// parsed by `parse_elem_macro(d, l, decl)`, or replaced by
// `replace_elem_macro(d, l, decl)` when `is_replacement_macro(d, l, decl)`
// expands to 1.
// Expand to `EMPTY` if decl is empty tuple `( )`.
// Expanded pp-seq of traits to be inspected using ..._TRAITS macros associated
// to parse_elem_macro and replace_elem_macro.
// Note: void = no, replace = yes, enum = yes (e.g., old-of assert.).
#define BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D \
    BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_1

/* PUBLIC (1) */

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_D_1( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_1_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_VOID_LIST_TRAITS_PARSE_D_1( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_1_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_FIXED_LIST_TRAITS_PARSE_D_1( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_1_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_1( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_1_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (1) */

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_1_(d, allow_void, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_LIST_TRAITS_HANDLE_VOID_1_ \
    , \
        BOOST_CONTRACT_EXT_PP_LIST_TRAITS_1_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_HANDLE_VOID_1_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_LIST_TRAITS_1_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_1_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_RETURN_1_xx( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PRED_1_, \
            BOOST_CONTRACT_EXT_PP_LIST_TRAITS_OP_1_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_RETURN_1_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PRED_1_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_OP_1_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_OP_ARGS_1_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_OP_ARGS_1_(d, decl_seq, traits, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 2, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_LIST_TRAITS_ELEM_REPLACE_1_ \
    , \
        BOOST_CONTRACT_EXT_PP_LIST_TRAITS_ELEM_PARSE_1_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_ELEM_PARSE_1_(d, decl_seq, \
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PUSH_BACK_1_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        traits, \
        parse_elem_macro(d, 2, BOOST_PP_SEQ_HEAD(decl_seq)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_ELEM_REPLACE_1_(d, decl_seq, traits, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PUSH_BACK_1_(d, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
        replace_elem_macro(d, 2, \
            ( \
                BOOST_PP_SEQ_HEAD(decl_seq), \
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits) \
            ) \
        ), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#include <boost/preprocessor/seq/push_front.hpp>

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PUSH_BACK_1_(d, decl_seq, traits, \
        elemdecl_elemtraits, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \
                2, 0, elemdecl_elemtraits)), \
            decl_seq BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_PUSH_FRONT \
        )(decl_seq, BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PUBLIC (2) */

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_D_2( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_2_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_VOID_LIST_TRAITS_PARSE_D_2( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_2_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_FIXED_LIST_TRAITS_PARSE_D_2( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_2_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        0 BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_2( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_2_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE (2) */

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_2_(d, allow_void, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_LIST_TRAITS_HANDLE_VOID_2_ \
    , \
        BOOST_CONTRACT_EXT_PP_LIST_TRAITS_2_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_HANDLE_VOID_2_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_LIST_TRAITS_2_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_2_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_RETURN_2_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PRED_2_, \
            BOOST_CONTRACT_EXT_PP_LIST_TRAITS_OP_2_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_RETURN_2_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PRED_2_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_OP_2_( \
        d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_OP_ARGS_2_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_OP_ARGS_2_(d, decl_seq, traits, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(d, 3, BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_LIST_TRAITS_REPLACE_2_ \
    , \
        BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PUSH_BACK_2_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PUSH_BACK_2_(d, decl_seq, traits, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    ( \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_LIST_TRAITS_EXPAND_TRAITS_2_( \
                    parse_elem_macro(d, 3, BOOST_PP_SEQ_HEAD(decl_seq))) \
        ), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_REPLACE_2_(d, decl_seq, traits, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    ( \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
            BOOST_CONTRACT_EXT_PP_LIST_TRAITS_EXPAND_TRAITS_2_( \
                replace_elem_macro(d, 3, \
                    ( \
                        BOOST_PP_SEQ_HEAD(decl_seq), \
                        BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits) \
                    ) \
                ) \
            ) \
        ), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

// Extra level of indirection for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_EXPAND_TRAITS_2_(decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

#endif // #include guard

