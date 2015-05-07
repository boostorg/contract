
#ifndef BOOST_CONTRACT_CONSTRUCTOR_HPP_
#define BOOST_CONTRACT_CONSTRUCTOR_HPP_

#include <boost/contract/core/var.hpp> // Here so user can store contract.
#include <boost/contract/core/set_postcondition_only.hpp>
#include <boost/contract/aux_/exception.hpp>
#include <boost/contract/aux_/function/constructor.hpp>
#include <boost/make_shared.hpp>

namespace boost { namespace contract {

template<class Class>
boost::contract::set_postcondition_only constructor(Class* const object) {
    return boost::contract::set_postcondition_only(boost::make_shared<
            boost::contract::aux::function::constructor<Class> >(object));
}

// Uses Class tparam to avoid multiple inheritance from same type.
template<class Class>
struct constructor_precondition {
    constructor_precondition() {} // For overloaded constructors with no pre.

    template<typename Precondition>
    explicit constructor_precondition(Precondition const& f) {
        try { f(); }
        catch(...) {
            boost::contract::aux::pre_failure_handler(
                    boost::contract::from_constructor);
        }
    }
};

} } // namespace

#endif // #include guard

