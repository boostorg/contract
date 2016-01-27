
// Test only middle base class with exit static invariants.

#define BOOST_CONTRACT_TEST_NO_A_STATIC_INV
#undef BOOST_CONTRACT_TEST_NO_B_STATIC_INV
#define BOOST_CONTRACT_TEST_NO_C_STATIC_INV
#include "decl.hpp"

#include <boost/preprocessor/control/iif.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>
#include <string>
        
std::string ok_a() {
    std::ostringstream ok; ok
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "a::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::dtor::old" << std::endl
        #endif
        << "a::dtor::body" << std::endl
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::dtor::post"  << std::endl
        #endif
    ;
    return ok.str();
}

std::string ok_b(bool failed = false) {
    std::ostringstream ok; ok
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "b::dtor::old" << std::endl
        #endif
        << "b::dtor::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "b::static_inv" << std::endl // This can fail.
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << (!failed ? "b::dtor::post\n" : "")
        #endif
    ;
    return ok.str();
}

std::string ok_c(bool threw = false) {
    std::ostringstream ok; ok
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "c::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "c::dtor::old" << std::endl
        #endif
        << "c::dtor::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << (threw ? "c::inv\n" : "")
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << (!threw ? "c::dtor::post\n" : "")
        #endif
    ;
    return ok.str();
}

int main() {
    std::ostringstream ok;
    
    a_exit_static_inv = true;
    b_exit_static_inv = true;
    c_exit_static_inv = true;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    {
        a aa;
        out.str("");
    }
    ok.str(""); ok // Test nothing failed.
        << ok_a()
        << ok_b()
        << ok_c()
    ;
    BOOST_TEST(out.eq(ok.str()));
    
    struct err {};
    boost::contract::set_exit_invariant_failure([&ok] (boost::contract::from) {
        BOOST_TEST(out.eq(ok.str())); // Must check before dtor throws.
        throw err(); // For testing only (as dtors should not throw otherwise).
    });

    a_exit_static_inv = false;
    b_exit_static_inv = true;
    c_exit_static_inv = true;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    try {
        {
            a aa;
            ok.str("");
            out.str("");
        }
        ok.str(""); ok
            << ok_a() // Test no exit a::static_inv so no failure here.
            << ok_b()
            << ok_c()
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_exit_static_inv = true;
    b_exit_static_inv = false;
    c_exit_static_inv = true;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    try {
        {
            a aa;
            ok.str(""); ok
                << ok_a()
                // Test exit b::static_inv failed...
                << ok_b(BOOST_CONTRACT_EXIT_INVARIANTS)
            ;
            out.str("");
        }
        #if BOOST_CONTRACT_EXIT_INVARIANTS
                BOOST_TEST(false);
            } catch(err const&) {
        #endif
        ok // ...then exec other dtors and check inv on throw (as dtor threw).
            << ok_c(BOOST_CONTRACT_EXIT_INVARIANTS)
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_exit_static_inv = true;
    b_exit_static_inv = true;
    c_exit_static_inv = false;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    try {
        {
            a aa;
            ok.str("");
            out.str("");
        }
        ok.str(""); ok
            << ok_a()
            << ok_b()
            // Test no exit c::static_inv so no failure here.
            << ok_c()
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    boost::contract::set_exit_invariant_failure([] (boost::contract::from) {
        // Testing multiple failures so dtors must not throw multiple except,
        // just ignore failure and continue test program (for testing only).
    });
    
    a_exit_static_inv = false;
    b_exit_static_inv = false;
    c_exit_static_inv = false;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    {
        a aa;
        out.str("");
    }
    ok.str(""); ok
        // Test no exit a::static_inv so no faliure here.
        << ok_a()
        // Test exit b::static_inv failed (as all did).
        << ok_b(BOOST_CONTRACT_EXIT_INVARIANTS)
        // Test no exit c::static_inv so no failure here.
        << ok_c()
    ;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

