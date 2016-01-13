
#ifndef BOOST_CONTRACT_AUX_DEBUG_HPP_
#define BOOST_CONTRACT_AUX_DEBUG_HPP_

// Usually, never #defined (so "debug" assertions always in code).
#ifdef BOOST_CONTRACT_AUX_CONFIG_NDEBUG
    #define BOOST_CONTRACT_AUX_DEBUG(cond)
#else
/** @cond */
    #include <cassert>
/** @endcond */
    #define BOOST_CONTRACT_AUX_DEBUG(cond) (assert(cond))
#endif

#endif // #include guard

