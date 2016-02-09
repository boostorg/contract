
#ifndef BOOST_CONTRACT_FUNCTION_HPP_
#define BOOST_CONTRACT_FUNCTION_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file */

#include <boost/contract/aux_/all_core_headers.hpp>
#if BOOST_CONTRACT_FUNCTIONS || BOOST_CONTRACT_INVARIANTS
    #include <boost/contract/aux_/operation/function.hpp>
#endif

namespace boost { namespace contract {

set_precondition_old_postcondition<> function() {
    // Must #if also on ..._INVARIANTS here because set_... is generic.
    #if BOOST_CONTRACT_FUNCTIONS || BOOST_CONTRACT_INVARIANTS
        return set_precondition_old_postcondition<>(
                new boost::contract::aux::function());
    #else
        return set_precondition_old_postcondition<>();
    #endif
}

} } // namespace

#endif // #include guard

