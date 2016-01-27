
// Test only middle base class with postconditions.

#define BOOST_CONTRACT_TEST_NO_A_POST
#define BOOST_CONTRACT_TEST_NO_B_POST
#define BOOST_CONTRACT_TEST_NO_C_POST
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok; ok // Test nothing fails.
        #if BOOST_CONTRACT_PRECONDITIONS
            << "a::ctor::pre" << std::endl
            << "b::ctor::pre" << std::endl
            << "c::ctor::pre" << std::endl
        #endif
        
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "c::static_inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "c::ctor::old" << std::endl
        #endif
        << "c::ctor::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
        #endif
            
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "b::static_inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "b::ctor::old" << std::endl
        #endif
        << "b::ctor::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
        #endif

        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "a::static_inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::ctor::old" << std::endl
        #endif
        << "a::ctor::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
    ;
    
    a_post = true;
    b_post = true;
    c_post = true;
    {
        out.str("");
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }

    a_post = false;
    b_post = true;
    c_post = true;
    {
        out.str("");
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    a_post = true;
    b_post = false;
    c_post = true;
    {
        out.str("");
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    a_post = true;
    b_post = true;
    c_post = false;
    {
        out.str("");
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    a_post = false;
    b_post = false;
    c_post = false;
    {
        out.str("");
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }
 
    return boost::report_errors();
}

