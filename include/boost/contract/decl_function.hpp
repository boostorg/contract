
#ifndef BOOST_CONTRACT_DECL_FUNCTION_HPP_
#define BOOST_CONTRACT_DECL_FUNCTION_HPP_

/** @file */

#include <boost/contract/core/decl.hpp>
#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/aux_/function/decl_free_function.hpp>
#include <boost/contract/aux_/function/decl_member_function.hpp>
#include <boost/contract/aux_/none.hpp>
/** @cond */
#include <boost/make_shared.hpp>
/** @endcond */

namespace boost { namespace contract {

// NOTE: `f` last arg otherwise some compilers (MSVC) cannot always deduce it.

// TODO: Support configurable function arity.

// Free function.

set_nothing decl_function(void (* f)(decl)) {
    return set_nothing(boost::make_shared<
        boost::contract::aux::decl_free_function<
            void (*)(decl),
            boost::contract::aux::none, boost::contract::aux::none
        >
    >(f, boost::contract::aux::none::value, boost::contract::aux::none::value));
}

template<typename A0>
set_nothing decl_function(A0 const& a0, void (* f)(A0 const&, decl)) {
    return set_nothing(boost::make_shared<
        boost::contract::aux::decl_free_function<
            void (*)(A0 const&, decl),
            A0, boost::contract::aux::none
        >
    >(f, a0, boost::contract::aux::none::value));
}

template<typename A0, typename A1>
set_nothing decl_function(A0 const& a0, A1 const& a1,
        void (* f)(A0 const&, A1 const&, decl)) {
    return set_nothing(boost::make_shared<
        boost::contract::aux::decl_free_function<
            void (*)(A0 const&, A1 const&, decl),
            A0, A1
        >
    >(f, a0, a1));
}

// Member function (constructor and destructor included).

template<class C>
set_nothing decl_function(C const* obj, void (C::* f)(decl) const) {
    return set_nothing(boost::make_shared<
        boost::contract::aux::decl_member_function<
            void (C::*)(decl) const,
            C, boost::contract::aux::none, boost::contract::aux::none
        >
    >(f, obj, boost::contract::aux::none::value,
            boost::contract::aux::none::value));
}

template<class C, typename A0>
set_nothing decl_function(C const* obj, A0 const& a0,
        void (C::* f)(A0 const&, decl) const) {
    return set_nothing(boost::make_shared<
        boost::contract::aux::decl_member_function<
            void (C::*)(A0 const&, decl) const,
            C, A0, boost::contract::aux::none
        >
    >(f, obj, a0, boost::contract::aux::none::value));
}

template<class C, typename A0, typename A1>
set_nothing decl_function(C const* obj, A0 const& a0, A1 const& a1,
        void (C::* f)(A0 const&, A1 const&, decl) const) {
    return set_nothing(boost::make_shared<
        boost::contract::aux::decl_member_function<
            void (C::*)(A0 const&, A1 const&, decl) const,
            C, A0, A1
        >
    >(f, obj, a0, a1));
}

} } // namespace

#endif // #include guard

