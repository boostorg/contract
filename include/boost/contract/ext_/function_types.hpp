
#ifndef BOOST_CONTRACT_EXT_FUNCTION_TYPES_HPP_
#define BOOST_CONTRACT_EXT_FUNCTION_TYPES_HPP_

#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace contract { namespace ext {
        namespace function_types {

namespace function_types_ {

template< unsigned int S, typename R, class C, class P >
struct member_function_pointer;

template< typename R, class C, class P >
struct member_function_pointer<0, R, C, P> {
    typedef R (C::* type) ( );
};

template< typename R, class C, class P >
struct member_function_pointer<1, R, C, P> {
    typedef R (C::* type) (
        typename boost::mpl::at_c<P, 0>::type
    );
};

template< typename R, class C, class P >
struct member_function_pointer<2, R, C, P> {
    typedef R (C::* type) (
        typename boost::mpl::at_c<P, 0>::type,
        typename boost::mpl::at_c<P, 1>::type
    );
};

} // namespace

template< typename R, typename C, class P >
struct member_function_pointer : function_types_::member_function_pointer<
        boost::mpl::size<P>::value, R, C, P> {};

} } } } // namespace

#endif // #include guard

