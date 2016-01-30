
// Test other contract checking disabled within contract checking [among libs].

#include "lib_a.hpp"
#include "lib_b.hpp"
#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <iostream>
#include <sstream>
#include <string>

std::string ok_f() {
    std::ostringstream ok; ok
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_PRECONDITIONS
            << "a::f::pre" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::f::old" << std::endl
        #endif
        << "a::f::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::f::post" << std::endl
        #endif
    ;
    return ok.str();
}

int main() {
    std::ostringstream ok;
    b bb;

    out("");
    bb.g();
    ok.str(""); ok
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_PRECONDITIONS
            << "b::g::pre" << std::endl
            #ifdef BOOST_CONTRACT_HEADER_ONLY
                // Test preconditions have disabled no contract (incorrect, but
                // only possible behaviour if shared linking not used ad doc).
                << ok_f()
            #elif defined(BOOST_CONTRACT_CONFIG_PRECONDITIONS_DISABLE_NOTHING)
                // Test preconditions have disabled no contract.
                << ok_f()
            #else
                // Test call while checking executes body (but no contracts).
                << "a::f::body" << std::endl
            #endif
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "b::g::old" << std::endl
        #endif
        << "b::g::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS    
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
        #endif 
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "b::g::post" << std::endl
            #ifdef BOOST_CONTRACT_HEADER_ONLY
                // Test preconditions have disabled no contract (incorrect, but
                // only possible behaviour if shared linking not used ad doc).
                << ok_f()
            #else
                // Test call while checking executes body (but no contracts).
                << "a::f::body" << std::endl
            #endif
        #endif
    ;
    BOOST_TEST(out_eq(ok.str()));

    // Test old values not copied for disabled contracts.
    unsigned const cnt =
        #if defined(BOOST_CONTRACT_CONFIG_PRECONDITIONS_DISABLE_NOTHING) && \
                BOOST_CONTRACT_PRECONDITIONS && BOOST_CONTRACT_POSTCONDITIONS
            1
        #else
            0
        #endif
    ;
    BOOST_TEST_EQ(a::x_type::copies(), cnt);
    BOOST_TEST_EQ(a::x_type::evals(), cnt);
    BOOST_TEST_EQ(a::x_type::ctors(), a::x_type::dtors());

    // Double check a call to f outside another contract checks f's contracts.
    out("");
    call_f();
    BOOST_TEST(out_eq(ok_f()));

    // Test setting failure handlers (from this program using a lib).

    a::disable_pre_failure();
    out("");
    boost::contract::precondition_failure(boost::contract::from());
    BOOST_TEST(out_eq("a::pre_failure"));
    
    a::disable_post_failure();
    out("");
    boost::contract::postcondition_failure(boost::contract::from());
    BOOST_TEST(out_eq("a::post_failure"));
    
    a::disable_entry_inv_failure();
    out("");
    boost::contract::entry_invariant_failure(boost::contract::from());
    BOOST_TEST(out_eq("a::entry_inv_failure"));
    
    a::disable_exit_inv_failure();
    out("");
    boost::contract::exit_invariant_failure(boost::contract::from());
    BOOST_TEST(out_eq("a::exit_inv_failure"));
    
    a::disable_inv_failure();
    out("");
    boost::contract::entry_invariant_failure(boost::contract::from());
    BOOST_TEST(out_eq("a::inv_failure"));
    out("");
    boost::contract::exit_invariant_failure(boost::contract::from());
    BOOST_TEST(out_eq("a::inv_failure"));
    
    a::disable_failure();
    out("");
    boost::contract::precondition_failure(boost::contract::from());
    BOOST_TEST(out_eq("a::failure"));
    out("");
    boost::contract::postcondition_failure(boost::contract::from());
    BOOST_TEST(out_eq("a::failure"));
    out("");
    boost::contract::entry_invariant_failure(boost::contract::from());
    BOOST_TEST(out_eq("a::failure"));
    out("");
    boost::contract::exit_invariant_failure(boost::contract::from());
    BOOST_TEST(out_eq("a::failure"));


    // Test setting failure handlers (from a lib using another lib).

    BOOST_TEST(b::test_disable_pre_failure());
    BOOST_TEST(b::test_disable_post_failure());
    BOOST_TEST(b::test_disable_entry_inv_failure());
    BOOST_TEST(b::test_disable_exit_inv_failure());
    BOOST_TEST(b::test_disable_inv_failure());
    BOOST_TEST(b::test_disable_failure());
    
    return boost::report_errors();
}

