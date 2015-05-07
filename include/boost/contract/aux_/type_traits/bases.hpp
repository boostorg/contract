
#ifndef BOOST_CONTRACT_AUX_TYPE_TRAITS_BASES_HPP_
#define BOOST_CONTRACT_AUX_TYPE_TRAITS_BASES_HPP_

#include <boost/contract/core/config.hpp>
#include <boost/contract/aux_/type_traits/introspection.hpp>

namespace boost { namespace contract { namespace aux { namespace type_traits {

BOOST_CONTRACT_AUX_TYPE_TRAITS_INTROSPECTION_HAS_TYPE(has_bases,
        BOOST_CONTRACT_CONFIG_BASE_TYPES)

template< class C >
struct bases_of { typedef typename C::BOOST_CONTRACT_CONFIG_BASE_TYPES type; };

} } } } // namespace

#endif // #include guard

