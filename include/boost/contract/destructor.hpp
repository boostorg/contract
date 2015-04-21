
#ifndef BOOST_CONTRACT_DESTRUCTOR_HPP_
#define BOOST_CONTRACT_DESTRUCTOR_HPP_

#include <boost/contract/type.hpp>
#include <boost/contract/aux_/destructor.hpp>
#include <boost/make_shared.hpp>

namespace boost { namespace contract {

template<class Class>
boost::contract::type destructor(Class* const object) {
    return boost::contract::type(boost::make_shared<boost::contract::aux::
            destructor<Class> >(object));
}

} } // namespace

#endif // #include guard

