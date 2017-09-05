
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_ASSERTION_FUNC_HPP_
#define CONTRACT_AUX_CODE_ASSERTION_FUNC_HPP_

#include <contract/aux_/macro/code_/assert.hpp>
#include <contract/detail/preprocessor/traits/assertion.hpp> // a
#include <contract/detail/preprocessor/keyword/const.hpp>
#include <contract/detail/preprocessor/keyword/static.hpp>
#include <boost/mpl/bool.hpp>

// PRIVATE //

#define CONTRACT_AUX_CODE_ASSERTION_FUNC_DEF_(d, \
        false_decl_tokens, true_decl_tokens, \
        true_def_statements_token, true_def_const_tokens, true_def_check_token)\
    (( /* seq of array to handle unwrapped commas */ \
        /* total number of tokens */ \
        BOOST_PP_SUB(BOOST_PP_LIST_SIZE(BOOST_PP_LIST_APPEND( \
                false_decl_tokens, BOOST_PP_LIST_APPEND(true_decl_tokens, \
                true_def_const_tokens))), \
                /* when 2 lists -1, when 3 lists -2 (trim list joint point) */ \
                BOOST_PP_IIF(BOOST_PP_LIST_IS_CONS(true_def_const_tokens),2,1))\
    , ( /* wrap all tokens within the array's tuple */ \
        BOOST_PP_LIST_ENUM(false_decl_tokens) \
        { \
            /* POLICY: do nothing, silently pass the assertion if the */ \
            /* assertion requirements are not met */ \
        } \
        BOOST_PP_LIST_ENUM(true_decl_tokens) \
        { \
            true_def_statements_token \
            BOOST_PP_LIST_ENUM(true_def_const_tokens) \
            true_def_check_token \
        } \
    )))

#define CONTRACT_AUX_CODE_ASSERTION_FUNC_PREV_STATEMENT_(d, number_code, a) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, number_code) /* code so far */ \
    , \
        BOOST_PP_TUPLE_ELEM(2, 1, number_code) /* code so far */ \
        /* append instruction code (if apply) */ \
        BOOST_PP_EXPR_IIF(BOOST_PP_BITAND( \
                CONTRACT_DETAIL_PP_ASSERTION_TRAITS_IS_STATEMENT(a), \
                BOOST_PP_LESS(CONTRACT_DETAIL_PP_ASSERTION_TRAITS_NUMBER(a), \
                        BOOST_PP_TUPLE_ELEM(2, 0, number_code))), \
            /* NOTE: if this is an assertion statement (using, etc) with a */ \
            /* number smaller (<) than spec number, then the statement */ \
            /* preceded the assertion being coded (i.e., with the spec */ \
            /* number) so its scope affects the coded assertion and the */ \
            /* statement is programmed into the assertion function */ \
            CONTRACT_DETAIL_PP_ASSERTION_TRAITS_INSTRUCTION(a) \
            ; /* trailing `;` ends statement */ \
        ) \
    )
        
#define CONTRACT_AUX_CODE_ASSERTION_FUNC_PREV_STATEMENTS_( \
        d, id, tpl, a, assertions) \
    BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PP_LIST_FOLD_LEFT_ ## d( \
            CONTRACT_AUX_CODE_ASSERTION_FUNC_PREV_STATEMENT_, \
            (CONTRACT_DETAIL_PP_ASSERTION_TRAITS_NUMBER(a), ;), assertions))

#define CONTRACT_AUX_CODE_ASSERTION_FUNC_REQUIREMENT_(d, id, tpl, a, \
        underscored_name, decl_tokens_macro, data, assertions, \
        true_def_const_tokens, true_def_check_token) \
    CONTRACT_AUX_CODE_ASSERTION_FUNC_DEF_(d \
        , decl_tokens_macro(d, id, tpl, data, \
                ::boost::mpl::false_ const&, a) \
        , decl_tokens_macro(d, id, tpl, data, \
                ::boost::mpl::true_ const&, a) \
        , CONTRACT_AUX_CODE_ASSERTION_FUNC_PREV_STATEMENTS_(d, id, tpl, a, \
                assertions) \
        , true_def_const_tokens \
        , true_def_check_token \
    )

#define CONTRACT_AUX_CODE_ASSERTION_FUNC_CONST_(d, id, tpl, a, \
        underscored_name, decl_tokens_macro, data, assertions) \
    CONTRACT_AUX_CODE_ASSERTION_FUNC_REQUIREMENT_(d, id, tpl, a, \
            underscored_name, decl_tokens_macro, data, assertions, \
            /* tokens that define the const-assertion local function */ \
            CONTRACT_AUX_CODE_ASSERT_CONST_DEF_TOKENS(id, tpl, a, \
                    underscored_name), \
            /* single token checking const assertion (calling loc func) */ \
            CONTRACT_AUX_CODE_ASSERT_CONST(id, tpl, a, \
                    underscored_name))

#define CONTRACT_AUX_CODE_ASSERTION_FUNC_STATIC_(d, id, tpl, a, \
        underscored_name, decl_tokens_macro, data, assertions) \
    CONTRACT_AUX_CODE_ASSERTION_FUNC_REQUIREMENT_(d, id, tpl, a, \
            underscored_name, decl_tokens_macro, data, assertions, \
            BOOST_PP_NIL, /* no const tokens (this is not const-assertion */ \
            /* single token checking static assertion */ \
            CONTRACT_AUX_CODE_ASSERT_STATIC(id, tpl, a, underscored_name))

#define CONTRACT_AUX_CODE_ASSERTION_FUNC_BOOL_(d, id, tpl, a, \
        underscored_name, decl_tokens_macro, data, assertions) \
    CONTRACT_AUX_CODE_ASSERTION_FUNC_REQUIREMENT_(d, id, tpl, a, \
            underscored_name, decl_tokens_macro, data, assertions, \
            BOOST_PP_NIL, /* no const tokens (this is not const-assertion */ \
            /* single token checking bool assertion */ \
            CONTRACT_AUX_CODE_ASSERT_BOOL(id, tpl, a, underscored_name))

#define CONTRACT_AUX_CODE_ASSERTION_FUNC_( \
        d, id_tpl_name_decl_data_assertions_code, a) \
    ( \
        BOOST_PP_TUPLE_ELEM(7, 0, id_tpl_name_decl_data_assertions_code) \
    , \
        BOOST_PP_TUPLE_ELEM(7, 1, id_tpl_name_decl_data_assertions_code) \
    , \
        BOOST_PP_TUPLE_ELEM(7, 2, id_tpl_name_decl_data_assertions_code) \
    , \
        BOOST_PP_TUPLE_ELEM(7, 3, id_tpl_name_decl_data_assertions_code) \
    , \
        BOOST_PP_TUPLE_ELEM(7, 4, id_tpl_name_decl_data_assertions_code) \
    , \
        BOOST_PP_TUPLE_ELEM(7, 5, id_tpl_name_decl_data_assertions_code) \
    , \
        BOOST_PP_TUPLE_ELEM(7, 6, id_tpl_name_decl_data_assertions_code) \
        /* append seq */ \
        BOOST_PP_IIF(BOOST_PP_COMPL(BOOST_PP_IS_EMPTY( \
                CONTRACT_DETAIL_PP_ASSERTION_TRAITS_REQUIREMENT(a))), \
            /* NOTE: assertion functions are used for assertion requirements */\
            /* so the assertion compilation is skipped when the assertion */ \
            /* requirements are not met (because the assertion func is a tpl)*/\
            BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_STATIC_ASSERT_FRONT( \
                    CONTRACT_DETAIL_PP_ASSERTION_TRAITS_INSTRUCTION(a)), \
                CONTRACT_AUX_CODE_ASSERTION_FUNC_STATIC_ \
            , \
            BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_CONST_FRONT( \
                    CONTRACT_DETAIL_PP_ASSERTION_TRAITS_INSTRUCTION(a)), \
                CONTRACT_AUX_CODE_ASSERTION_FUNC_CONST_ \
            , \
                CONTRACT_AUX_CODE_ASSERTION_FUNC_BOOL_ \
            )) \
        , \
            BOOST_PP_TUPLE_EAT(8) /* skip this assertion (no requirement) */\
        )( \
              d \
            , BOOST_PP_TUPLE_ELEM(7, 0, id_tpl_name_decl_data_assertions_code) \
            , BOOST_PP_TUPLE_ELEM(7, 1, id_tpl_name_decl_data_assertions_code) \
            , a \
            , BOOST_PP_TUPLE_ELEM(7, 2, id_tpl_name_decl_data_assertions_code) \
            , BOOST_PP_TUPLE_ELEM(7, 3, id_tpl_name_decl_data_assertions_code) \
            , BOOST_PP_TUPLE_ELEM(7, 4, id_tpl_name_decl_data_assertions_code) \
            , BOOST_PP_TUPLE_ELEM(7, 5, id_tpl_name_decl_data_assertions_code) \
        ) \
    )

#define CONTRACT_AUX_CODE_ASSERTION_FUNC_DEF_FROM_ARRAY_( \
        r, unused, code_array) \
    BOOST_PP_LIST_ENUM_R(r, BOOST_PP_TUPLE_TO_LIST( \
            BOOST_PP_ARRAY_SIZE(code_array), BOOST_PP_ARRAY_DATA(code_array)))

#define CONTRACT_AUX_CODE_ASSERTION_FUNC_DEF_FROM_SEQ_(code_seq) \
    BOOST_PP_SEQ_FOR_EACH(CONTRACT_AUX_CODE_ASSERTION_FUNC_DEF_FROM_ARRAY_, ~, \
            BOOST_PP_SEQ_TAIL(code_seq))

#define CONTRACT_AUX_CODE_ASSERTION_FUNC_DEF_GET_(code_seq) \
    BOOST_PP_IIF(BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(code_seq), 1), \
        BOOST_PP_TUPLE_EAT(1) /* no assertion func definition code */ \
    , \
        CONTRACT_AUX_CODE_ASSERTION_FUNC_DEF_FROM_SEQ_ \
    )(code_seq)

// PUBLIC //

// Where `decl_tokens_macro(d, id, tpl, data, dispatch_param, a)`
// expands to token list (data is optional, pass ~ or similar if not needed).
#define CONTRACT_AUX_CODE_ASSERTION_FUNC_DEF(id, tpl, \
        underscored_name, decl_tokens_macro, data, assertions) \
    /* can't use LIST_FOR_EACH here instead of FOLD_LEFT because it doesn't */ \
    /* reenter correctly on MSVC (not even if FOR_EACH_R is used) because */ \
    /* many of the alg used to expand the assert func also use LIST_FOR_EACH */\
    CONTRACT_AUX_CODE_ASSERTION_FUNC_DEF_GET_(BOOST_PP_TUPLE_ELEM(7, 6, \
            BOOST_PP_LIST_FOLD_LEFT(CONTRACT_AUX_CODE_ASSERTION_FUNC_, \
                    /* code in seq of array to handle unwrapped commas */ \
                    ( id, tpl, underscored_name, decl_tokens_macro, \
                      data, assertions, ((1, (;))) ), \
                    assertions)))

#endif // #include guard

