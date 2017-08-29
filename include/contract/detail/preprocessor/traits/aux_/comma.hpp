
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_HPP_
#define CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_HPP_

#include <contract/detail/preprocessor/tuple/split.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_ARRAY_(size_tuple_rest) \
    (BOOST_PP_TUPLE_ELEM(3, 0, size_tuple_rest), \
            BOOST_PP_TUPLE_ELEM(3, 1, size_tuple_rest))

#define CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_AFTER_(size_tuple_rest) \
    BOOST_PP_TUPLE_ELEM(3, 2, size_tuple_rest)

#define CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_SPLIT_(size) \
    size, CONTRACT_DETAIL_PP_TUPLE_SPLIT(size) /* split */

#define CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_comma(comma_count) \
    /* tuple size is number of commas + 1 */ \
    CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_SPLIT_(BOOST_PP_INC(comma_count))
    
// tokens: `comma(n) (token0, ..., token_n) ...`
#define CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_( \
        after01, no_comma_macro, tokens) \
    BOOST_PP_IIF(after01, \
        CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_AFTER_ \
    , \
        CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_ARRAY_ \
    )((BOOST_PP_CAT(CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_, tokens)))
    
#ifndef BOOST_NO_VARIADIC_MACROS
#   define CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_PAREN_SPLIT_(...) \
        CONTRACT_DETAIL_PP_VARIADIC_SIZE(__VA_ARGS__), (__VA_ARGS__), /*split*/
#else
#   define CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_PAREN_SPLIT_(token) \
        1, (token), /* split */
#endif

// tokens: `(token0, ...) ...`
#define CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_PAREN_( \
        after01, no_comma_macro, tokens) \
    BOOST_PP_IIF(after01, \
        CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_AFTER_ \
    , \
        CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_ARRAY_ \
    )((CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_PAREN_SPLIT_ tokens))
        
#define CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_NOT_AFTER_(rest) \
    rest

#define CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_NOT_ARRAY_(token) \
    /* training EMPTY() so MSVC properly handle when token is empty */ \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY(token BOOST_PP_EMPTY()), \
        (0, ()) /* 0-size array for empty */ \
    , \
        (1, (token)) \
    )

#define CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_NOT_( \
        after01, no_comma_macro, tokens) \
    BOOST_PP_IIF(after01, \
        CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_NOT_AFTER_ \
    , \
        CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_NOT_ARRAY_ \
    )(no_comma_macro(tokens))

#define CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_DISPATCH_( \
        after01, no_comma_macro, tokens) \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_COMMA_FRONT(tokens), \
        CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_ \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_HAS_PAREN(tokens), \
        CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_PAREN_ \
    , \
        CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_NOT_ \
    ))(after01, no_comma_macro, tokens)

// PROTECTED //

#define CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA(no_comma_macro, tokens) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_DISPATCH_( \
            0 /* array, not after */, no_comma_macro, tokens)

#define CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_COMMA(no_comma_macro, tokens) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_DISPATCH_( \
            1 /* after */, no_comma_macro, tokens)

#endif // #include guard

