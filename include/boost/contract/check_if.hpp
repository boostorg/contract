
#ifndef BOOST_CONTRACT_CHECK_IF_HPP_
#define BOOST_CONTRACT_CHECK_IF_HPP_

#include <boost/mpl/bool.hpp>

namespace boost { namespace contract {

// TODO: Use this call_if in all places where I dispatch the actual call
// based on a static bool condition.

namespace check_if_ {
    template< typename F, typename A0, typename A1 >
    bool check_if ( boost::mpl::false_ const& b, F const f,
            A0 const& a0, A1 const& a1 ) {
        return true;
    }
    
    template< typename F, typename A0, typename A1 >
    bool check_if ( boost::mpl::true_ const& b, F const f,
            A0 const& a0, A1 const& a1 ) {
        return f(a0, a1);
    }
}

template< bool B, typename F, typename A0, typename A1 >
bool check_if_c ( F const f, A0 const& a0, A1 const& a1 ) {
    return check_if_::check_if(boost::mpl::bool_<B>(), f, a0, a1);
}

template< class B, typename F, typename A0, typename A1 >
bool check_if ( F const f, A0 const& a0, A1 const& a1 ) {
    return check_if_c<B::value>(f, a0, a1);
}

} } // namespace

#endif

