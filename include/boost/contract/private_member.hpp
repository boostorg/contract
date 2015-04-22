
#ifndef BOOST_CONTRACT_PRIVATE_MEMBER_HPP_
#define BOOST_CONTRACT_PRIVATE_MEMBER_HPP_

#include <boost/contract/aux_/function/private_member.hpp>
#include <boost/contract/aux_/set/pre_post.hpp>
#include <boost/make_shared.hpp>

// TOOD: On C++11 Clang... these could static_assert enclosing func is not pub?

namespace boost { namespace contract {

boost::contract::aux::set::pre_post private_member() {
    return boost::contract::aux::set::pre_post(boost::make_shared<
            boost::contract::aux::function::private_member>());
}

} } // namespace

#endif // 

