
#ifndef BOOST_CONTRACT_AUX_DEBUG_HPP_
#define BOOST_CONTRACT_AUX_DEBUG_HPP_

#include <boost/contract/aux_/config.hpp>
#if BOOST_CONTRACT_AUX_CONFIG_DEBUG
#   include <cassert>
#   define BOOST_CONTRACT_AUX_DEBUG(cond) assert(cond)
#else
#   define BOOST_COTNRACT_AUX_DEBUG(cond)
#endif

#endif // #include guard

