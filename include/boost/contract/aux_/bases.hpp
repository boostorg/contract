
#ifndef BOOST_CONTRACT_AUX_BASES_HPP_
#define BOOST_CONTRACT_AUX_BASES_HPP_

#include <boost/contract/aux_/name.hpp>
#include <boost/contract/ext_/sfinae.hpp>

#define BOOST_CONTRACT_AUX_BASES BOOST_CONTRACT_AUX_NAME1(bases)

namespace boost { namespace contract { namespace aux {

namespace bases_ {
    struct has {
        template< class C >
        static boost::contract::ext::sfinae::yes& apply (
                typename C::BOOST_CONTRACT_AUX_BASES* );
    };
}

template< class C >
struct has_bases : boost::contract::ext::sfinae::check<C, bases_::has> {};

template< class C >
struct bases_of { typedef typename C::BOOST_CONTRACT_AUX_BASES type; };

} } } // namespace

#endif // #include guard

