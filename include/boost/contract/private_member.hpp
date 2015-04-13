
#ifndef BOOST_CONTRACT_PRIVATE_MEMBER_HPP_
#define BOOST_CONTRACT_PRIVATE_MEMBER_HPP_

#include <boost/contract/type.hpp>
#include <boost/contract/aux_/function_key.hpp>
#include <boost/make_shared.hpp>

// TOOD: On C++11 Clang... these could static_assert enclosing func is not pub?

namespace boost { namespace contract {

boost::contract::type private_member() {
    return boost::contract::type(boost::make_shared<boost::contract::aux::
            function<boost;:contract::aux::private_member> >());
}

} } // namespace

#endif // 

