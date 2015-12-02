
// Test derived and base classes all without preconditions.

#define BOOST_CONTRACT_AUX_TEST_NO_A_PRE
#define BOOST_CONTRACT_AUX_TEST_NO_B_PRE
#define BOOST_CONTRACT_AUX_TEST_NO_C_PRE
#include "./decl.hpp"

#include "../aux_/oteststream.hpp"
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok; ok
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        
        // Test no preconditions.
        
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
        
        << "c::f::old" << std::endl
        << "c::f::post" << std::endl
        << "b::f::old" << std::endl
        << "b::f::post" << std::endl
        << "a::f::post" << std::endl
    ;

    a aa;

    a_pre = true;
    b_pre = false;
    c_pre = false;
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));
    
    a_pre = false;
    b_pre = true;
    c_pre = false;
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));
    
    a_pre = false;
    b_pre = false;
    c_pre = true;
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));
    
    a_pre = false;
    b_pre = false;
    c_pre = false;
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

