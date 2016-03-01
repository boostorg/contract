
#ifndef BOOST_CONTRACT_DESTRUCTOR_HPP_
#define BOOST_CONTRACT_DESTRUCTOR_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file */

#include <boost/contract/detail/all_core_headers.hpp>
#if !defined(BOOST_CONTRACT_NO_DESTRUCTORS) || \
        !defined(BOOST_CONTRACT_NO_PRECONDITIONS)
    #include <boost/contract/detail/operation/destructor.hpp>
#endif

namespace boost { namespace contract {

template<class C>
set_old_postcondition<> destructor(C* obj) {
    // Must #if also on ..._PRECONDITIONS here because set_... is generic.
    #if !defined(BOOST_CONTRACT_NO_DESTRUCTORS) || \
            !defined(BOOST_CONTRACT_NO_PRECONDITIONS)
        return set_old_postcondition<>(
                new boost::contract::detail::destructor<C>(obj));
    #else
        return set_old_postcondition<>();
    #endif
}

} } // namespace

#endif // #include guard

