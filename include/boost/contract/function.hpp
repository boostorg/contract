
#ifndef BOOST_CONTRACT_FUNCTION_HPP_
#define BOOST_CONTRACT_FUNCTION_HPP_

/** @file */

#include <boost/contract/core/set_precondition_old_postcondition.hpp>
#include <boost/contract/aux_/operation/function.hpp>

namespace boost { namespace contract {

set_precondition_old_postcondition<> function() {
    // Must check ..._INVARIANTS here because set_... is generic.
    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        return set_precondition_old_postcondition<>(
                new boost::contract::aux::function());
    #else
        return set_precondition_old_postcondition<>();
    #endif
}

} } // namespace

#endif // #include guard

