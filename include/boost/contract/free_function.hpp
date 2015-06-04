
#ifndef BOOST_CONTRACT_FREE_FUNCTION_HPP_
#define BOOST_CONTRACT_FREE_FUNCTION_HPP_

/** @file */

#include <boost/contract/core/set_precondition_postcondition.hpp>
#include <boost/contract/aux_/function/free_function.hpp>
/** @cond */
#include <boost/make_shared.hpp>
/** @endcond */

namespace boost { namespace contract {

set_precondition_postcondition<> free_function() {
    return set_precondition_postcondition<>(boost::make_shared<
            boost::contract::aux::free_function>());
}

} } // namespace

#endif // #include guard

