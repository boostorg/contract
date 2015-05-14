
#ifndef BOOST_CONTRACT_PUBLIC_MEMBER_HPP_
#define BOOST_CONTRACT_PUBLIC_MEMBER_HPP_

/** @file */

#include <boost/contract/core/call.hpp>
#include <boost/contract/core/set_precondition_postcondition.hpp>
#include <boost/contract/aux_/function/public_member.hpp>
#include <boost/contract/aux_/none.hpp>
/** @cond */
#include <boost/make_shared.hpp>
/** @endcond */

namespace boost { namespace contract {

template<class C>
boost::contract::set_precondition_postcondition public_member(
        boost::contract::call const& c, C const* obj) {
    return boost::contract::set_precondition_postcondition(boost::make_shared<
        boost::contract::aux::public_member<boost::contract::aux::none, C,
                boost::contract::aux::none>
    >(c.call_, obj, boost::contract::aux::none::value));
}

template<class C>
boost::contract::set_precondition_postcondition public_member(C const* obj) {
    return boost::contract::set_precondition_postcondition(boost::make_shared<
        boost::contract::aux::public_member<boost::contract::aux::none, C,
                boost::contract::aux::none>
    >(obj, boost::contract::aux::none::value));
}

template<class I, class C, typename A0>
boost::contract::set_precondition_postcondition public_member(C const* obj,
        A0 const& a0) {
    return boost::contract::set_precondition_postcondition(boost::make_shared<
        boost::contract::aux::public_member<I, C, A0>
    >(obj, a0));
}

} } // namespace

#endif // #include guard

