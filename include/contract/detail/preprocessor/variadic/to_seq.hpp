
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_VARIADIC_TO_SEQ_HPP_
#define CONTRACT_DETAIL_PP_VARIADIC_TO_SEQ_HPP_

// Do not use Boost.PP variadic because they use a different config macro.
#include <boost/config.hpp>
#ifndef BOOST_NO_VARIADIC_MACROS

#include <contract/detail/preprocessor/variadic/is.hpp>
#include <contract/detail/preprocessor/variadic/size.hpp>
#include <contract/detail/preprocessor/variadic/rem.hpp>
#include <contract/detail/preprocessor/variadic/eat.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/if.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_VARIADIC_TO_SEQ_(...) \
    BOOST_PP_TUPLE_TO_SEQ(CONTRACT_DETAIL_PP_VARIADIC_SIZE(__VA_ARGS__), \
            (__VA_ARGS__))

#define CONTRACT_DETAIL_PP_VARIADIC_TO_SEQ_NOT_EMPTY_(...) \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_IS_VARIADIC(__VA_ARGS__), \
        CONTRACT_DETAIL_PP_VARIADIC_TO_SEQ_ \
    , \
        CONTRACT_DETAIL_PP_VARIADIC_REM \
    )(__VA_ARGS__)

// PUBLIC //

// Expand to `(arg0)(arg1)...` is __VA_ARGS__ is `arg0, arg1, ...` or already
// `(arg0)(arg1)...`, if __VA_ARGS__ is empty `` expand to `empty_seq`.
#define CONTRACT_DETAIL_PP_VARIADIC_TO_SEQ(empty_seq, ...) \
    BOOST_PP_IF(CONTRACT_DETAIL_PP_VARIADIC_SIZE_MAYBE_EMPTY(__VA_ARGS__), \
        CONTRACT_DETAIL_PP_VARIADIC_TO_SEQ_NOT_EMPTY_ \
    , \
        empty_seq CONTRACT_DETAIL_PP_VARIADIC_EAT \
    )(__VA_ARGS__)

#endif

#endif // #include guard

