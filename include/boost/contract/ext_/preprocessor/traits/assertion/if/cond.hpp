
#ifndef BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_HPP_
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND_HPP_

#include <boost/contract/ext_/preprocessor/traits/capture.hpp>

/* PUBLIC */

// Expand to const-assertion-traits or bool-assertion-traits (depending on
// ASSERTION_TRAITS_KIND) to be inspected using CONST_ASSERTION_TRAITS and
// BOOL_ASSERTION_TRAITS respectively.
// For static-if, always expand to bool-assertion-traits.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_AUX_COND_INDEX, traits)

// PARSE macro #defined in "if.hpp" (because easier for reentrant repetitions).

#endif // #include gaurd

