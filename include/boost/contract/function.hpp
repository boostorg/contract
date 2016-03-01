
#ifndef BOOST_CONTRACT_FUNCTION_HPP_
#define BOOST_CONTRACT_FUNCTION_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file */

#include <boost/contract/detail/all_core_headers.hpp>
#if !defined(BOOST_CONTRACT_NO_FUNCTIONS) || \
        !defined(BOOST_CONTRACT_NO_INVARIANTS)
    #include <boost/contract/detail/operation/function.hpp>
#endif

namespace boost { namespace contract {

set_precondition_old_postcondition<> function() {
    // Must #if also on ..._INVARIANTS here because set_... is generic.
    #if !defined(BOOST_CONTRACT_NO_FUNCTIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        return set_precondition_old_postcondition<>(
                new boost::contract::detail::function());
    #else
        return set_precondition_old_postcondition<>();
    #endif
}

} } // namespace

#endif // #include guard

