
#ifndef BOOST_CONTRACT_FUNCTION_HPP_
#define BOOST_CONTRACT_FUNCTION_HPP_

/** @file */

#include <boost/contract/core/set_precondition_old_postcondition.hpp>
#include <boost/contract/aux_/operation/function.hpp>
/** @cond */
#include <boost/make_shared.hpp>
/** @endcond */

namespace boost { namespace contract {

set_precondition_old_postcondition<> function() {
    return set_precondition_old_postcondition<>(boost::make_shared<
            boost::contract::aux::function>());
}

} } // namespace

#endif // #include guard

