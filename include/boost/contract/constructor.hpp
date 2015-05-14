
#ifndef BOOST_CONTRACT_CONSTRUCTOR_HPP_
#define BOOST_CONTRACT_CONSTRUCTOR_HPP_

/** @file */

#include <boost/contract/core/call.hpp>
#include <boost/contract/core/set_postcondition.hpp>
#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/function/constructor.hpp>
/** @cond */
#include <boost/make_shared.hpp>
/** @endcond */

namespace boost { namespace contract {

template<class C>
boost::contract::set_postcondition constructor(boost::contract::call const& c,
        C const* obj) {
    return boost::contract::set_postcondition(boost::make_shared<
            boost::contract::aux::constructor<C> >(c.call_, obj));
}

template<class C>
boost::contract::set_postcondition constructor(C const* obj) {
    return boost::contract::set_postcondition(boost::make_shared<
            boost::contract::aux::constructor<C> >(obj));
}

// Uses C tparam to avoid multiple inheritance from same type.
template<class C>
struct constructor_precondition {
    constructor_precondition() {} // For user ctor overloads with no pre.

    // TODO: All these F must be passed by const& because they could be complex
    // functors with value captures and I don't want to copy these values
    // multiple times.
    template<typename F>
    explicit constructor_precondition(F f) {
        try { f(); }
        catch(...) {
            boost::contract::precondition_failed(
                    boost::contract::from_constructor);
        }
    }
};

} } // namespace

#endif // #include guard

