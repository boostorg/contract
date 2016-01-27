
// Test all derived and base classes without entry static invariants.

#define BOOST_CONTRACT_TEST_NO_A_STATIC_INV
#define BOOST_CONTRACT_TEST_NO_B_STATIC_INV
#define BOOST_CONTRACT_TEST_NO_C_STATIC_INV
#include "decl.hpp"

#include <boost/preprocessor/control/iif.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok; ok // Test nothing fails.
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "a::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::dtor::old" << std::endl
        #endif
        << "a::dtor::body" << std::endl
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::dtor::post" << std::endl
        #endif

        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "b::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "b::dtor::old" << std::endl
        #endif
        << "b::dtor::body" << std::endl
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "b::dtor::post" << std::endl
        #endif
            
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "c::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "c::dtor::old" << std::endl
        #endif
        << "c::dtor::body" << std::endl
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "c::dtor::post" << std::endl
        #endif
    ;
    
    a_entry_static_inv = true;
    b_entry_static_inv = true;
    c_entry_static_inv = true;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    {
        a aa;
        out.str("");
    }
    BOOST_TEST(out.eq(ok.str()));
    
    a_entry_static_inv = false;
    b_entry_static_inv = true;
    c_entry_static_inv = true;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    {
        a aa;
        out.str("");
    }
    BOOST_TEST(out.eq(ok.str()));
    
    a_entry_static_inv = true;
    b_entry_static_inv = false;
    c_entry_static_inv = true;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    {
        a aa;
        out.str("");
    }
    BOOST_TEST(out.eq(ok.str()));
    
    a_entry_static_inv = true;
    b_entry_static_inv = true;
    c_entry_static_inv = false;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    {
        a aa;
        out.str("");
    }
    BOOST_TEST(out.eq(ok.str()));
    
    a_entry_static_inv = false;
    b_entry_static_inv = false;
    c_entry_static_inv = false;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    {
        a aa;
        out.str("");
    }
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

