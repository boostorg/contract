
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_CONST_EXPR_HPP_
#define CONTRACT_AUX_CODE_CONST_EXPR_HPP_

#include <contract/detail/preprocessor/traits/const_expr.hpp>
#include <contract/detail/preprocessor/keyword/const.hpp>
#include <boost/local_function.hpp>
#include <boost/preprocessor/arithmetic/mul.hpp>

// PRIVATE //

// Precondition: SIZE(TYPE(var_traits)) > 1.
// NOTE: The implementation of this macro seems to confuse most compilers
// because of the use of BOOST_IDENTITY_TYPE (so explicit types with commas
// don't work, as a workaround users can use a typedef assertion statement).
// It /seems/ that fixing this would ultimately require a better overload of
// Boost.ScopeExit deref function template but that's outside the scope of this
// library.
#define CONTRACT_AUX_CODE_CONST_EXPR_BIND_VAR_EXPLICT_TYPE_COMMAS_( \
        r, tpl, var_traits) \
    ( \
        BOOST_PP_EXPR_IIF(tpl, typename) \
        BOOST_IDENTITY_TYPE(( /* handles unwrapped commas */ \
            BOOST_PP_ARRAY_ENUM( \
                    CONTRACT_DETAIL_PP_CONST_EXPR_VAR_TRAITS_TYPE( \
                            var_traits)) \
        )) \
    )

// Precondition: SIZE(TYPE(var_traits)) > 1.
#define CONTRACT_AUX_CODE_CONST_EXPR_BIND_VAR_EXPLICT_TYPE_NO_COMMA_( \
        r, tpl, var_traits) \
    ( \
        BOOST_PP_ARRAY_ENUM(CONTRACT_DETAIL_PP_CONST_EXPR_VAR_TRAITS_TYPE( \
                var_traits)) \
    )

// Precondition: SIZE(TYPE(var_traits)) > 0.
#define CONTRACT_AUX_CODE_CONST_EXPR_BIND_VAR_EXPLICT_TYPE_( \
        r, tpl, var_traits) \
    BOOST_PP_IIF(BOOST_PP_EQUAL(1, BOOST_PP_ARRAY_SIZE( \
                    CONTRACT_DETAIL_PP_CONST_EXPR_VAR_TRAITS_TYPE( \
                            var_traits))), \
        CONTRACT_AUX_CODE_CONST_EXPR_BIND_VAR_EXPLICT_TYPE_NO_COMMA_ \
    , \
        /* NOTE: unfortunately, to handle commas we need to used */ \
        /* BOOST_IDENTITY_TYPE which seems to confuse compilers when */ \
        /* explicit types are specified so we separate the no-comma */ \
        /* case to not use IDENTITY_TYPE to not confuse compilers if */ \
        /* no commas and explicit types (but compilers will still be */ \
        /* confused when commas and explicit types) */ \
        CONTRACT_AUX_CODE_CONST_EXPR_BIND_VAR_EXPLICT_TYPE_COMMAS_ \
    )(r, tpl, var_traits)

#define CONTRACT_AUX_CODE_CONST_EXPR_BIND_SEQ_(r, tpl, var_traits) \
    ( /* local function bind syntax `(const bind[(var_type)]& var_name)...` */ \
        const /* for const-expression const-correctness */ \
        bind /* capture variable in scope */ \
        BOOST_PP_IF(BOOST_PP_ARRAY_SIZE( /* if explicit variable type */ \
                CONTRACT_DETAIL_PP_CONST_EXPR_VAR_TRAITS_TYPE(var_traits)), \
            CONTRACT_AUX_CODE_CONST_EXPR_BIND_VAR_EXPLICT_TYPE_ \
        , \
            BOOST_PP_TUPLE_EAT(3) /* type implicitly deduced with Typeof */ \
        )(r, tpl, var_traits) \
        & /* ref so no copy constructor is required */ \
        CONTRACT_DETAIL_PP_CONST_EXPR_VAR_TRAITS_NAME(var_traits) \
    )

// Count tokens separated by commas not wrapped by round parenthesis `()`.
#define CONTRACT_AUX_CODE_CONST_EXPR_TOKENS_COUNT_(var_count) \
    /* NOTE: The Local library uses an initialization assignment */ \
    /* `= { var1 , ... }` later followed by a member initialization */ \
    /* `: var1 , ...` for a total of 2 * n - 1 tokens separated by commas */ \
    /* not wrapped within round parenthesis */ \
    BOOST_PP_DEC(BOOST_PP_MUL(2, var_count))

#define CONTRACT_AUX_CODE_CONST_EXPR_TOKENS_FUNC_DEF_( \
        id, tpl, result_type, func_name, const_traits) \
    BOOST_PP_TUPLE_TO_LIST( \
        CONTRACT_AUX_CODE_CONST_EXPR_TOKENS_COUNT_(BOOST_PP_LIST_SIZE( \
                CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_VARS(const_traits))) \
    , ( /* tuple to wrap commas from LOCAL_FUNCTION expansion */ \
        /* using internal LOCAL_FUNCTION macros to pass id */ \
        BOOST_PP_IIF(tpl, \
            BOOST_LOCAL_FUNCTION_ID_TPL \
        , \
            BOOST_LOCAL_FUNCTION_ID \
        )(  \
              func_name /* name is unique (and contains id) */ \
            , BOOST_PP_LIST_FOR_EACH( /* always pp-sequence syntax */ \
                  CONTRACT_AUX_CODE_CONST_EXPR_BIND_SEQ_ \
                , tpl \
                , CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_VARS(const_traits) \
              ) \
              (return result_type) /* avoid Boost.Typeof for result type */ \
        ) \
            { /* local function body */ \
                /* extra paren around expression to wrap eventual commas */ \
                return (CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_EXPR( \
                        const_traits)); \
            } \
        BOOST_PP_IIF(tpl, \
            BOOST_LOCAL_FUNCTION_NAME_TPL \
        , \
            BOOST_LOCAL_FUNCTION_NAME \
        )(func_name) \
    ) )

#define CONTRACT_AUX_CODE_CONST_EXPR_TOKENS_( \
        id, tpl, result_type, func_name, const_expr) \
    CONTRACT_AUX_CODE_CONST_EXPR_TOKENS_FUNC_DEF_(id, tpl, result_type, \
            func_name, CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS(const_expr))

// PUBLIC //

// Expand `const( ... ) ...` to pp-list of tokens to handle commas not wrapped
// within round parenthesis contained in local function code (use PP_LIST_ENUM
// to generate final code).
#define CONTRACT_AUX_CODE_CONST_EXPR_TOKENS( \
        id, tpl, result_type, func_name, const_expr) \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_CONST_FRONT(const_expr), \
        CONTRACT_AUX_CODE_CONST_EXPR_TOKENS_ \
    , \
        BOOST_PP_NIL BOOST_PP_TUPLE_EAT(5) \
    )(id, tpl, result_type, func_name, const_expr)

#endif // #include guard

