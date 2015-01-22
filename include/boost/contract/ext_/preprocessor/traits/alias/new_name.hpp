
#ifndef BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_NEW_NAME_HPP_
#define BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_NEW_NAME_HPP_

#include <boost/contract/ext_/preprocessor/traits/alias/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PUBLIC */

// Expand to `new-name | EMPTY()` (can be not empty only for both using
// and typedef aliases).
#define BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_NEW_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_AUX_NEW_NAME_INDEX, traits)()

#endif // #include guard

