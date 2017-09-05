
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_HPP_
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_HPP_

#include <contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <contract/detail/preprocessor/traits/aux_/type.hpp>
#include <contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <contract/detail/preprocessor/traits/aux_/list.hpp>
#include <contract/detail/preprocessor/traits/aux_/name.hpp>
#include <contract/detail/preprocessor/punctuation/has_paren.hpp>
#include <contract/detail/preprocessor/keyword/contract/comma.hpp>
#include <contract/detail/preprocessor/keyword/operator.hpp>
#include <contract/detail/preprocessor/keyword/new.hpp>
#include <contract/detail/preprocessor/keyword/delete.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/detail/is_unary.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_NOT_PAREN_(tokens) \
    BOOST_PP_COMPL(CONTRACT_DETAIL_PP_HAS_PAREN(tokens))

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_NOT_OPERATOR_PAREN_(tokens) \
    BOOST_PP_COMPL(BOOST_PP_BITAND( \
          CONTRACT_DETAIL_PP_KEYWORD_IS_OPERATOR_FRONT(tokens) \
        , CONTRACT_DETAIL_PP_HAS_PAREN( \
                CONTRACT_DETAIL_PP_KEYWORD_OPERATOR_REMOVE_FRONT(tokens)) \
    ))

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_NOT_OPERATOR_NEW_(tokens) \
    BOOST_PP_COMPL(BOOST_PP_BITAND( \
          CONTRACT_DETAIL_PP_KEYWORD_IS_OPERATOR_FRONT(tokens) \
        , CONTRACT_DETAIL_PP_KEYWORD_IS_NEW_FRONT( \
                CONTRACT_DETAIL_PP_KEYWORD_OPERATOR_REMOVE_FRONT(tokens)) \
    ))

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_NOT_OPERATOR_DELETE_( \
        tokens) \
    BOOST_PP_COMPL(BOOST_PP_BITAND( \
          CONTRACT_DETAIL_PP_KEYWORD_IS_OPERATOR_FRONT(tokens) \
        , CONTRACT_DETAIL_PP_KEYWORD_IS_DELETE_FRONT( \
                CONTRACT_DETAIL_PP_KEYWORD_OPERATOR_REMOVE_FRONT(tokens)) \
    ))

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_NOT_OPERATOR_COMMA_( \
        tokens) \
    BOOST_PP_COMPL(BOOST_PP_BITAND( \
          CONTRACT_DETAIL_PP_KEYWORD_IS_OPERATOR_FRONT(tokens) \
        , CONTRACT_DETAIL_PP_KEYWORD_IS_COMMA_FRONT( \
                CONTRACT_DETAIL_PP_KEYWORD_OPERATOR_REMOVE_FRONT(tokens)) \
    ))

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_IS_EMPTY_CHECK_OPERATOR_( \
        next_next_sign) \
    BOOST_PP_BITAND( \
        CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_NOT_OPERATOR_PAREN_( \
                next_next_sign) \
    , BOOST_PP_BITAND( \
        CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_NOT_OPERATOR_NEW_( \
                next_next_sign) \
    , BOOST_PP_BITAND( \
        CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_NOT_OPERATOR_DELETE_( \
                next_next_sign) \
    ,   CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_NOT_OPERATOR_COMMA_( \
                next_next_sign) \
    )))

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_IS_EMPTY_CHECK_NOT_NIL_( \
        next_next_sign) \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_NOT_PAREN_( \
            next_next_sign), \
        CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_IS_EMPTY_CHECK_OPERATOR_ \
    , \
        0 BOOST_PP_TUPLE_EAT(1) \
    )(next_next_sign)

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_IS_EMPTY_CHECK_( \
        next_next_sign) \
    /* result is empty <=> next_next_sign == nil || (next_next_sign != ()... */\
    /* && != opeator(...)... && != operator new... && != operator delete...) */\
    /* (this supports type conversion `operator T()` which has no result) */ \
    BOOST_PP_EXPAND(BOOST_PP_IIF( \
            CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_PAREN(next_next_sign), \
        1 BOOST_PP_TUPLE_EAT(1) \
    , \
        CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_IS_EMPTY_CHECK_NOT_NIL_ \
    )(next_next_sign))

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_IS_EMPTY_PAREN_(sign) \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_IS_EMPTY_CHECK_( \
        CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_LIST( /* next */ \
        CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_NAME( /* next */ \
            sign \
        )) \
    )

#ifndef BOOST_NO_VARIADIC_MACROS
#   define CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_MAYBE_NAME_1TOKEN_SIZE_( \
            ...) \
        CONTRACT_DETAIL_PP_VARIADIC_SIZE(__VA_ARGS__),
#else
#   define CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_MAYBE_NAME_1TOKEN_SIZE_( \
            token) \
        1, /* must always be 1 token `(token)` if no variadics */
#endif

#define CONRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_MAYBE_NAME_1TOKEN_(sign) \
    BOOST_PP_EQUAL(BOOST_PP_TUPLE_ELEM(2, 0, ( \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_MAYBE_NAME_1TOKEN_SIZE_ \
            sign)), 1)

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_MAYBE_NAME_(sign) \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_HAS_PAREN(sign), \
        CONRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_MAYBE_NAME_1TOKEN_ \
    , \
        0 BOOST_PP_TUPLE_EAT(1) \
    )(sign)

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_IS_EMPTY_(sign) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( /* EXPAND for MSVC */ \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_MAYBE_NAME_(sign)), \
        CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_IS_EMPTY_PAREN_ \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_COMMA_FRONT(sign), \
        0 BOOST_PP_TUPLE_EAT(1) \
    , \
        0 BOOST_PP_TUPLE_EAT(1) \
    ))(sign)

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_TRAIT_(sign) \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_IS_EMPTY_(sign), \
        (0, ()) /* empty array for no result type */ \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE \
    )(sign)

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_SIGN_(sign) \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_IS_EMPTY_(sign), \
        sign BOOST_PP_TUPLE_EAT(1) /* no result_type to skip */ \
    , \
        CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TYPE /* skip result_type */ \
    )(sign)

// PROTECTED //

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_RESULT_TYPE(traits_sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_TRAIT_, \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE_SIGN_)

// PUBLIC //

// Expand to `(comma_n, (result_type_token1, ...))` (array for unwrapped
// commas, 0-size array if no result type for constructors and destructors).
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE(func_traits) \
    BOOST_PP_ARRAY_ELEM(10, func_traits)

#endif // #include guard

