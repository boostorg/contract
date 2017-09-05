
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_IS_VARIADIC_HPP_
#define CONTRACT_DETAIL_PP_IS_VARIADIC_HPP_

// Do not use Boost.PP variadic because they use a different config macro.
#include <boost/config.hpp>
#ifndef BOOST_NO_VARIADIC_MACROS

#include <contract/detail/preprocessor/variadic/size.hpp>
#include <contract/detail/preprocessor/variadic/eat.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
// `IS_UNARY` not working on Borland and other pp which have no variadic anyway.
#include <boost/preprocessor/detail/is_unary.hpp>

// PRIVATE // 

// Define own version of EXPAND for reentrancy.
#if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC() && \
        ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_DMC()
#   define CONTRACT_DETAIL_PP_IS_VARIADIC_EXPAND_(x) \
        CONTRACT_DETAIL_PP_IS_VARIADIC_EXPAND_I_(x)
#else
#   define CONTRACT_DETAIL_PP_IS_VARIADIC_EXPAND_(x) \
        CONTRACT_DETAIL_PP_IS_VARIADIC_EXPAND_OO_((x))
#   define CONTRACT_DETAIL_PP_IS_VARIADIC_EXPAND_OO_(par) \
        CONTRACT_DETAIL_PP_IS_VARIADIC_EXPAND_I_ ## par
#endif
#define CONTRACT_DETAIL_PP_IS_VARIADIC_EXPAND_I_(x) x
        
#define CONTRACT_DETAIL_PP_IS_VARIADIC_UNARY_SINGLE_TOKEN_(tokens) \
    BOOST_PP_EQUAL(1, CONTRACT_DETAIL_PP_VARIADIC_SIZE tokens)
    
#define CONTRACT_DETAIL_PP_IS_VARIADIC_UNARY_SIGNLE_SPLIT_(...) \
    (__VA_ARGS__),

// Precondition: tokens = `(...) ...`.
#define CONTRACT_DETAIL_PP_IS_VARIADIC_UNARY_SIGNLE_(tokens) \
    CONTRACT_DETAIL_PP_IS_VARIADIC_UNARY_SINGLE_TOKEN_( \
        BOOST_PP_TUPLE_ELEM(2, 0, \
                (CONTRACT_DETAIL_PP_IS_VARIADIC_UNARY_SIGNLE_SPLIT_ tokens)) \
    )

#define CONTRACT_DETAIL_PP_IS_VARIADIC_UNARY_(tokens) \
    CONTRACT_DETAIL_PP_IS_VARIADIC_EXPAND_( /* EXPAND for MSVC */ \
        BOOST_PP_IIF(CONTRACT_DETAIL_PP_HAS_PAREN(tokens), \
            CONTRACT_DETAIL_PP_IS_VARIADIC_UNARY_SIGNLE_ \
        , \
            0 BOOST_PP_TUPLE_EAT(1) \
        )(tokens) \
    )

// Precondition: size == 1 AND 1st token is unary.
#define CONTRACT_DETAIL_PP_IS_VARIADIC_NOT_UNARY_2ND_(tokens) \
    BOOST_PP_COMPL(CONTRACT_DETAIL_PP_IS_VARIADIC_UNARY_( \
        CONTRACT_DETAIL_PP_VARIADIC_EAT tokens \
        (1) /* handle empty (1st is unary so all unary) */ \
    ))

// Precondition: size == 1.
#define CONTRACT_DETAIL_PP_IS_VARIADIC_NOT_UNARY_1ST_(tokens) \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_IS_VARIADIC_UNARY_(tokens), \
        CONTRACT_DETAIL_PP_IS_VARIADIC_NOT_UNARY_2ND_ \
    , \
        1 BOOST_PP_TUPLE_EAT(1) /* 1st not unary thus not seq and variadic */ \
    )(tokens)

#define CONTRACT_DETAIL_PP_IS_VARIADIC_(size, ...) \
    BOOST_PP_IIF(BOOST_PP_EQUAL(size, 1), \
        CONTRACT_DETAIL_PP_IS_VARIADIC_NOT_UNARY_1ST_ \
    , /* size == 0 or size > 1 */ \
        1 CONTRACT_DETAIL_PP_VARIADIC_EAT \
    )(__VA_ARGS__)

// PUBLIC //

#define CONTRACT_DETAIL_PP_IS_VARIADIC(...) \
    CONTRACT_DETAIL_PP_IS_VARIADIC_( \
            CONTRACT_DETAIL_PP_VARIADIC_SIZE_MAYBE_EMPTY(__VA_ARGS__), \
            __VA_ARGS__)

#endif

#endif // #include guard

