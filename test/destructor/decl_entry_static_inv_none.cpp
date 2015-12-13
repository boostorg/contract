
// Test derived and base classes all without entry static invariants.

#define BOOST_CONTRACT_AUX_TEST_NO_A_STATIC_INV
#define BOOST_CONTRACT_AUX_TEST_NO_B_STATIC_INV
#define BOOST_CONTRACT_AUX_TEST_NO_C_STATIC_INV
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok; ok // Test nothing fails.
        << "a::inv" << std::endl
        << "a::dtor::old" << std::endl
        << "a::dtor::body" << std::endl
        << "a::dtor::post" << std::endl

        << "b::inv" << std::endl
        << "b::dtor::old" << std::endl
        << "b::dtor::body" << std::endl
        << "b::dtor::post" << std::endl
        
        << "c::inv" << std::endl
        << "c::dtor::old" << std::endl
        << "c::dtor::body" << std::endl
        << "c::dtor::post" << std::endl
    ;
    
    a_entry_static_inv = true;
    b_entry_static_inv = true;
    c_entry_static_inv = true;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =true;
    {
        a aa;
        out.str("");
    }
    BOOST_TEST(out.eq(ok.str()));
    
    a_entry_static_inv = false;
    b_entry_static_inv = true;
    c_entry_static_inv = true;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =true;
    {
        a aa;
        out.str("");
    }
    BOOST_TEST(out.eq(ok.str()));
    
    a_entry_static_inv = true;
    b_entry_static_inv = false;
    c_entry_static_inv = true;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =true;
    {
        a aa;
        out.str("");
    }
    BOOST_TEST(out.eq(ok.str()));
    
    a_entry_static_inv = true;
    b_entry_static_inv = true;
    c_entry_static_inv = false;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =true;
    {
        a aa;
        out.str("");
    }
    BOOST_TEST(out.eq(ok.str()));
    
    a_entry_static_inv = false;
    b_entry_static_inv = false;
    c_entry_static_inv = false;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =true;
    {
        a aa;
        out.str("");
    }
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

