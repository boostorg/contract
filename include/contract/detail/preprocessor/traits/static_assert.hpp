
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_STATIC_ASSERT_TRAITS_HPP_
#define CONTRACT_DETAIL_PP_STATIC_ASSERT_TRAITS_HPP_

#include <contract/detail/preprocessor/keyword/cxx11/static_assert.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

// Where static_assert_instruction is `static_assert(condition, error)`.
#define CONTRACT_DETAIL_PP_STATIC_ASSERT_TRAITS(static_assert_instruction) \
    CONTRACT_DETAIL_PP_KEYWORD_STATIC_ASSERT_REMOVE_FRONT( \
            static_assert_instruction)

#define CONTRACT_DETAIL_PP_STATIC_ASSERT_TRAITS_CONDITION( \
        static_assert_traits) \
    BOOST_PP_TUPLE_ELEM(2, 0, static_assert_traits)
    
#define CONTRACT_DETAIL_PP_STATIC_ASSERT_TRAITS_ERROR( \
        static_assert_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, static_assert_traits)

#endif // #include guard

