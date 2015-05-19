
#ifndef BOOST_CONTRACT_DESTRUCTOR_HPP_
#define BOOST_CONTRACT_DESTRUCTOR_HPP_

/** @file */

#include <boost/contract/core/set_postcondition_only.hpp>
#include <boost/contract/core/decl.hpp>
#include <boost/contract/aux_/function/destructor.hpp>
/** @cond */
#include <boost/make_shared.hpp>
/** @endcond */

namespace boost { namespace contract {

template<class C>
set_postcondition_only destructor(C const* obj) {
    return set_postcondition_only(boost::make_shared<
            boost::contract::aux::destructor<C> >(obj));
}

template<class C>
set_postcondition_only destructor(decl const& c, C const* obj) {
    return set_postcondition_only(boost::make_shared<
            boost::contract::aux::destructor<C> >(c.call_, obj));
}

} } // namespace

#endif // #include guard

