
#ifndef BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_KIND_HPP_
#define BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_KIND_HPP_

#include <boost/contract/ext_/preprocessor/traits/alias/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>

/* PUBLIC */

// Expand to `namespace | using | typedef`.
#define BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_KIND(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_AUX_KIND_INDEX, traits)

#endif // #include guard

