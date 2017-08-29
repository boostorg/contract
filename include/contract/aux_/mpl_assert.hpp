
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_MPL_ASSERT_HPP_
#define CONTRACT_AUX_MPL_ASSERT_HPP_

#include <boost/mpl/assert.hpp>
#include <boost/preprocessor/cat.hpp>

// PRIVATE //

#define CONTRACT_AUX_MPL_ASSERT_MSG_(counter, condition, message, types) \
    /* unfortunately, need to use Boost.MPL implementation detail */ \
    /* to pass unique ID (not just __LINE__) so this macro can be expanded */ \
    /* multiple times on the same line if with different IDs */ \
    BOOST_MPL_ASSERT_MSG_IMPL( \
            BOOST_PP_CAT(BOOST_PP_CAT(message, _id_), counter), \
            condition, message, types)

// PUBLIC //

// Allow to expand multiple assert macros on same line (without name clashes).
#define CONTRACT_AUX_MPL_ASSERT_MSG(condition, message, types) \
    CONTRACT_AUX_MPL_ASSERT_MSG_( \
            BOOST_MPL_AUX_PP_COUNTER(), /* uses Boost.MPL impl detail */ \
            condition, message, types)

#endif // #include guard

