
#ifndef BOOST_CONTRACT_BIND_HPP_
#define BOOST_CONTRACT_BIND_HPP_

#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/aux_/function/bind.hpp>
#include <boost/make_shared.hpp>

namespace boost { namespace contract {

// A0 is object ptr if F is member func ptr, 1st func arg otherwise.

template<typename F, typename A0, typename A1>
boost::contract::set_nothing bind(F f, A0 const& a0, A1 const& a1) {
    return boost::contract::set_nothing(boost::make_shared<boost::contract::
            aux::bind<F, A0, A1> >(f, a0, a1));
}

} } // namespace

#endif // #include guard

