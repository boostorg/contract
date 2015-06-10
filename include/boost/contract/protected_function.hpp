
#ifndef BOOST_CONTRACT_PROTECTED_FUNCTION_HPP_
#define BOOST_CONTRACT_PROTECTED_FUNCTION_HPP_

/** @file */

#include <boost/contract/core/set_precondition_postcondition.hpp>
#include <boost/contract/aux_/function/protected_function.hpp>
/** @cond */
#include <boost/make_shared.hpp>
/** @endcond */

namespace boost { namespace contract {

set_precondition_postcondition<> protected_function() {
    return set_precondition_postcondition<>(boost::make_shared<
            boost::contract::aux::protected_function>());
}

} } // namespace

#endif // 

