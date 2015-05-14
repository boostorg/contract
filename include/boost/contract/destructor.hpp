
#ifndef BOOST_CONTRACT_DESTRUCTOR_HPP_
#define BOOST_CONTRACT_DESTRUCTOR_HPP_

/** @file */

#include <boost/contract/core/set_postcondition.hpp>
#include <boost/contract/core/call.hpp>
#include <boost/contract/aux_/function/destructor.hpp>
/** @cond */
#include <boost/make_shared.hpp>
/** @endcond */

namespace boost { namespace contract {

template<class C>
boost::contract::set_postcondition destructor(C const* obj) {
    return boost::contract::set_postcondition(boost::make_shared<
            boost::contract::aux::destructor<C> >(obj));
}

template<class C>
boost::contract::set_postcondition destructor(boost::contract::call const& c,
        C const* obj) {
    return boost::contract::set_postcondition(boost::make_shared<
            boost::contract::aux::destructor<C> >(c.call_, obj));
}

} } // namespace

#endif // #include guard

