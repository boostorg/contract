
// Test derived and base classes all without entry static invariants.

#define BOOST_CONTRACT_AUX_TEST_NO_A_STATIC_INV
#define BOOST_CONTRACT_AUX_TEST_NO_B_STATIC_INV
#define BOOST_CONTRACT_AUX_TEST_NO_C_STATIC_INV
#include "./decl.hpp"

#include "../aux_/oteststream.hpp"
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok; ok
        // Test no static invariants.
        << "c::inv" << std::endl
        << "b::inv" << std::endl
        << "a::inv" << std::endl

        << "c::f::pre" << std::endl
        
        << "c::f::old" << std::endl
        << "b::f::old" << std::endl
        << "a::f::old" << std::endl
        
        << "a::f::body" << std::endl
        
        << "c::inv" << std::endl
        << "b::inv" << std::endl
        << "a::inv" << std::endl
        
        << "c::f::old" << std::endl
        << "c::f::post" << std::endl
        << "b::f::old" << std::endl
        << "b::f::post" << std::endl
        << "a::f::post" << std::endl
    ;
    
    a aa;

    a_entry_static_inv = false;
    b_entry_static_inv = true;
    c_entry_static_inv = true;
    out.str("");
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            true;
    aa.f();
    BOOST_TEST(out.eq(ok.str()));
    
    a_entry_static_inv = true;
    b_entry_static_inv = false;
    c_entry_static_inv = true;
    out.str("");
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            true;
    aa.f();
    BOOST_TEST(out.eq(ok.str()));
    
    a_entry_static_inv = true;
    b_entry_static_inv = true;
    c_entry_static_inv = false;
    out.str("");
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            true;
    aa.f();
    BOOST_TEST(out.eq(ok.str()));
    
    a_entry_static_inv = false;
    b_entry_static_inv = false;
    c_entry_static_inv = false;
    out.str("");
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            true;
    aa.f();
    BOOST_TEST(out.eq(ok.str()));
    
    return boost::report_errors();
}

