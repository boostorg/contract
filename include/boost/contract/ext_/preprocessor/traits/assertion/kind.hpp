
#ifndef BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_KIND_HPP_
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_KIND_HPP_

#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
    
/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_KIND_SET(kind, decl_traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST(decl_traits) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
                BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND(decl_traits), kind) \
    )

// Index 0 used and reserved for kind, other traits must use index 1, 2, etc.

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_KIND(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM(0, traits)

#endif // #include guard

