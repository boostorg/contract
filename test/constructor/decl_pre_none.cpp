
// Test all derived and base classes without preconditions.

#define BOOST_CONTRACT_AUX_TEST_NO_A_PRE
#define BOOST_CONTRACT_AUX_TEST_NO_B_PRE
#define BOOST_CONTRACT_AUX_TEST_NO_C_PRE
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok; ok
        // Test no preconditions here.

        << "c::static_inv" << std::endl
        << "c::ctor::old" << std::endl
        << "c::ctor::body" << std::endl
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "c::ctor::post" << std::endl
        
        << "b::static_inv" << std::endl
        << "b::ctor::old" << std::endl
        << "b::ctor::body" << std::endl
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "b::ctor::post" << std::endl

        << "a::static_inv" << std::endl
        << "a::ctor::old" << std::endl
        << "a::ctor::body" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        << "a::ctor::post" << std::endl
    ;
    
    a_pre = true;
    b_pre = true;
    c_pre = true;
    out.str("");
    {
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }

    a_pre = false;
    b_pre = true;
    c_pre = true;
    out.str("");
    {
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    a_pre = true;
    b_pre = false;
    c_pre = true;
    out.str("");
    {
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    a_pre = true;
    b_pre = true;
    c_pre = false;
    out.str("");
    {
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    a_pre = false;
    b_pre = false;
    c_pre = false;
    out.str("");
    {
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }

    return boost::report_errors();
}

