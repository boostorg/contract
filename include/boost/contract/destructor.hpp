
#ifndef BOOST_CONTRACT_DESTRUCTOR_HPP_
#define BOOST_CONTRACT_DESTRUCTOR_HPP_

#include <boost/contract/core/var.hpp> // Here so user can store contract.
#include <boost/contract/core/set_postcondition_only.hpp>
#include <boost/contract/aux_/function/destructor.hpp>
#include <boost/make_shared.hpp>

namespace boost { namespace contract {

template<class Class>
boost::contract::set_postcondition_only destructor(Class* const object) {
    return boost::contract::set_postcondition_only(boost::make_shared<
            boost::contract::aux::function::destructor<Class> >(object));
}

} } // namespace

#endif // #include guard

