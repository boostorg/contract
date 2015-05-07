
#ifndef BOOST_CONTRACT_PUBLIC_MEMBER_HPP_
#define BOOST_CONTRACT_PUBLIC_MEMBER_HPP_

#include <boost/contract/core/var.hpp> // Here so user can store contract.
#include <boost/contract/core/set_precondition_postcondition.hpp>
#include <boost/contract/core/virtual.hpp>
#include <boost/contract/aux_/function/public_static_member.hpp>
#include <boost/contract/aux_/function/public_member.hpp>
#include <boost/make_shared.hpp>

namespace boost { namespace contract {

// Contract for public member functions with a virtual body and members of a
// class that inherits from one or more base classes (optionally, it can be used
// also if there are no base classes).
template<class Introspection, class Class, typename Argument0>
boost::contract::set_precondition_postcondition public_member(boost::contract::
        virtual_* const v, Class* const object, Argument0& argument0) {
    return boost::contract::set_precondition_postcondition(boost::make_shared<
        boost::contract::aux::function::public_member<Class, Introspection,
                Argument0> >(v, object, argument0)
    );
}

// Contract for public member functions with a non-virtual body and members of a
// class that inherits from one or more base classes (optionally, it can be used
// also if there are no base classes).
template<class Introspection, class Class, typename Argument0>
boost::contract::set_precondition_postcondition public_member(
        Class* const object, Argument0& argument0) {
    return boost::contract::set_precondition_postcondition(boost::make_shared<
        boost::contract::aux::function::public_member<Class, Introspection,
                Argument0> >(object, argument0)
    );
}

// Contract for public member functions with a virtual body and members of a
// class that does not inherits from any base class.
template<class Class>
boost::contract::set_precondition_postcondition public_member(
        boost::contract::virtual_* const v, Class* const object) {
    return boost::contract::set_precondition_postcondition(boost::make_shared<
            boost::contract::aux::function::public_member<Class> >(v, object));
}

// Contract for public member functions with a non-virtual body and members of a
// class that does not inherits from any base class.
template<class Class>
boost::contract::set_precondition_postcondition public_member(
        Class* const object) {
    return boost::contract::set_precondition_postcondition(boost::make_shared<
            boost::contract::aux::function::public_member<Class> >(object));
}

// Contract for public static member functions.
template<class Class>
boost::contract::set_precondition_postcondition public_member() {
    return boost::contract::set_precondition_postcondition(boost::make_shared<
            boost::contract::aux::function::public_static_member<Class> >());
}

} } // namespace

#endif // #include guard

