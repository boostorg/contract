
// Test derived and base classes all without postconditions.

#define BOOST_CONTRACT_AUX_TEST_NO_A_POST
#define BOOST_CONTRACT_AUX_TEST_NO_B_POST
#define BOOST_CONTRACT_AUX_TEST_NO_C_POST
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok; ok // Test nothing fails.
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        << "a::dtor::old" << std::endl
        << "a::dtor::body" << std::endl
        << "a::static_inv" << std::endl

        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "b::dtor::old" << std::endl
        << "b::dtor::body" << std::endl
        << "b::static_inv" << std::endl
        
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "c::dtor::old" << std::endl
        << "c::dtor::body" << std::endl
        << "c::static_inv" << std::endl
    ;
    
    a_post = true;
    b_post = true;
    c_post = true;
    {
        a aa;
        out.str("");
    }
    BOOST_TEST(out.eq(ok.str()));
    
    a_post = false;
    b_post = true;
    c_post = true;
    {
        a aa;
        out.str("");
    }
    BOOST_TEST(out.eq(ok.str()));
    
    a_post = true;
    b_post = false;
    c_post = true;
    {
        a aa;
        out.str("");
    }
    BOOST_TEST(out.eq(ok.str()));
    
    a_post = true;
    b_post = true;
    c_post = false;
    {
        a aa;
        out.str("");
    }
    BOOST_TEST(out.eq(ok.str()));
    
    a_post = false;
    b_post = false;
    c_post = false;
    {
        a aa;
        out.str("");
    }
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

