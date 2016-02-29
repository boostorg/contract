
// Test all derived and grandparent classes (ends) with exit invariants.

#define BOOST_CONTRACT_TEST_NO_A_INV
#define BOOST_CONTRACT_TEST_NO_B_INV
#define BOOST_CONTRACT_TEST_NO_C_INV
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok; ok // Test nothing fails.
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            << "a::ctor::pre" << std::endl
            << "b::ctor::pre" << std::endl
            << "c::ctor::pre" << std::endl
        #endif
        
        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            << "c::static_inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "c::ctor::old" << std::endl
        #endif
        << "c::ctor::body" << std::endl
        #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
            << "c::static_inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "c::ctor::post" << std::endl
        #endif
        
        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            << "b::static_inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "b::ctor::old" << std::endl
        #endif
        << "b::ctor::body" << std::endl
        #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
            << "b::static_inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "b::ctor::post" << std::endl
        #endif
        
        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            << "a::static_inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "a::ctor::old" << std::endl
        #endif
        << "a::ctor::body" << std::endl
        #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
            << "a::static_inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "a::ctor::post" << std::endl
        #endif
    ;
    
    a_exit_inv = true;
    b_exit_inv = true;
    c_exit_inv = true;
    {
        out.str("");
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    a_exit_inv = false;
    b_exit_inv = true;
    c_exit_inv = true;
    {
        out.str("");
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }

    a_exit_inv = true;
    b_exit_inv = false;
    c_exit_inv = true;
    {
        out.str("");
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    a_exit_inv = true;
    b_exit_inv = true;
    c_exit_inv = false;
    {
        out.str("");
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    a_exit_inv = false;
    b_exit_inv = false;
    c_exit_inv = false;
    {
        out.str("");
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }

    return boost::report_errors();
}

