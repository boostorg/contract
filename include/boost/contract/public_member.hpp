
#ifndef BOOST_CONTRACT_PUBLIC_MEMBER_HPP_
#define BOOST_CONTRACT_PUBLIC_MEMBER_HPP_

#include <boost/contract/type.hpp>
#include <boost/contract/virtual_body.hpp>
#include <boost/contract/aux_/function/public_static_member.hpp>
#include <boost/contract/aux_/function/public_member.hpp>
#include <boost/make_shared.hpp>

// TODO: On C++11 Clang... these could static_assert enclosing func is pub?

// TODO: Consider providing also macros like:
//  void push_back(T const& value, boost::contract::virtual_back v = 0) {
//      unsigned const old_size = v.oldof_(size());
//      BOOST_CONTRACT_PUBLIC_MEMBER(this, &vector::push_back, value, v)
//          .precondition(...)
//          .postcondition(...)
//      ;
//      ...
//  }
// These macros should take the exact same params as their related functions
// (allowing param overloading via variadic macros) so to avoid confusion for
// the user in using macros instead of function-based APIs.
// The real benefit of these macros is that with C++14 generic lambdas they
// do not require users to also call BOOST_CONTRACT_INTROSPECT(push_back)!
// Also, with C++11 constexpr and __func__ (but also __FUNCTION__), these macros
// can check the specified function name is correct (matching
// `&.*::__func__` == `&vector::push_back`).
// So these macros could be always provided, they will double check the function
// name only on C++11 constexpr + __func__, and the will not require the
// external call to BOOST_CONTRACT_INTROSPECT only on C++14 generic lambdas (so
// even if they are always provided, they become truly useful and more prowerful
// on on C++14 generic lambdas when compared to the function-base APIs).

namespace boost { namespace contract {

// Contract for public member functions with a virtual body and members of a
// class that inherits from one or more base classes (optionally, it can be used
// also if there are no base classes).
template<class Itrospection, class Class, typename Function,
        typename Argument0>
boost::contract::type public_member(Class* const object, Function const&,
        Argument0 argument0, boost::contract::virtual_body const v) {
    return boost::contract::type(boost::make_shared<boost::contract::aux::
        function::public_member<Class, Itrospection, Function, Argument0> >(
                v, object, argument0)
    );
}


// Contract for public member functions with a non-virtual body and members of a
// class that inherits from one or more base classes (optionally, it can be used
// also if there are no base classes).
template<class Introspection, class Class, typename Function,
        typename Argument0>
boost::contract::type public_member(Class* const object, Function const&,
        Argument0 argument0) {
    return boost::contract::type(boost::make_shared<boost::contract::aux::
        function::public_member<Class, Introspection, Function, Argument0> >(
                object, argument0)
    );
}

// Contract for public member functions with a virtual body and members of a
// class that does not inherits from any base class.
template<class Class>
boost::contract::type public_member(Class* const object,
        boost::contract::virtual_body const v) {
    return boost::contract::type(boost::make_shared<boost::contract::aux::
            function::public_member<Class> >(v, object));
}

// Contract for public member functions with a non-virtual body and members of a
// class that does not inherits from any base class.
template<class Class>
boost::contract::type public_member(Class* const object) {
    return boost::contract::type(boost::make_shared<boost::contract::aux::
            function::public_member<Class> >(object));
}

// Contract for public static member functions.
template<class Class>
boost::contract::type public_member() {
    return boost::contract::type(boost::make_shared<boost::contract::aux::
            function::public_static_member<Class> >());
}

} } // namespace

#endif // #include guard

