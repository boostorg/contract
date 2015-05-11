
#ifndef BOOST_CONTRACT_PUBLIC_MEMBER_HPP_
#define BOOST_CONTRACT_PUBLIC_MEMBER_HPP_

#include <boost/contract/core/call.hpp>
#include <boost/contract/core/set_precondition_postcondition.hpp>
#include <boost/contract/aux_/function/public_member.hpp>
#include <boost/make_shared.hpp>

namespace boost { namespace contract {

template<class C>
boost::contract::set_precondition_postcondition public_member(
        boost::contract::call const& c, C const* obj) {
    return boost::contract::set_precondition_postcondition(boost::make_shared<
            boost::contract::aux::public_member<C> >(c.call_, obj));
}

template<class C>
boost::contract::set_precondition_postcondition public_member(C const* obj) {
    return boost::contract::set_precondition_postcondition(boost::make_shared<
            boost::contract::aux::public_member<C> >(obj));
}

} } // namespace

#endif // #include guard

