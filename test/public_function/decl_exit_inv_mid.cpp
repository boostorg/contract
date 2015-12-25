
// Test only middle base class with exit invariants.

#define BOOST_CONTRACT_AUX_TEST_NO_A_INV
#undef BOOST_CONTRACT_AUX_TEST_NO_B_INV
#define BOOST_CONTRACT_AUX_TEST_NO_C_INV
#include "decl.hpp"

#include <boost/preprocessor/control/iif.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok;
    
    a aa;
    
    a_exit_inv = true;
    b_exit_inv = true;
    c_exit_inv = true;
    a_entering_inv = b_entering_inv = c_entering_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    out.str("");
    aa.f();
    ok.str(""); ok // Test nothing failed.
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "c::static_inv" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl
        #endif
        #if BOOST_CONTRACT_PRECONDITIONS
            << "c::f::pre" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "c::f::old" << std::endl
            << "b::f::old" << std::endl
            << "a::f::old" << std::endl
        #endif
        << "a::f::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "c::static_inv" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "c::f::old" << std::endl
            << "c::f::post" << std::endl
            << "b::f::old" << std::endl
            << "b::f::post" << std::endl
            << "a::f::post" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));
    
    struct err {};
    boost::contract::set_exit_invariant_failure(
            [] (boost::contract::from) { throw err(); });

    a_exit_inv = false;
    b_exit_inv = true;
    c_exit_inv = true;
    a_entering_inv = b_entering_inv = c_entering_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    out.str("");
    try {
        aa.f();
        ok.str(""); ok
            #if BOOST_CONTRACT_ENTRY_INVARIANTS
                << "c::static_inv" << std::endl
                << "b::static_inv" << std::endl
                << "b::inv" << std::endl
                << "a::static_inv" << std::endl
            #endif
            #if BOOST_CONTRACT_PRECONDITIONS
                << "c::f::pre" << std::endl
            #endif
            #if BOOST_CONTRACT_POSTCONDITIONS
                << "c::f::old" << std::endl
                << "b::f::old" << std::endl
                << "a::f::old" << std::endl
            #endif
            << "a::f::body" << std::endl
            #if BOOST_CONTRACT_EXIT_INVARIANTS
                << "c::static_inv" << std::endl
                << "b::static_inv" << std::endl
                << "b::inv" << std::endl
                << "a::static_inv" << std::endl
                // Test no failure here.
            #endif
            #if BOOST_CONTRACT_POSTCONDITIONS
                << "c::f::old" << std::endl
                << "c::f::post" << std::endl
                << "b::f::old" << std::endl
                << "b::f::post" << std::endl
                << "a::f::post" << std::endl
            #endif
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_exit_inv = true;
    b_exit_inv = false;
    c_exit_inv = true;
    a_entering_inv = b_entering_inv = c_entering_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    out.str("");
    try {
        aa.f();
        #if BOOST_CONTRACT_EXIT_INVARIANTS
                BOOST_TEST(false);
            } catch(err const&) {
        #endif
        ok.str(""); ok
            #if BOOST_CONTRACT_ENTRY_INVARIANTS
                << "c::static_inv" << std::endl
                << "b::static_inv" << std::endl
                << "b::inv" << std::endl
                << "a::static_inv" << std::endl
            #endif
            #if BOOST_CONTRACT_PRECONDITIONS
                << "c::f::pre" << std::endl
            #endif
            #if BOOST_CONTRACT_POSTCONDITIONS
                << "c::f::old" << std::endl
                << "b::f::old" << std::endl
                << "a::f::old" << std::endl
            #endif
            << "a::f::body" << std::endl
            #if BOOST_CONTRACT_EXIT_INVARIANTS
                << "c::static_inv" << std::endl
                << "b::static_inv" << std::endl
                << "b::inv" << std::endl // Test this failed.
            #elif BOOST_CONTRACT_POSTCONDITIONS
                << "c::f::old" << std::endl
                << "c::f::post" << std::endl
                << "b::f::old" << std::endl
                << "b::f::post" << std::endl
                << "a::f::post" << std::endl
            #endif
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_exit_inv = true;
    b_exit_inv = true;
    c_exit_inv = false;
    a_entering_inv = b_entering_inv = c_entering_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    out.str("");
    try {
        aa.f();
        ok.str(""); ok
            #if BOOST_CONTRACT_ENTRY_INVARIANTS
                << "c::static_inv" << std::endl
                << "b::static_inv" << std::endl
                << "b::inv" << std::endl
                << "a::static_inv" << std::endl
            #endif
            #if BOOST_CONTRACT_PRECONDITIONS
                << "c::f::pre" << std::endl
            #endif
            #if BOOST_CONTRACT_POSTCONDITIONS
                << "c::f::old" << std::endl
                << "b::f::old" << std::endl
                << "a::f::old" << std::endl
            #endif
            << "a::f::body" << std::endl
            #if BOOST_CONTRACT_EXIT_INVARIANTS
                << "c::static_inv" << std::endl
                << "b::static_inv" << std::endl
                << "b::inv" << std::endl
                << "a::static_inv" << std::endl
            #endif
            #if BOOST_CONTRACT_POSTCONDITIONS
                << "c::f::old" << std::endl
                << "c::f::post" << std::endl
                << "b::f::old" << std::endl
                << "b::f::post" << std::endl
                << "a::f::post" << std::endl
            #endif
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_exit_inv = false;
    b_exit_inv = false;
    c_exit_inv = false;
    a_entering_inv = b_entering_inv = c_entering_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    out.str("");
    try {
        aa.f();
        #if BOOST_CONTRACT_EXIT_INVARIANTS
                BOOST_TEST(false);
            } catch(err const&) {
        #endif
        ok.str(""); ok
            #if BOOST_CONTRACT_ENTRY_INVARIANTS
                << "c::static_inv" << std::endl
                << "b::static_inv" << std::endl
                << "b::inv" << std::endl
                << "a::static_inv" << std::endl
            #endif
            #if BOOST_CONTRACT_PRECONDITIONS
                << "c::f::pre" << std::endl
            #endif
            #if BOOST_CONTRACT_POSTCONDITIONS
                << "c::f::old" << std::endl
                << "b::f::old" << std::endl
                << "a::f::old" << std::endl
            #endif
            << "a::f::body" << std::endl
            #if BOOST_CONTRACT_EXIT_INVARIANTS
                << "c::static_inv" << std::endl
                << "b::static_inv" << std::endl
                << "b::inv" << std::endl // Test this failed (as all did).
            #elif BOOST_CONTRACT_POSTCONDITIONS
                << "c::f::old" << std::endl
                << "c::f::post" << std::endl
                << "b::f::old" << std::endl
                << "b::f::post" << std::endl
                << "a::f::post" << std::endl
            #endif
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    return boost::report_errors();
}

