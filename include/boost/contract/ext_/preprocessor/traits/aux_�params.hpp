
#ifndef BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_HPP_
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_HPP_

#include <boost/contract/ext_/preprocessor/keyword/default.hpp>
#include <boost/contract/ext_/preprocessor/keyword/void.hpp>
#include <boost/contract/ext_/preprocessor/paren/front.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/list/append.hpp>
#include <boost/preprocessor/list/size.hpp>
#include <boost/preprocessor/list/at.hpp>
#include <boost/preprocessor/list/first_n.hpp>

/* PRIVATE */
            
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_REPLACE_LAST_DEFAULT_( \
        s, decl, d, param_parse_macro, default_replace_macro, traits, last) \
    BOOST_PP_LIST_APPEND_D(d, \
        BOOST_PP_LIST_FIRST_N_D(d, last, traits), \
        ( \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND( \
                default_replace_macro(d, s, \
                    ( \
                        decl, \
                        BOOST_PP_LIST_AT_D(d, traits, last) \
                    ) \
                ) \
            ), \
            BOOST_PP_NIL \
        ) \
    )

// Now parsing `default ...` so replace default value of last parsed parameter.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_REPLACE_DEFAULT_( \
        s, decl, d, param_parse_macro, default_replace_macro, traits) \
    ( \
        d, \
        param_parse_macro, \
        default_replace_macro, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_REPLACE_LAST_DEFAULT_( \
                s, decl, d, param_parse_macro, default_replace_macro, traits, \
                BOOST_PP_DEC(BOOST_PP_LIST_SIZE_D(d, traits))) \
    )

// Now paring parameter declaration (assume default is EMPTY at first).
// Implementation: `decl BOOST_PP_EMPTY` to handle unnamed params.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_APPEND_PARAM_( \
        s, decl, d, param_parse_macro, default_replace_macro, traits) \
    ( \
        d, \
        param_parse_macro, \
        default_replace_macro, \
        BOOST_PP_LIST_APPEND_D(d, \
            traits, \
            ( \
                BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND( \
                    param_parse_macro(d, s, \
                        ( \
                            decl BOOST_PP_EMPTY, \
                            BOOST_PP_EMPTY() \
                        ) \
                    ) \
                ), \
                BOOST_PP_NIL \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAM_( \
        s, d_param_default_traits, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_DEFAULT_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_REPLACE_DEFAULT_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_APPEND_PARAM_ \
    )( \
        s, \
        decl, \
        BOOST_PP_TUPLE_ELEM(4, 0, d_param_default_traits), \
        BOOST_PP_TUPLE_ELEM(4, 1, d_param_default_traits), \
        BOOST_PP_TUPLE_ELEM(4, 2, d_param_default_traits), \
        BOOST_PP_TUPLE_ELEM(4, 3, d_param_default_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_( \
        d, s, allow_void, decl, param_parse_macro, default_replace_macro) \
    BOOST_PP_TUPLE_ELEM(4, 3, \
        BOOST_PP_SEQ_FOLD_LEFT_ ## s( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAM_, \
            ( \
                d, \
                param_parse_macro, \
                default_replace_macro, \
                BOOST_PP_NIL \
            ), \
            BOOST_PP_TUPLE_TO_SEQ(decl) \
        ) \
    )

// Handle `decl == (void)` (i.e., void parameters).
// Precondition: decl is 1-tuple and decl != ().
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_HANDLE_VOID_( \
        d, s, allow_void, decl, param_parse_macro, default_replace_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_TUPLE_REM_CTOR(decl)), \
        BOOST_PP_NIL BOOST_PP_TUPLE_EAT(6) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_ \
    )(d, s, allow_void, decl, param_parse_macro, default_replace_macro)

// Handle `decl == ()` (i.e., empty parameters).
// Precondition: decl is 1-tuple.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_HANDLE_EMPTY_( \
        d, s, allow_void, decl, param_parse_macro, default_replace_macro) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY(BOOST_PP_TUPLE_REM_CTOR(decl)), \
        BOOST_PP_NIL BOOST_PP_TUPLE_EAT(6) \
    , BOOST_PP_IIF(allow_void, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_HANDLE_VOID_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_ \
    ))(d, s, allow_void, decl, param_parse_macro, default_replace_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_D_S_( \
        d, s, allow_void, decl, param_parse_macro, default_replace_macro) \
    BOOST_PP_IIF(BOOST_PP_EQUAL(BOOST_PP_TUPLE_SIZE(decl), 1), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_HANDLE_EMPTY_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_ \
    )(d, s, allow_void, decl, param_parse_macro, default_replace_macro)

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_D_S( \
        d, s, decl, param_parse_macro, default_replace_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_D_S_( \
            d, s, 0, decl, param_parse_macro, default_replace_macro)

// Expand specified pp-tuple of parameter declarations into a pp-list of
// parameters traits (handles empty parameters and default arguments).
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS(decl) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_D_S(1, 1, decl)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_PARAMS_D_S( \
        d, s, decl, param_parse_macro, default_replace_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_D_S_( \
            d, s, 1, decl, param_parse_macro, default_replace_macro)

// Expand specified pp-tuple of parameter declarations into a pp-list of
// parameters traits (handles void and empty parameters, and default arguments).
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_PARAMS(decl) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_PARAMS_D_S(1, 1, decl)

#endif // #include guard

