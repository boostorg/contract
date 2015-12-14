
// Test all derived and grandparent classes (ends) with exit invariants.

#define BOOST_CONTRACT_AUX_TEST_NO_A_INV
#define BOOST_CONTRACT_AUX_TEST_NO_B_INV
#define BOOST_CONTRACT_AUX_TEST_NO_C_INV
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok; ok // Test nothing fails.
        << "a::ctor::pre" << std::endl
        << "b::ctor::pre" << std::endl
        << "c::ctor::pre" << std::endl
        
        << "c::static_inv" << std::endl
        << "c::ctor::old" << std::endl
        << "c::ctor::body" << std::endl
        << "c::static_inv" << std::endl
        << "c::ctor::post" << std::endl
        
        << "b::static_inv" << std::endl
        << "b::ctor::old" << std::endl
        << "b::ctor::body" << std::endl
        << "b::static_inv" << std::endl
        << "b::ctor::post" << std::endl
        
        << "a::static_inv" << std::endl
        << "a::ctor::old" << std::endl
        << "a::ctor::body" << std::endl
        << "a::static_inv" << std::endl
        << "a::ctor::post" << std::endl
    ;
    
    a_exit_inv = true;
    b_exit_inv = true;
    c_exit_inv = true;
    out.str("");
    {
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    a_exit_inv = false;
    b_exit_inv = true;
    c_exit_inv = true;
    out.str("");
    {
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }

    a_exit_inv = true;
    b_exit_inv = false;
    c_exit_inv = true;
    out.str("");
    {
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    a_exit_inv = true;
    b_exit_inv = true;
    c_exit_inv = false;
    out.str("");
    {
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    a_exit_inv = false;
    b_exit_inv = false;
    c_exit_inv = false;
    out.str("");
    {
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }

    return boost::report_errors();
}

