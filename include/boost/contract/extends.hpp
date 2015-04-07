
#ifndef BOOST_CONTRACT_EXTENDS_HPP_
#define BOOST_CONTRACT_EXTENDS_HPP_

#include <boost/contract/aux_/bases.hpp>
#include <boost/mpl/vector.hpp>

#define BOOST_CONTRACT_EXTENDS_DEF2_ \
    { \
        typedef boost::mpl::vector<B0, B1> BOOST_CONTRACT_AUX_BASES; \
        \
        extends ( ) : B0(), B1() {} \
        explicit extends ( B0 const& b0 ) : B0(b0), B1() {} \
        explicit extends ( B1 const& b1 ) : B0(), B1(b1) {} \
        extends ( B0 const& b0, B1 const& b1 ) : B0(b0), B1(b1) {} \
    };

namespace boost { namespace contract {

// TODO: Impl all public, public_virtual, protected, protected_virtual, private,
// private_virtual combinations and for a max number of bases controlled via
// a config macro.

template< class B > struct public_;
template< class B > struct protected_;
template< class B > struct private_;
template< class B > struct public_virtual;
template< class B > struct protected_virtual;
template< class B > struct private_virtual;
    
template< class B0, class B1 >
struct extends :
    B0, B1
BOOST_CONTRACT_EXTENDS_DEF2_

template< class B0, class B1 >
struct extends<public_<B0>, protected_virtual<B1> > :
    public B0, protected virtual B1
BOOST_CONTRACT_EXTENDS_DEF2_

} } // namespace

#endif // #include guard

