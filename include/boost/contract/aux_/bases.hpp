
#ifndef BOOST_CONTRACT_AUX_BASES_HPP_
#define BOOST_CONTRACT_AUX_BASES_HPP_

#include <boost/contract/config.hpp>
#include <boost/contract/aux_/name.hpp>
#include <boost/contract/ext_/sfinae.hpp>

namespace boost { namespace contract { namespace aux {

namespace bases_ {
    struct has {
        template< class C >
        static boost::contract::ext::sfinae::yes& apply (
                typename C::BOOST_CONTRACT_CONFIG_BASE_TYPES* );
    };
}

template< class C >
struct has_bases : boost::contract::ext::sfinae::check<C, bases_::has> {};

template< class C >
struct bases_of { typedef typename C::BOOST_CONTRACT_CONFIG_BASE_TYPES type; };

} } } // namespace

#endif // #include guard

