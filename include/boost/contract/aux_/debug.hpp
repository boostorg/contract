
#ifndef BOOST_CONTRACT_AUX_DEBUG_HPP_
#define BOOST_CONTRACT_AUX_DEBUG_HPP_

#include <boost/contract/aux_/config.hpp>

#ifdef BOOST_CONTRACT_AUX_CONFIG_NDEBUG
#   define BOOST_CONTRACT_AUX_DEBUG(cond)
#else
#   include <cassert>
#   define BOOST_CONTRACT_AUX_DEBUG(cond) (assert(cond))
#endif

#endif // #include guard

