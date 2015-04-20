
#ifndef BOOST_CONTRACT_AUX_BASES_HPP_
#define BOOST_CONTRACT_AUX_BASES_HPP_

#include <boost/contract/config.hpp>
#include <boost/contract/aux_/tti.hpp>

namespace boost { namespace contract { namespace aux {

BOOST_CONTRACT_AUX_TTI_TRAIT_HAS_TYPE(has_bases,
        BOOST_CONTRACT_CONFIG_BASE_TYPES)

template< class C >
struct bases_of { typedef typename C::BOOST_CONTRACT_CONFIG_BASE_TYPES type; };

} } } // namespace

#endif // #include guard

