
#ifndef BOOST_CONTRACT_PRIVATE_FUNCTION_HPP_
#define BOOST_CONTRACT_PRIVATE_FUNCTION_HPP_

/** @file */

#include <boost/contract/core/set_precondition_postcondition.hpp>
#include <boost/contract/aux_/function/private_function.hpp>
/** @cond */
#include <boost/make_shared.hpp>
/** @endcond */

namespace boost { namespace contract {

set_precondition_postcondition<> private_function() {
    return set_precondition_postcondition<>(boost::make_shared<
            boost::contract::aux::private_function>());
}

} } // namespace

#endif // 

