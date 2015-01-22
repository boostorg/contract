
#ifndef BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_NAMESPACE_HPP_
#define BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_NAMESPACE_HPP_

#include <boost/contract/ext_/preprocessor/traits/alias/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PUBLIC */

// Expand to `namespace | EMPTY()` (can be not empty only for using aliases).
#define BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_NAMESPACE(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_AUX_NAMESPACE_INDEX, traits)()

#endif // #include guard

