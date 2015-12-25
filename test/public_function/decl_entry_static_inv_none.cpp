
// Test all derived and base classes without entry static invariants.

#define BOOST_CONTRACT_AUX_TEST_NO_A_STATIC_INV
#define BOOST_CONTRACT_AUX_TEST_NO_B_STATIC_INV
#define BOOST_CONTRACT_AUX_TEST_NO_C_STATIC_INV
#include "decl.hpp"

#include <boost/preprocessor/control/iif.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok; ok // Test nothing fails.
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "c::inv" << std::endl
            << "b::inv" << std::endl
            << "a::inv" << std::endl
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
            << "c::inv" << std::endl
            << "b::inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "c::f::old" << std::endl
            << "c::f::post" << std::endl
            << "b::f::old" << std::endl
            << "b::f::post" << std::endl
            << "a::f::post" << std::endl
        #endif
    ;
    
    a aa;
    
    a_entry_static_inv = true;
    b_entry_static_inv = true;
    c_entry_static_inv = true;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));

    a_entry_static_inv = false;
    b_entry_static_inv = true;
    c_entry_static_inv = true;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));
    
    a_entry_static_inv = true;
    b_entry_static_inv = false;
    c_entry_static_inv = true;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));
    
    a_entry_static_inv = true;
    b_entry_static_inv = true;
    c_entry_static_inv = false;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));
    
    a_entry_static_inv = false;
    b_entry_static_inv = false;
    c_entry_static_inv = false;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));
    
    return boost::report_errors();
}

