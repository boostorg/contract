
#ifndef BOOST_CONTRACT_PROTECTED_MEMBER_HPP_
#define BOOST_CONTRACT_PROTECTED_MEMBER_HPP_

#include <boost/contract/type.hpp>
#include <boost/contract/aux_/protected_member.hpp>
#include <boost/make_shared.hpp>

// TOOD: On C++11 Clang... these could static_assert enclosing func is not pub?

namespace boost { namespace contract {

boost::contract::type protected_member() {
    return boost::contract::type(boost::make_shared<boost::contract::aux::
            protected_member>());
}

} } // namespace

#endif // 

