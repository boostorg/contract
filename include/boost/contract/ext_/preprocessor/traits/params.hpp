
#ifndef BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/param.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/default.hpp>
#include <boost/contract/ext_/preprocessor/keyword/void.hpp>
#include <boost/contract/ext_/preprocessor/utility/empty.hpp>
#include <boost/preprocessor/comparison/not_equal.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

/* PRIVATE */
            
#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_REPLACE_DEFAULT_( \
        d, decl_seq, traits, param_parse_macro, default_replace_macro) \
    ( \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                default_replace_macro(d, \
                    ( \
                        BOOST_PP_SEQ_HEAD(decl_seq), \
                        BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits) \
                    ) \
                ) \
            ) \
        ), \
        param_parse_macro, \
        default_replace_macro \
    )

#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_PUSH_BACK_PARAM_( \
        d, decl_seq, traits, param_parse_macro, default_replace_macro) \
    ( \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                    param_parse_macro(d, BOOST_PP_SEQ_HEAD(decl_seq))) \
        ), \
        param_parse_macro, \
        default_replace_macro \
    )

#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_OP_ARGS_( \
        d, decl_seq, traits, param_parse_macro, default_replace_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_DEFAULT_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_REPLACE_DEFAULT_ \
    , \
        BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_PUSH_BACK_PARAM_ \
    )(d, decl_seq, traits, param_parse_macro, default_replace_macro)

#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_OP_(d, decl_traits_param_default) \
    BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_OP_ARGS_( \
        d, \
        BOOST_PP_TUPLE_ELEM(4, 0, decl_traits_param_default), \
        BOOST_PP_TUPLE_ELEM(4, 1, decl_traits_param_default), \
        BOOST_PP_TUPLE_ELEM(4, 2, decl_traits_param_default), \
        BOOST_PP_TUPLE_ELEM(4, 3, decl_traits_param_default) \
    )

#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_PRED_( \
        d, decl_traits_param_default) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(4, 0, \
            decl_traits_param_default)), 1)
    
// Trailing EMPTY to traits to handle EMPTY() parameters.
#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_RETURN_(decl_traits_param_default) \
    ( \
        BOOST_PP_TUPLE_ELEM(4, 0, decl_traits_param_default), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(4, 1, \
                decl_traits_param_default)) BOOST_PP_EMPTY \
    )

#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_( \
        d, decl_seq, param_parse_macro, default_replace_macro) \
    BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_RETURN_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_PRED_, \
            BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_OP_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT, \
                param_parse_macro, \
                default_replace_macro \
            ) \
        ) \
    )

// Expand traits to EMPTY for EMPTY() parameters.
// Precondition: decl_seq is a valid pp-seq, so decl_seq != EMPTY().
#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_HANDLE_VOID_( \
        d, decl_seq, param_parse_macro, default_replace_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(4) \
    , \
        BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_ \
    )(d, decl_seq, param_parse_macro, default_replace_macro)

// Expand traits to EMPTY for EMPTY() parameters.
#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_PARSE_( \
        d, allow_void, decl_seq, param_parse_macro, default_replace_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(4) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_HANDLE_VOID_ \
    , \
        BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_ \
    ))(d, decl_seq, param_parse_macro, default_replace_macro)

#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_DEFAULT_REPLACE_PARSE_( \
        d, decl_traits) \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_REPLACE_PARSE(decl_traits)

/* PUBLIC */

// Expand decl_seq = `(param1)...(param-n)` to pp-seq of parameter traits,
// otherwise expand decl_seq = `EMPTY() | (void)` to EMPTY().
// NOTE: Variadic parameter tuples `( ) | ( void ) | ( param1, ..., paran-n )`
// can be transformed to EMPTY() or pp-seq using EXT_PP_VARIADIC_TO_SEQ.
#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_PARSE_D(d, decl_seq) \
    BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_PARSE_( \
        d, 1, decl_seq, \
        BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_PARSE_D, \
        BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_DEFAULT_REPLACE_PARSE_ \
    )

// Expand decl = `(,,,)` containing template parameter declarations into pp-list
// of template parameter traits (to then be inspected using PARAM_TRAITS
// macros). Handle empty `()`.
#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAMS_TRAITS_PARSE_D(d, decl_seq) \
    BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_PARSE_( \
        d, 0, decl_seq, \
        BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_PARSE_D, \
        BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_DEFAULT_REPLACE_PARSE_ \
    )

#endif // #include guard

