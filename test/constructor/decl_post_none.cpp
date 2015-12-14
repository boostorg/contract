
// Test only middle base class with postconditions.

#define BOOST_CONTRACT_AUX_TEST_NO_A_POST
#define BOOST_CONTRACT_AUX_TEST_NO_B_POST
#define BOOST_CONTRACT_AUX_TEST_NO_C_POST
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
        << "c::inv" << std::endl
        
        << "b::static_inv" << std::endl
        << "b::ctor::old" << std::endl
        << "b::ctor::body" << std::endl
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl

        << "a::static_inv" << std::endl
        << "a::ctor::old" << std::endl
        << "a::ctor::body" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
    ;
    
    a_post = true;
    b_post = true;
    c_post = true;
    out.str("");
    {
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }

    a_post = false;
    b_post = true;
    c_post = true;
    out.str("");
    {
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    a_post = true;
    b_post = false;
    c_post = true;
    out.str("");
    {
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    a_post = true;
    b_post = true;
    c_post = false;
    out.str("");
    {
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    a_post = false;
    b_post = false;
    c_post = false;
    out.str("");
    {
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }
 
    return boost::report_errors();
}

