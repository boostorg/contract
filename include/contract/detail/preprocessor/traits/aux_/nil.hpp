
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_HPP_
#define CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_HPP_

#include <contract/detail/preprocessor/variadic/size.hpp>
#include <contract/detail/preprocessor/variadic/eat.hpp>
#include <contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <contract/detail/preprocessor/keyword/facilities/remove.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/config.hpp>

// PROTECTED //

// Make sure NIL symbGl is not defined by users.
#ifdef CONTRACT_DETAIL_PP_TRAITS_AUX_NIL
#   error "internal macro CONTRACT_DETAIL_PP_TRAITS_AUX_NIL must be undefined"
#endif

// These are not local macros -- DO NOT #UNDEF.
#define CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_IS_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL \
    (1) /* unary */
#define \
CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL \
    /* nothing */

#define CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_FRONT(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_IS_)

// Or directly PP_CAT with CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_ (faster).
#define CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_FRONT(tokens) \
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_FRONT, \
            CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_)

#ifndef BOOST_NO_VARIADIC_MACROS
#   define CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_(...) \
        BOOST_PP_IIF(BOOST_PP_EQUAL( \
                CONTRACT_DETAIL_PP_VARIADIC_SIZE(__VA_ARGS__), 1), \
            CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_FRONT \
        , \
            0 CONTRACT_DETAIL_PP_VARIADIC_EAT \
        )(__VA_ARGS__)
#   define CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_SPLIT_(...) \
        (__VA_ARGS__), /* comma split remaining tokens */
#   define CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_PAREN_(paren_tokens) \
        BOOST_PP_EXPAND( \
            CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_ \
            BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_EXPAND( \
                (CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_SPLIT_ paren_tokens) \
            )) \
        )
// Expand to 1 iff `(nil)...`.
#   define CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_PAREN(...) \
        BOOST_PP_IIF(CONTRACT_DETAIL_PP_HAS_PAREN(__VA_ARGS__), \
            CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_PAREN_ \
        , \
            CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_FRONT \
        )(__VA_ARGS__)
// Expand to 1 iff `nil, ...`.
#   define CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL(...) \
        CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(CONTRACT_DETAIL_PP_VARIADIC_SIZE( \
                    __VA_ARGS__), 0 /* first variadic elem */, (__VA_ARGS__)))
#else
#   define CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_PAREN_(tokens) \
        CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_FRONT(tokens)
#   define CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_(paren_tokens) \
        BOOST_PP_EXPAND( \
             CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_PAREN_ paren_tokens)
#   define CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_PAREN(tokens) \
        BOOST_PP_IIF(BOOST_PP_IS_UNARY(tokens), \
            CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_ \
        , \
            0 BOOST_PP_TUPLE_EAT(1) \
        )(tokens)
#   define CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL(tokens) \
        CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_FRONT(tokens)
#endif

#endif // #include guard

