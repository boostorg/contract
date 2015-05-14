
#ifndef BOOST_CONTRACT_AUX_DEBUG_HPP_
#define BOOST_CONTRACT_AUX_DEBUG_HPP_

/** @cond */
#include <boost/contract/aux_/config.hpp>
/** @endcond */

#ifdef BOOST_CONTRACT_AUX_CONFIG_NDEBUG
#   define BOOST_CONTRACT_AUX_DEBUG(cond)
#else
/** @cond */
#   include <cassert>
/** @endcond */
#   define BOOST_CONTRACT_AUX_DEBUG(cond) (assert(cond))
#endif

#endif // #include guard

