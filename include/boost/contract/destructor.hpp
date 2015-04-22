
#ifndef BOOST_CONTRACT_DESTRUCTOR_HPP_
#define BOOST_CONTRACT_DESTRUCTOR_HPP_

#include <boost/contract/aux_/function/destructor.hpp>
#include <boost/contract/aux_/set/post_only.hpp>
#include <boost/make_shared.hpp>

namespace boost { namespace contract {

template<class Class>
boost::contract::aux::set::post_only destructor(Class* const object) {
    return boost::contract::aux::set::post_only(boost::make_shared<
            boost::contract::aux::function::destructor<Class> >(object));
}

} } // namespace

#endif // #include guard

