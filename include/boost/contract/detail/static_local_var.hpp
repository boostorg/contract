
#ifndef BOOST_CONTRACT_DETAIL_STATIC_LOCAL_VAR_HPP_
#define BOOST_CONTRACT_DETAIL_STATIC_LOCAL_VAR_HPP_

// Copyright (C) 2008-2017 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/none.hpp>

namespace boost { namespace contract { namespace detail {

// This is used to hold the state of this library (already checking assertions,
// failure handers, mutexes, etc.). Local static variables are used instead of
// global or class-level static variables to avoid ODR errors when this library
// is used as header-only.

template<typename Tag, typename T, typename Init = none*, Init init = Init()>
struct static_local_var {
    static T& ref() {
        static T data(init); // Init same as or implicitly convertible to T.
        return data;
    }
};

template<typename Tag, typename T>
struct static_local_var<Tag, T> {
    static T& ref() {
        static T data; // Use T's default constructor (instead of init).
        return data;
    }
};

} } } // namespace
       
#endif // #include guard

