
#ifndef BOOST_CONTRACT_DESTRUCTOR_HPP_
#define BOOST_CONTRACT_DESTRUCTOR_HPP_

/** @file */

#include <boost/contract/core/set_old_postcondition.hpp>
#include <boost/contract/aux_/operation/destructor.hpp>

namespace boost { namespace contract {

template<class C>
set_old_postcondition<> destructor(C* obj) {
    // Must check ..._PRECONDITIONS here because set_... is generic.
    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        return set_old_postcondition<>(
                new boost::contract::aux::destructor<C>(obj));
    #else
        return set_old_postcondition<>();
    #endif
}

} } // namespace

#endif // #include guard

