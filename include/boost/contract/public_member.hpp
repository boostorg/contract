
#ifndef BOOST_CONTRACT_PUBLIC_MEMBER_HPP_
#define BOOST_CONTRACT_PUBLIC_MEMBER_HPP_

#include <boost/contract/type.hpp>
#include <boost/contract/virtual_body.hpp>
#include <boost/contract/aux_/function.hpp>
#include <boost/contract/aux_/function_key.hpp>
#include <boost/make_shared.hpp>

// TODO: On C++11 Clang... these could static_assert enclosing func is pub?

namespace boost { namespace contract {

// Contract for public member functions with a virtual body and members of a
// class that inherits from one or more base classes (optionally, it can be used
// also if there are no base classes).
template<class Itrospection, class Class, typename Function,
        typename Argument0>
boost::contract::type public_member(Class* const object, Function const&,
        Argument0 argument0, boost::contract::virtual_body const v) {
    return boost::contract::type(
        boost::make_shared<boost::contract::aux::function<
            boost::contract::aux::public_member, Class, Itrospection, Function,
                    Argument0
        > >(v, object, argument0)
    );
}


// Contract for public member functions with a non-virtual body and members of a
// class that inherits from one or more base classes (optionally, it can be used
// also if there are no base classes).
template<class Introspection, class Class, typename Function,
        typename Argument0>
boost::contract::type public_member(Class* const object, Function const&,
        Argument0 argument0) {
    return boost::contract::type(
        boost::make_shared<boost::contract::aux::function<
            boost::contract::aux::public_member, Class, Introspection, Function,
                    Argument0
        > >(object, argument0)
    );
}

// Contract for public member functions with a virtual body and members of a
// class that does not inherits from any base class.
template<class Class>
boost::contract::type public_member(Class* const object,
        boost::contract::virtual_body v) {
    return boost::contract::type(
        boost::make_shared<boost::contract::aux::function<
            boost::contract::aux::public_member, Class
        > >(v, object)
    );
}

// Contract for public member functions with a non-virtual body and members of a
// class that does not inherits from any base class.
template<class Class>
boost::contract::type public_member(Class* const object) {
    return boost::contract::type(
        boost::make_shared<boost::contract::aux::function<
            boost::contract::aux::public_member, Class
        > >(object)
    );
}

template<class Class>
boost::contract::type public_member() {
    return boost::contract::type(
        boost::make_shared<boost::contract::aux::function<
            boost::contract::aux::public_member, Class
        > >()
    );
}

} } // namespace

#endif // #include guard

