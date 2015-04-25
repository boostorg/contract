
#ifndef BOOST_CONTRACT_PROTECTED_MEMBER_HPP_
#define BOOST_CONTRACT_PROTECTED_MEMBER_HPP_

#include <boost/contract/set/precondition_postcondition.hpp>
#include <boost/contract/aux_/function/protected_member.hpp>
#include <boost/make_shared.hpp>

// TOOD: On C++11 Clang... these could static_assert enclosing func is not pub?

namespace boost { namespace contract {

boost::contract::set::precondition_postcondition protected_member() {
    return boost::contract::set::precondition_postcondition(boost::make_shared<
            boost::contract::aux::function::protected_member>());
}

} } // namespace

#endif // 

