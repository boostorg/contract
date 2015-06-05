
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

// For static members.
template<class C>
set_precondition_postcondition<> public_member() {
    return set_precondition_postcondition<>(boost::make_shared<
            boost::contract::aux::public_static_member<C> >());
}

// For non-virtual, non-overriding members.
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
    >(static_cast<boost::contract::virtual_*>(0), obj, boost::contract::aux::
            none::value, boost::contract::aux::none::value));
}

// NOTE: O and R (optionally) allowed only when v is present because:
// * An overriding func must override a base func declared virtual so with
//   v extra param, thus the overriding func must also always have v (i.e., O
//   might be present only if v is also present).
//   However, the first appearing virtual func (e.g., in root class) will not
//   override any previously declared virtual func so does not need O (i.e., O
//   always optional).
//   Furthermore, F needs to be specified only together with O.
// * R is only used for virtual functions (i.e., R might be present only if v
//   is also present).
//   However, R is never specified, not even for virtual functions, when the
//   return type is void (i.e., R always optional).

// For virtual, non-overriding, void members.
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

// For virtual, non-overriding, non-void members.
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

/* Overriding (arity = 0) */

// For virtual, overriding, void members.
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

// For virtual, overriding, non-void members of class with bases.
template<class O, typename R, typename F, class C>
set_precondition_postcondition<R> public_member(virtual_* v, R& r, F, C* obj) {
    return set_precondition_postcondition<R>(boost::make_shared<
        boost::contract::aux::public_member<
            O,
            R,
            F,
            C,
            boost::contract::aux::none
        >
    >(v, obj, r, boost::contract::aux::none::value));
}

/* Overriding (arity = 1) */

template<class O, typename F, class C, typename A0>
set_precondition_postcondition<> public_member(
        virtual_* v, F, C* obj, A0& a0) {
    return set_precondition_postcondition<>(boost::make_shared<
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

