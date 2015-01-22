
#ifndef BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_NAME_HPP_
#define BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_NAME_HPP_

#include <boost/contract/ext_/preprocessor/traits/alias/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>

/* PUBLIC */

// Expand to `(name,,,)` (wrapped within parenthesis because in general this
// name/type can contain unwrapped commas).
#define BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_AUX_NAME_INDEX, traits)

#endif // #include guard

