
#ifndef BOOST_CONTRACT_AUX_NAME_HPP_
#define BOOST_CONTRACT_AUX_NAME_HPP_

#include <boost/contract/aux_/config.hpp>
#include <boost/preprocessor/cat.hpp>

/* PUBLIC */

// NOTE: Explicitly list number of names to concatenate using ..._NAME-n
// (instead of using ..._SEQ_CAT or similar) for optimal speed and reentrancy.

#define BOOST_CONTRACT_AUX_NAME1(name1) \
        BOOST_PP_CAT(BOOST_CONTRACT_AUX_CONFIG_NAME_PREFIX, name1)

#endif // #include guard

