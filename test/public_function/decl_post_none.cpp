
// Test derived and base classes all without postconditions.

#define BOOST_CONTRACT_AUX_TEST_NO_A_POST
#define BOOST_CONTRACT_AUX_TEST_NO_B_POST
#define BOOST_CONTRACT_AUX_TEST_NO_C_POST
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok; ok // Test nothing fails.
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        
        << "c::f::pre" << std::endl
        
        << "c::f::old" << std::endl
        << "b::f::old" << std::endl
        << "a::f::old" << std::endl
        
        << "a::f::body" << std::endl
        
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        
        // No postconditions.
        << "c::f::old" << std::endl
        << "b::f::old" << std::endl
    ;

    a aa;
    
    a_post = true;
    b_post = true;
    c_post = true;
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));

    a_post = false;
    b_post = true;
    c_post = true;
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));
    
    a_post = true;
    b_post = false;
    c_post = true;
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));
    
    a_post = true;
    b_post = true;
    c_post = false;
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));
    
    a_post = false;
    b_post = false;
    c_post = false;
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

