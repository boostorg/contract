
#ifndef BOOST_CONTRACT_MEMBER_HPP_
#define BOOST_CONTRACT_MEMBER_HPP_

#include <boost/contract/type.hpp>
#include <boost/contract/virtual_body.hpp>
#include <boost/contract/aux_/function.hpp>
#include <boost/make_shared.hpp>

namespace boost { namespace contract {

// Use this if enclosing class has bases and body is not virtual.
template<
    class FuncTraits,
    class Class,
    typename FuncPtr,
    typename Arg0
>
type member (
    Class* const obj,
    FuncPtr const func,
    Arg0 arg0
) {
    // TODO: static_assert(Arg-last != boost::contract::virtual_body)
    return type(boost::make_shared<boost::contract::aux::function<
        FuncTraits,
        FuncPtr,
        Class,
        Arg0
    > >(obj, arg0));
}

// Use this if enclosing class has no bases and body is virtual.
template< class Class >
type member ( Class* const obj, boost::contract::virtual_body const v ) {
    return type(boost::make_shared<boost::contract::aux::function<
        boost::contract::aux::none,
        boost::contract::aux::none,
        Class,
        boost::contract::aux::none
    > >(obj, v));
}

} } // namespace

#endif // #include guard

