
#ifndef BOOST_CONTRACT_PROTECTED_MEMBER_HPP_
#define BOOST_CONTRACT_PROTECTED_MEMBER_HPP_

/** @file */

#include <boost/contract/core/set_precondition_postcondition.hpp>
#include <boost/contract/aux_/function/protected_member.hpp>
/** @cond */
#include <boost/make_shared.hpp>
/** @endcond */

namespace boost { namespace contract {

set_precondition_postcondition<> protected_member() {
    return set_precondition_postcondition<>(boost::make_shared<
            boost::contract::aux::protected_member>());
}

} } // namespace

#endif // 

