
#ifndef BOOST_CONTRACT_TEST_LIB_B_HPP_
#define BOOST_CONTRACT_TEST_LIB_B_HPP_

// Test other contract checking disabled within contract checking [among libs].

#include <boost/config.hpp>

#ifdef BOOST_CONTRACT_TEST_LIB_B_DYN_LINK
    #ifdef BOOST_CONTRACT_TEST_LIB_B_SOURCE
        #define BOOST_CONTRACT_TEST_LIB_B_DECL BOOST_SYMBOL_EXPORT
    #else
        #define BOOST_CONTRACT_TEST_LIB_B_DECL BOOST_SYMBOL_IMPORT
    #endif
#else
    #define BOOST_CONTRACT_TEST_LIB_B_DECL /* nothing */
#endif

bool BOOST_CONTRACT_TEST_LIB_B_DECL call_f();

struct BOOST_CONTRACT_TEST_LIB_B_DECL b {
    static void static_invariant();
    void invariant() const;

    void g();

    static bool test_disable_pre_failure();
    static bool test_disable_post_failure();
    static bool test_disable_entry_inv_failure();
    static bool test_disable_exit_inv_failure();
    static bool test_disable_inv_failure();
    static bool test_disable_failure();
    
};

#endif // #include guard


