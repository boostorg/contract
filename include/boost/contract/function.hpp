
#ifndef BOOST_CONTRACT_FUNCTION_HPP_
#define BOOST_CONTRACT_FUNCTION_HPP_

#include <boost/contract/type.hpp>
#include <boost/contract/virtual_body.hpp>
#include <boost/contract/aux_/function.hpp>
#include <boost/make_shared.hpp>

namespace boost { namespace contract {

// Use this when enclosing class has bases and body is not virtual.
template<
    class Intro,
    class Class,
    typename FuncPtr,
    typename Arg0
>
type function (
    Class* const obj,
    FuncPtr const func,
    Arg0 arg0
) {
    return type(boost::make_shared<boost::contract::aux::function<
        Intro,
        Class,
        FuncPtr,
        Arg0
    > >(obj, arg0));
}

// Use this when enclosing class has bases and body is not virtual.
template<
    class Intro,
    class Class,
    typename FuncPtr,
    typename Arg0
>
type function (
    Class* const obj,
    FuncPtr const func,
    Arg0 arg0,
    boost::contract::virtual_body const v
) {
    return type(boost::make_shared<boost::contract::aux::function<
        Intro,
        Class,
        FuncPtr,
        Arg0
    > >(obj, arg0, v));
}

// Use this when enclosing class has no bases and body is virtual.
template< class Class >
type function ( Class* const obj, boost::contract::virtual_body const v ) {
    return type(boost::make_shared<boost::contract::aux::function<
        boost::contract::aux::none,
        Class,
        boost::contract::aux::none,
        boost::contract::aux::none
    > >(obj, v));
}

} } // namespace

#endif // #include guard

