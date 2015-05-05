
#ifndef BOOST_CONTRACT_VIRTUAL_BODY_HPP_
#define BOOST_CONTRACT_VIRTUAL_BODY_HPP_

#include <boost/contract/aux_/virtual_call.hpp>

namespace boost { namespace contract {

// TODO: Can I use a straight pointer * instead of a smart pointer?

// This type must be initialized when assigned to `0` and it must be efficient
// to pass it as a function parameter and to copy it (like a pointer).
typedef boost::shared_ptr<boost::contract::aux::virtual_call> virtual_body;

} } // namespace

#endif // #include guard

