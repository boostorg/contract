
#ifndef BOOST_CONTRACT_AUX_BASE_TYPES_HPP_
#define BOOST_CONTRACT_AUX_BASE_TYPES_HPP_

#include <boost/contract/core/config.hpp>
#include <boost/contract/aux_/type_traits/introspection.hpp>

namespace boost { namespace contract { namespace aux {

BOOST_CONTRACT_AUX_INTROSPECTION_HAS_TYPE(has_base_types,
        BOOST_CONTRACT_CONFIG_BASE_TYPES)

template<class C>
struct base_types_of {
    typedef typename C::BOOST_CONTRACT_CONFIG_BASE_TYPES type;
};

} } } // namespace

#endif // #include guard

