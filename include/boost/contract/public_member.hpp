
#ifndef BOOST_CONTRACT_PUBLIC_MEMBER_HPP_
#define BOOST_CONTRACT_PUBLIC_MEMBER_HPP_

/** @file */

#include <boost/contract/core/set_precondition_postcondition.hpp>
#include <boost/contract/core/virtual.hpp>
#include <boost/contract/aux_/function/public_member.hpp>
#include <boost/contract/aux_/function/public_static_member.hpp>
#include <boost/contract/aux_/none.hpp>
/** @cond */
#include <boost/make_shared.hpp>
/** @endcond */

namespace boost { namespace contract {

// For public static member functions.
template<class C>
set_precondition_postcondition<> public_member() {
    return set_precondition_postcondition<>(boost::make_shared<
            boost::contract::aux::public_static_member<C> >());
}

// For non-virtual of class with no bases.
template<class C>
set_precondition_postcondition<> public_member(C* obj) {
    return set_precondition_postcondition<>(boost::make_shared<
        boost::contract::aux::public_member<
            boost::contract::aux::none,
            boost::contract::aux::none,
            boost::contract::aux::none,
            C,
            boost::contract::aux::none
        >
    >(0, obj, boost::contract::aux::none::value,
            boost::contract::aux::none::value));
}

// For virtual members of class with no bases.
template<class C>
set_precondition_postcondition<> public_member(virtual_* v, C* obj) {
    return set_precondition_postcondition<>(boost::make_shared<
        boost::contract::aux::public_member<
            boost::contract::aux::none,
            boost::contract::aux::none,
            boost::contract::aux::none,
            C,
            boost::contract::aux::none
        >
    >(v, obj, boost::contract::aux::none::value,
            boost::contract::aux::none::value));
}

// TODO: R should be specified *only* when v is present. If F present but not
// v then R should NOT be specified. Because an overriding functions must
// always use v even if no longer decl virtual so to overload correct func
// from base class with v param (otherwise most compilers will give a warning
// and overloading will not work) so "virtual result" R never needed unless v
// is present... actually, this meas also F is there only when v is there!
//
//      O, [R], F allowed only when v is present!
//

// For virtual members of class with no bases.
template<typename R, class C>
set_precondition_postcondition<R> public_member(virtual_* v, R& r, C* obj) {
    return set_precondition_postcondition<R>(boost::make_shared<
        boost::contract::aux::public_member<
            boost::contract::aux::none,
            R,
            boost::contract::aux::none,
            C,
            boost::contract::aux::none
        >
    >(v, obj, r, boost::contract::aux::none::value));
}

// TODO: Support configurable function arity.
// arity = 0

// For non-virtual members of class with bases.
template<class O, typename F, class C>
set_precondition_postcondition<> public_member(F, C* obj) {
    return set_precondition_postcondition<>(boost::make_shared<
        boost::contract::aux::public_member<
            O,
            boost::contract::aux::none,
            F,
            C,
            boost::contract::aux::none
        >
    >(0, obj, boost::contract::aux::none::value));
}

// For virtual members of class with bases.
template<class O, typename F, class C>
set_precondition_postcondition<> public_member(virtual_* v, F, C* obj) {
    return set_precondition_postcondition<>(boost::make_shared<
        boost::contract::aux::public_member<
            O,
            boost::contract::aux::none,
            F,
            C,
            boost::contract::aux::none
        >
    >(v, obj, boost::contract::aux::none::value,
            boost::contract::aux::none::value));
}

// arity = 1

template<class O, typename F, class C, typename A0>
set_precondition_postcondition<> public_member(F, C* obj, A0& a0) {
    return set_precondition_postcondition<>(boost::make_shared<
        boost::contract::aux::public_member<
            O,
            boost::contract::aux::none,
            F,
            C,
            A0
        >
    >(0, obj, a0));
}

template<class O, typename F, class C, typename A0>
set_precondition_postcondition<boost::contract::aux::none> public_member(
        virtual_* v, F, C* obj, A0& a0) {
    return set_precondition_postcondition<boost::contract::aux::none>(
            boost::make_shared<
        boost::contract::aux::public_member<
            O,
            boost::contract::aux::none,
            F,
            C,
            A0
        >
    >(v, obj, boost::contract::aux::none::value, a0));
}

template<class O, typename R, typename F, class C, typename A0>
set_precondition_postcondition<R> public_member(
        virtual_* v, R& r, F, C* obj, A0& a0) {
    return set_precondition_postcondition<R>(boost::make_shared<
        boost::contract::aux::public_member<
            O,
            R,
            F,
            C,
            A0
        >
    >(v, obj, r, a0));
}

// TODO: Support configurable arity.

} } // namespace

#endif // #include guard

