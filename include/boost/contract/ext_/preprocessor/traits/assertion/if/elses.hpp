
#ifndef BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_HPP_
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/index/assertion.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>

/* PUBLIC */

// Expand to `pp-seq | EMPTY()`, pp-seq of assertion traits to be inspected via
// appropriate ..._ASSERTION_TRAITS_... macros.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ELEM( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_IF_ASSERTION_ELSES, traits)()

// PARSE macro #defined in "if.hpp" (because easier for reentrant repetitions).

#endif // #include guard

