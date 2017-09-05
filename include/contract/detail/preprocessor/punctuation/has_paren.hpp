
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_HAS_PAREN_HPP_
#define CONTRACT_DETAIL_PP_HAS_PAREN_HPP_

#include <boost/config.hpp>

// PUBLIC //

#ifndef BOOST_NO_VARIADIC_MACROS

#   include <boost/preprocessor/config/config.hpp>
#   include <boost/preprocessor/detail/check.hpp>

#   if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#       define CONTRACT_DETAIL_PP_HAS_PAREN(tokens) \
            BOOST_PP_CHECK(tokens, CONTRACT_DETAIL_PP_HAS_PAREN_CHECK)
#   else
#       define CONTRACT_DETAIL_PP_HAS_PAREN(tokens) \
            CONTRACT_DETAIL_PP_HAS_PAREN_I(tokens)
#       define CONTRACT_DETAIL_PP_HAS_PAREN_I(tokens) \
            BOOST_PP_CHECK(tokens, CONTRACT_DETAIL_PP_HAS_PAREN_CHECK)
#   endif
#   define CONTRACT_DETAIL_PP_HAS_PAREN_CHECK(...) \
        1 /* variadics handle any arity */
#   define BOOST_PP_CHECK_RESULT_CONTRACT_DETAIL_PP_HAS_PAREN_CHECK \
        0, BOOST_PP_NIL

#else

#   include <boost/preprocessor/detail/is_unary.hpp>

// Expand to 1 iff tokens have parenthesis `(x)...` (only this case is handled
// if no variadic macros), or `(x, y, ...)...`, or etc.
#   define CONTRACT_DETAIL_PP_HAS_PAREN(tokens) \
        BOOST_PP_IS_UNARY(tokens)

#endif

#endif // #include guard

