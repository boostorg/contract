
#ifndef BOOST_CONTRACT_PRIVATE_MEMBER_HPP_
#define BOOST_CONTRACT_PRIVATE_MEMBER_HPP_

#include <boost/contract/core/var.hpp> // Here so user can store contract.
#include <boost/contract/core/set_precondition_postcondition.hpp>
#include <boost/contract/aux_/function/private_member.hpp>
#include <boost/make_shared.hpp>

// TOOD: On C++11 Clang... these could static_assert enclosing func is not pub?

namespace boost { namespace contract {

boost::contract::set_precondition_postcondition private_member() {
    return boost::contract::set_precondition_postcondition(boost::make_shared<
            boost::contract::aux::function::private_member>());
}

} } // namespace

#endif // 

