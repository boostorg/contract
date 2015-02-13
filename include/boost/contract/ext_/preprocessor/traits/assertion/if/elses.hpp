
#ifndef BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_HPP_
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES_HPP_

/* PUBLIC */

// Expand to `pp-seq | EMPTY()`, pp-seq of assertion traits to be inspected via
// appropriate ..._ASSERTION_TRAITS_... macros.
#define BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_AUX_ELSES_INDEX, traits)()

// PARSE macro #defined in "if.hpp" (because easier for reentrant repetitions).

#endif // #include guard

