
#ifndef BOOST_CONTRACT_DESTRUCTOR_HPP_
#define BOOST_CONTRACT_DESTRUCTOR_HPP_

/** @file */

#include <boost/contract/core/set_postcondition_only.hpp>
#include <boost/contract/aux_/operation/destructor.hpp>
/** @cond */
#include <boost/make_shared.hpp>
/** @endcond */

namespace boost { namespace contract {

template<class C>
set_postcondition_only<> destructor(C* obj) {
    return set_postcondition_only<>(boost::make_shared<
            boost::contract::aux::destructor<C> >(obj));
}

} } // namespace

#endif // #include guard

