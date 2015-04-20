
#ifndef BOOST_CONTRACT_AUX_NAME_HPP_
#define BOOST_CONTRACT_AUX_NAME_HPP_

#include <boost/preprocessor/cat.hpp>

/* PUBLIC */

// IMPORTANT: Cannot use '_' infix to prevent forming reserved C++ names
// (containing "__" if user `name` starts/ends with '_' already) so using 'X'.

// NOTE: Explicitly list number of names to concatenate using ..._NAME-n
// (instead of using ..._SEQ_CAT or similar) for optimal speed and reentrancy.

#define BOOST_CONTRACT_AUX_NAME1(name1) \
    BOOST_PP_CAT(boost_contract_auxX, name1)

#endif // #include guard

