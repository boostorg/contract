
// Test all derived and base classes without exit invariants.

#define BOOST_CONTRACT_AUX_TEST_NO_A_INV
#define BOOST_CONTRACT_AUX_TEST_NO_B_INV
#define BOOST_CONTRACT_AUX_TEST_NO_C_INV
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok;
    ok.str(""); ok // Test nothing fails.
        // No invariants.
        << "c::static_inv" << std::endl
        << "b::static_inv" << std::endl
        << "a::static_inv" << std::endl

        << "c::f::pre" << std::endl
        
        << "c::f::old" << std::endl
        << "b::f::old" << std::endl
        << "a::f::old" << std::endl
        
        << "a::f::body" << std::endl
        
        << "c::static_inv" << std::endl
        << "b::static_inv" << std::endl
        << "a::static_inv" << std::endl

        << "c::f::old" << std::endl
        << "c::f::post" << std::endl
        << "b::f::old" << std::endl
        << "b::f::post" << std::endl
        << "a::f::post" << std::endl
    ;
    
    struct err {};
    boost::contract::set_exit_invariant_failure(
            [] (boost::contract::from) { throw err(); });

    a aa;
    
    a_exit_inv = true;
    b_exit_inv = true;
    c_exit_inv = true;
    a_entering_inv = b_entering_inv = c_entering_inv = true;
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));

    a_exit_inv = false;
    b_exit_inv = true;
    c_exit_inv = true;
    a_entering_inv = b_entering_inv = c_entering_inv = true;
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));
    
    a_exit_inv = true;
    b_exit_inv = false;
    c_exit_inv = true;
    a_entering_inv = b_entering_inv = c_entering_inv = true;
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));
    
    a_exit_inv = true;
    b_exit_inv = true;
    c_exit_inv = false;
    a_entering_inv = b_entering_inv = c_entering_inv = true;
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));
    
    a_exit_inv = false;
    b_exit_inv = false;
    c_exit_inv = false;
    a_entering_inv = b_entering_inv = c_entering_inv = true;
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

