
#ifndef BOOST_CONTRACT_CONSTRUCTOR_HPP_
#define BOOST_CONTRACT_CONSTRUCTOR_HPP_

/** @file */

#include <boost/contract/core/set_postcondition_only.hpp>
#include <boost/contract/core/decl.hpp>
#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/function/constructor.hpp>
/** @cond */
#include <boost/make_shared.hpp>
/** @endcond */

namespace boost { namespace contract {

template<class C>
set_postcondition_only constructor(decl const& c, C const* obj) {
    return set_postcondition_only(boost::make_shared<
            boost::contract::aux::constructor<C> >(c.call_, obj));
}

template<class C>
set_postcondition_only constructor(C const* obj) {
    return set_postcondition_only(boost::make_shared<
            boost::contract::aux::constructor<C> >(obj));
}

// Uses C tparam to avoid multiple inheritance from same type.
template<class C>
struct constructor_precondition {
    constructor_precondition() {} // For user ctor overloads with no pre.

    template<typename F>
    explicit constructor_precondition(F const& f) {
        try { f(); }
        catch(...) { precondition_failed(from_constructor); }
    }
};

} } // namespace

#endif // #include guard

