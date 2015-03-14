
import os
import sys

LIMIT = 64

def code():
    result = ''
    for i in range(1, LIMIT + 1):
        result = result + '''
/* PUBLIC ({0}) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_D_{0}( \\
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \\
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_{0}_(d, \\
        0, \\
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \\
        parse_elem_macro, \\
        is_replacement_macro, \\
        replace_elem_macro \\
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_LIST_PARSE_D_{0}( \\
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \\
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_{0}_(d, \\
        1, \\
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \\
        parse_elem_macro, \\
        is_replacement_macro, \\
        replace_elem_macro \\
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_{0}( \\
        d, decl, parse_elem_macro) \\
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_{0}_(d, \\
        0, \\
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \\
        parse_elem_macro, \\
        0 BOOST_PP_TUPLE_EAT(3), \\
        BOOST_PP_NIL \\
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_{0}( \\
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \\
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_{0}_(d, \\
        0, \\
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \\
        parse_elem_macro, \\
        is_replacement_macro, \\
        replace_elem_macro \\
    )

/* PRIVATE ({0}) */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PARSE_{0}_(d, allow_void, \\
        decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro) \\
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \\
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \\
    , BOOST_PP_IIF(allow_void, \\
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_{0}_ \\
    , \\
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_{0}_ \\
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HANDLE_VOID_{0}_(d, decl_seq, \\
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \\
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \\
            BOOST_PP_SEQ_HEAD(decl_seq)), \\
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \\
    , \\
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_{0}_ \\
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_{0}_(d, decl_seq, \\
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \\
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_{0}_( \\
        BOOST_PP_WHILE_ ## d( \\
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_{0}_, \\
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_{0}_, \\
            ( \\
                decl_seq (BOOST_PP_NIL), \\
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \\
                parse_elem_macro, \\
                is_replacement_macro, \\
                replace_elem_macro \\
            ) \\
        ) \\
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_RETURN_{0}_( \\
        decl_traits_parse_is_replace) \\
    ( \\
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \\
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \\
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \\
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PRED_{0}_( \\
        d, decl_traits_parse_is_replace) \\
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \\
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_{0}_( \\
        d, decl_traits_parse_is_replace) \\
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_{0}_(d, \\
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \\
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \\
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \\
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \\
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \\
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_OP_ARGS_{0}_(d, decl_seq, \\
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \\
    BOOST_PP_IIF(is_replacement_macro(d, {1}, BOOST_PP_SEQ_HEAD(decl_seq)), \\
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_{0}_ \\
    , \\
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_{0}_ \\
    )(d, decl_seq, traits, \\
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_PARSE_{0}_(d, decl_seq, \\
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \\
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_{0}_(d, \\
        BOOST_PP_SEQ_TAIL(decl_seq), \\
        traits, \\
        parse_elem_macro(d, {1}, BOOST_PP_SEQ_HEAD(decl_seq)), \\
        parse_elem_macro, \\
        is_replacement_macro, \\
        replace_elem_macro \\
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_ELEM_REPLACE_{0}_(d, decl_seq, \\
        traits, parse_elem_macro, is_replacement_macro, replace_elem_macro) \\
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_{0}_(d, \\
        BOOST_PP_SEQ_TAIL(decl_seq), \\
        BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \\
        replace_elem_macro(d, {1}, (BOOST_PP_SEQ_HEAD(decl_seq), \\
                BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits))), \\
        parse_elem_macro, \\
        is_replacement_macro, \\
        replace_elem_macro \\
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_PUSH_BACK_{0}_(d, \\
    decl_seq, traits, elemdecl_elemtraits, \\
    parse_elem_macro, is_replacement_macro, replace_elem_macro \\
) \\
    ( \\
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM( \\
                2, 0, elemdecl_elemtraits)), \\
            decl_seq BOOST_PP_TUPLE_EAT(2) \\
        , \\
            BOOST_PP_SEQ_PUSH_FRONT \\
        )(decl_seq, BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \\
                BOOST_PP_TUPLE_ELEM(2, 0, elemdecl_elemtraits))), \\
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \\
                BOOST_PP_TUPLE_ELEM(2, 1, elemdecl_elemtraits)), \\
        parse_elem_macro, \\
        is_replacement_macro, \\
        replace_elem_macro \\
    )
'''.format(i, i + 1)
    return result

script = os.path.basename(sys.argv[0])
path = sys.argv[0].replace('-generate.py', '', 1) + ".hpp"
file = open(path, 'w')
file.write('''
#ifndef BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HPP_
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run related generation script "{0}".

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
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_LIST_LIMIT {1}

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
{2}
#endif // #include guard

'''.format(script, LIMIT, code()))
file.close()
print "Written:", path

