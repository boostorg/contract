
#ifndef BOOST_CONTRACT_TEST_LIB_A_HPP_
#define BOOST_CONTRACT_TEST_LIB_A_HPP_

#include "../aux_/oteststream.hpp"
#include "../aux_/counter.hpp"
#include <boost/config.hpp>
#include <string>

// Test other contract checking disabled within contract checking [among libs].

#ifdef BOOST_CONTRACT_TEST_LIB_A_DYN_LINK
    #ifdef BOOST_CONTRACT_TEST_LIB_A_SOURCE
        #define BOOST_CONTRACT_TEST_LIB_A_DECL BOOST_SYMBOL_EXPORT
    #else
        #define BOOST_CONTRACT_TEST_LIB_A_DECL BOOST_SYMBOL_IMPORT
    #endif
#else
    #define BOOST_CONTRACT_TEST_LIB_A_DECL /* nothing */
#endif

BOOST_CONTRACT_TEST_AUX_OTESTSTREAM_STR_DECL(
        BOOST_CONTRACT_TEST_LIB_A_DECL, out)

struct BOOST_CONTRACT_TEST_LIB_A_DECL a {
    static void static_invariant();
    void invariant() const;

    struct x_tag;
    typedef boost::contract::test::aux::counter<x_tag, int> x_type;

    int f(x_type& x);

    static void disable_pre_failure();
    static void disable_post_failure();
    static void disable_entry_inv_failure();
    static void disable_exit_inv_failure();
    static void disable_inv_failure();
    static void disable_failure();
};

#endif // #include guard

