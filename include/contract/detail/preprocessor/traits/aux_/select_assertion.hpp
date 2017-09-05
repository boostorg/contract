
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_HPP_
#define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_HPP_

#include <contract/detail/preprocessor/keyword/if.hpp>
#include <contract/detail/preprocessor/keyword/else.hpp>
#include <contract/detail/preprocessor/variadic/to_seq.hpp>
#include <boost/config.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_SEQ_TO_LIST_( \
        seq) \
    BOOST_PP_TUPLE_TO_LIST(BOOST_PP_SEQ_SIZE(seq), BOOST_PP_SEQ_TO_TUPLE(seq))

#define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_NIL_REMOVE_ \
    /* must expand to nothing */

#ifndef BOOST_NO_VARIADIC_MACROS
#   define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_ELSE_(...) \
        CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_SEQ_TO_LIST_( \
                CONTRACT_DETAIL_PP_VARIADIC_TO_SEQ( \
                        (ERROR_cannot_specify_empty_if_else_assertions), \
                        __VA_ARGS__))
#else
#   define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_ELSE_(seq) \
        CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_SEQ_TO_LIST_(seq)
#endif

#define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_ELSE_LIST_YES_( \
        else_tokens) \
    BOOST_PP_CAT( \
            BOOST_PP_EXPAND( \
            CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_ELSE_ \
            CONTRACT_DETAIL_PP_KEYWORD_ELSE_REMOVE_FRONT(else_tokens)), \
            REMOVE_ /* removes trailing NIL */)

#define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_ELSE_LIST_( \
        condition, then_assertions, else_tokens) \
    (\
        condition \
    , \
        then_assertions \
    , \
        BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_ELSE_FRONT(else_tokens), \
            CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_ELSE_LIST_YES_ \
        , \
            BOOST_PP_NIL /* empty list */ \
            BOOST_PP_TUPLE_EAT(1) \
        )(else_tokens) \
    )

#ifndef BOOST_NO_VARIADIC_MACROS
#   define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_SPLIT_THEN_(...) \
        CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_SEQ_TO_LIST_( \
                CONTRACT_DETAIL_PP_VARIADIC_TO_SEQ( \
                        (ERROR_cannot_specify_empty_if_then_assertions), \
                        __VA_ARGS__)) \
        , /* comma splits */
#else
#   define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_SPLIT_THEN_(seq) \
        CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_SEQ_TO_LIST_(seq) \
        , /* comma split */ 
#endif

#define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_SPLIT_(cond) \
    cond , /* comma splits */ \
    CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_SPLIT_THEN_

// PROTECTED //

#define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_PREPEND_RCURLY( \
        d, number_instruction_requirements_traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(4, 0, number_instruction_requirements_traits) \
    , \
        /* NOTE: cannot use `}` directly because instruction must be */ \
        /* inspected for pp-keywords so it must start with alphanumeric */ \
        CONTRACT_DETAIL_PP_RCURLY \
    , \
        CONTRACT_DETAIL_PP_TRAITS_AUX_NIL \
    , \
        CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_APPEND(d \
            , BOOST_PP_TUPLE_ELEM(4, 3, number_instruction_requirements_traits)\
            , BOOST_PP_TUPLE_ELEM(4, 0, number_instruction_requirements_traits)\
            , BOOST_PP_TUPLE_ELEM(4, 1, number_instruction_requirements_traits)\
            , BOOST_PP_TUPLE_ELEM(4, 2, number_instruction_requirements_traits)\
        ) \
    )

#define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_PREPEND_ELSE( \
        d, number_instruction_requirements_traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(4, 0, number_instruction_requirements_traits) \
    , \
        else /* use needs to add trailing { */ \
    , \
        CONTRACT_DETAIL_PP_TRAITS_AUX_NIL \
    , \
        CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_APPEND(d \
            , BOOST_PP_TUPLE_ELEM(4, 3, number_instruction_requirements_traits)\
            , BOOST_PP_TUPLE_ELEM(4, 0, number_instruction_requirements_traits)\
            , BOOST_PP_TUPLE_ELEM(4, 1, number_instruction_requirements_traits)\
            , BOOST_PP_TUPLE_ELEM(4, 2, number_instruction_requirements_traits)\
        ) \
    )

#define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_PREPEND_IF( \
        d, select_condition, number_instruction_requirements_traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(4, 0, number_instruction_requirements_traits) \
    , \
        if(select_condition) /* user needs to add trailing { */ \
    , \
        CONTRACT_DETAIL_PP_TRAITS_AUX_NIL \
    , \
        CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_APPEND(d \
            , BOOST_PP_TUPLE_ELEM(4, 3, number_instruction_requirements_traits)\
            , BOOST_PP_TUPLE_ELEM(4, 0, number_instruction_requirements_traits)\
            , BOOST_PP_TUPLE_ELEM(4, 1, number_instruction_requirements_traits)\
            , BOOST_PP_TUPLE_ELEM(4, 2, number_instruction_requirements_traits)\
        ) \
    )

// Traits of a single select assertion.
#define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION(assertion) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_ELSE_LIST_ \
    BOOST_PP_EXPAND( ( \
        CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_SPLIT_ \
        CONTRACT_DETAIL_PP_KEYWORD_IF_REMOVE_FRONT(assertion) \
        CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_NIL_ /* empty */ \
    ) )

#define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_IF( \
        traits) \
    BOOST_PP_TUPLE_ELEM(3, 0, traits)

#define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_THENS(traits) \
    BOOST_PP_TUPLE_ELEM(3, 1, traits)

#define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_ELSES(traits) \
    BOOST_PP_TUPLE_ELEM(3, 2, traits)

#endif // #include guard

