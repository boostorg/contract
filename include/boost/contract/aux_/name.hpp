
#ifndef BOOST_CONTRACT_AUX_NAME_HPP_
#define BOOST_CONTRACT_AUX_NAME_HPP_

#include <boost/preprocessor/cat.hpp>

/* PUBLIC */

// NOTE: Explicitly list number of names to concatenate using ..._NAME-n
// (instead of using ..._SEQ_CAT or similar) for optimal speed and reentrancy.

#define BOOST_CONTRACT_AUX_NAME1(name1) \
        BOOST_PP_CAT(BOOST_CONTRACT_AUX_NAME_PREFIX_, name1)
       
/* PRIVATE */

#define BOOST_CONTRACT_AUX_NAME_PREFIX_ boost_contract_auxX

#endif // #include guard

