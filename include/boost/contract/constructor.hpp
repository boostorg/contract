
#ifndef BOOST_CONTRACT_CONSTRUCTOR_HPP_
#define BOOST_CONTRACT_CONSTRUCTOR_HPP_

#include <boost/contract/type.hpp>
#include <boost/contract/aux_/constructor.hpp>
#include <boost/make_shared.hpp>

namespace boost { namespace contract {

template<class Class>
boost::contract::type constructor(Class* const object) {
    return boost::contract::type(boost::make_shared<boost::contract::aux::
            constructor<Class> >(object));
}

// Uses Class tparam to avoid multiple inheritance from same type.
template<class Class>
struct constructor_precondition {
    constructor_precondition() {} // For overloaded constructors with no pre.

    template<typename Precondition>
    explicit constructor_precondition(Precondition const& f) { f(); }
};

} } // namespace

#endif // #include guard

