
#ifndef BOOST_CONTRACT_EXT_PP_LIST_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_HPP_

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

// Expand decl = `( ,,, ) | ( )` (pp-tuple or empty tuple) to `[pp-seq] EMPTY`
// of list element traits as parsed by parse_elem_macro (and replaced by
// replace_elem_macro for default values, etc.) to be inspected using
// ..._TRAITS macros associated to parse_elem_macro and replace_elem_macro
// (expand to `EMPTY` if decl is empty tuple `( )`).
// Implementation: void = no, replace = yes, enum = no (e.g., template params).
#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_D( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

// Expand decl = `( ,,, ) | ( ) | ( void )` (pp-tuple, empty tuple, or void
// tuple) to `[pp-seq] EMPTY` of list element traits as parsed by
// parse_elem_macro (and replaced by replace_elem_macro for default values,
// etc.) to be inspected using ..._TRAITS macros related to parse_elem_macro
// and replace_elem_macro (expand to `EMPTY` if decl is empty `( )` or void
// `( void )` tuple).
// Implementation: void = yes, replace = yes, enum = no (e.g., func params).
#define BOOST_CONTRACT_EXT_PP_VOID_LIST_TRAITS_PARSE_D( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_(d, \
        1, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

// Implementation: void = no, replace = no, enum = no (e.g., captures).
#define BOOST_CONTRACT_EXT_PP_FIXED_LIST_TRAITS_PARSE_D( \
        d, decl, parse_elem_macro) \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ decl, \
        parse_elem_macro, \
        BOOST_CONTRACT_EXT_PP_LIST_TRAITS_ALWAYS_FALSE_, \
        BOOST_PP_NIL \
    )

// Implementation: void = no, replace = yes, enum = yes (e.g., old-of assert.).
#define BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D( \
        d, decl, parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_(d, \
        0, \
        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ decl, \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

/* PRIVATE */

// TODO: Can I use `0 BOOST_PP_TUPLE_EAT(1)` instead of this macro?
#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_ALWAYS_FALSE_(decl) 0

// Expand traits to EMPTY for EMPTY() parameters.
#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_(d, allow_void, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
   BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_LIST_TRAITS_HANDLE_VOID_ \
    , \
        BOOST_CONTRACT_EXT_PP_LIST_TRAITS_ \
    ))(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

// Expand traits to EMPTY for EMPTY() parameters.
// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_HANDLE_VOID_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_EXT_PP_LIST_TRAITS_ \
    )(d, decl_seq, parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_(d, decl_seq, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_RETURN_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PRED_, \
            BOOST_CONTRACT_EXT_PP_LIST_TRAITS_OP_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                parse_elem_macro, \
                is_replacement_macro, \
                replace_elem_macro \
            ) \
        ) \
    )

// Trailing EMPTY to traits to handle EMPTY() parameters.
#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_RETURN_( \
        decl_traits_parse_is_replace) \
    ( \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(5, 1, \
                decl_traits_parse_is_replace)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PRED_( \
        d, decl_traits_parse_is_replace) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            5, 0, decl_traits_parse_is_replace)), 1)
    
#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_OP_(d, decl_traits_parse_is_replace) \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_OP_ARGS_(d, \
        BOOST_PP_TUPLE_ELEM(5, 0, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 1, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 2, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 3, decl_traits_parse_is_replace), \
        BOOST_PP_TUPLE_ELEM(5, 4, decl_traits_parse_is_replace) \
    )

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_OP_ARGS_(d, decl_seq, traits, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    BOOST_PP_IIF(is_replacement_macro(BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_LIST_TRAITS_REPLACE_ \
    , \
        BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PUSH_BACK_ \
    )(d, decl_seq, traits, \
            parse_elem_macro, is_replacement_macro, replace_elem_macro)

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PUSH_BACK_(d, decl_seq, traits, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    ( \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_LIST_TRAITS_EXPAND_TRAITS_( \
                    parse_elem_macro(d, BOOST_PP_SEQ_HEAD(decl_seq))) \
        ), \
        parse_elem_macro, \
        is_replacement_macro, \
        replace_elem_macro \
    )

#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_REPLACE_(d, decl_seq, traits, \
        parse_elem_macro, is_replacement_macro, replace_elem_macro) \
    ( \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
            BOOST_CONTRACT_EXT_PP_LIST_TRAITS_EXPAND_TRAITS_( \
                replace_elem_macro(d, \
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
#define BOOST_CONTRACT_EXT_PP_LIST_TRAITS_EXPAND_TRAITS_(decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

#endif // #include guard

