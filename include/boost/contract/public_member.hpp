
#ifndef BOOST_CONTRACT_PUBLIC_MEMBER_HPP_
#define BOOST_CONTRACT_PUBLIC_MEMBER_HPP_

/** @file */

#include <boost/contract/core/set_precondition_postcondition.hpp>
#include <boost/contract/core/virtual.hpp>
#include <boost/contract/aux_/function/public_member.hpp>
#include <boost/contract/aux_/none.hpp>
/** @cond */
#include <boost/make_shared.hpp>
/** @endcond */

namespace boost { namespace contract {

// For non-virtual of class with no bases.
template<class C>
set_precondition_postcondition public_member(C* obj) {
    return set_precondition_postcondition(boost::make_shared<
        boost::contract::aux::public_member<
            boost::contract::aux::none,
            boost::contract::aux::none,
            C,
            boost::contract::aux::none
        >
    >(0, obj, boost::contract::aux::none::value));
}

// For virtual members of class with no bases.
template<class C>
set_precondition_postcondition public_member(virtual_* v, C* obj) {
    return set_precondition_postcondition(boost::make_shared<
        boost::contract::aux::public_member<
            boost::contract::aux::none,
            boost::contract::aux::none,
            C,
            boost::contract::aux::none
        >
    >(v, obj, boost::contract::aux::none::value));
}

// TODO: Support configurable function arity.
// arity = 0

// For non-virtual members of class with bases.
template<class O, typename F, class C>
set_precondition_postcondition public_member(F, C* obj) {
    return set_precondition_postcondition(boost::make_shared<
        boost::contract::aux::public_member<
            O,
            F,
            C,
            boost::contract::aux::none
        >
    >(0, obj, boost::contract::aux::none::value));
}

// For virtual members of class with bases.
template<class O, typename F, class C>
set_precondition_postcondition public_member(virtual_* v, F, C* obj) {
    return set_precondition_postcondition(boost::make_shared<
        boost::contract::aux::public_member<
            O,
            F,
            C,
            boost::contract::aux::none
        >
    >(v, obj, boost::contract::aux::none::value));
}

// arity = 1

template<class O, typename F, class C, typename A0>
set_precondition_postcondition public_member(F, C* obj, A0& a0) {
    return set_precondition_postcondition(boost::make_shared<
        boost::contract::aux::public_member<
            O,
            F,
            C,
            A0
        >
    >(0, obj, a0));
}

template<class O, typename F, class C, typename A0>
set_precondition_postcondition public_member(virtual_* v, F, C* obj, A0& a0) {
    return set_precondition_postcondition(boost::make_shared<
        boost::contract::aux::public_member<
            O,
            F,
            C,
            A0
        >
    >(v, obj, a0));
}

// TODO: Support configurable arity.

} } // namespace

#endif // #include guard

