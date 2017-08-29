
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_VARIADIC_SIZE_HPP_
#define CONTRACT_DETAIL_PP_VARIADIC_SIZE_HPP_

// Do not use Boost.PP variadic because they use a different config macro.
#include <boost/config.hpp>
#ifndef BOOST_NO_VARIADIC_MACROS

#include <contract/detail/preprocessor/variadic/eat.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/cat.hpp>
// `IS_UNARY` not working on Borland and other pp which have no variadic anyway.
#include <boost/preprocessor/detail/is_unary.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_VARIADIC_SIZE_1OR0_TOKEN_(maybe_empty) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY(maybe_empty (/*expand empty */) ), 0, 1)

#define CONTRACT_DETAIL_PP_VARIADIC_SIZE_1OR0_(maybe_empty) \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_HAS_PAREN(maybe_empty(/*exapnd empty */)), \
        1 BOOST_PP_TUPLE_EAT(1) \
    , \
        CONTRACT_DETAIL_PP_VARIADIC_SIZE_1OR0_TOKEN_ \
    )(maybe_empty)

#define CONTRACT_DETAIL_PP_VARIADIC_SIZE_HANDLE_EMPTY_(size, ...) \
    BOOST_PP_IIF(BOOST_PP_EQUAL(size, 1), \
        CONTRACT_DETAIL_PP_VARIADIC_SIZE_1OR0_ \
    , \
        size \
        CONTRACT_DETAIL_PP_VARIADIC_EAT \
    )(__VA_ARGS__ BOOST_PP_EMPTY)

// PUBLIC //

#if BOOST_MSVC
#   define CONTRACT_DETAIL_PP_VARIADIC_SIZE(...) \
        BOOST_PP_CAT(CONTRACT_DETAIL_PP_VARIADIC_SIZE_I_(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,),)
#else // MSVC
#   define CONTRACT_DETAIL_PP_VARIADIC_SIZE(...) \
        CONTRACT_DETAIL_PP_VARIADIC_SIZE_I_(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,)
#endif // MSVC
#define CONTRACT_DETAIL_PP_VARIADIC_SIZE_I_(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63, size, ...) size

#define CONTRACT_DETAIL_PP_VARIADIC_SIZE_MAYBE_EMPTY(...) \
    CONTRACT_DETAIL_PP_VARIADIC_SIZE_HANDLE_EMPTY_( \
            CONTRACT_DETAIL_PP_VARIADIC_SIZE(__VA_ARGS__), __VA_ARGS__)

#endif

#endif // #include guard

