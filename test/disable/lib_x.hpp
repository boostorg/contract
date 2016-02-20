
#ifndef BOOST_CONTRACT_TEST_LIB_X_HPP_
#define BOOST_CONTRACT_TEST_LIB_X_HPP_

// Test contracts in .cpp so never has post (because NO_POST in its Jamfile).

#include "../aux_/oteststream.hpp"
#include <boost/config.hpp>
#include <string>

#ifdef BOOST_CONTRACT_TEST_LIB_X_DYN_LINK
    #ifdef BOOST_CONTRACT_TEST_LIB_X_SOURCE
        #define BOOST_CONTRACT_TEST_LIB_X_DECLSPEC BOOST_SYMBOL_EXPORT
    #else
        #define BOOST_CONTRACT_TEST_LIB_X_DECLSPEC BOOST_SYMBOL_IMPORT
    #endif
#else
    #define BOOST_CONTRACT_TEST_LIB_X_DECLSPEC /* nothing */
#endif

BOOST_CONTRACT_TEST_AUX_OTESTSTREAM_STR_DECL(
        BOOST_CONTRACT_TEST_LIB_X_DECLSPEC, out)

void BOOST_CONTRACT_TEST_LIB_X_DECLSPEC x();

#endif

