
#ifndef BOOST_CONTRACT_CONSTRUCTOR_HPP_
#define BOOST_CONTRACT_CONSTRUCTOR_HPP_

/** @file */

#include <boost/contract/core/set_old_postcondition.hpp>
#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/operation/constructor.hpp>
/** @cond */
#include <boost/make_shared.hpp>
/** @endcond */

namespace boost { namespace contract {

template<class C>
set_old_postcondition<> constructor(C* obj) {
    return set_old_postcondition<>(boost::make_shared<
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

