
// Test only middle base class with postconditions.

#define BOOST_CONTRACT_AUX_TEST_NO_A_POST
#undef BOOST_CONTRACT_AUX_TEST_NO_B_POST
#define BOOST_CONTRACT_AUX_TEST_NO_C_POST
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>
#include <string>        

std::string ok_begin() {
    std::ostringstream ok; ok
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_PRECONDITIONS
            << "c::f::pre" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "c::f::old" << std::endl
            << "b::f::old" << std::endl
            << "a::f::old" << std::endl
        #endif 
        << "a::f::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS 
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
    ;
    return ok.str();
}

int main() {
    std::ostringstream ok;
    
    a aa;
    
    a_post = true;
    b_post = true;
    c_post = true;
    out.str("");
    aa.f();
    ok.str(""); ok // Test nothing failed.
        << ok_begin()
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "c::f::old" << std::endl
            << "b::f::old" << std::endl
            << "b::f::post" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));
    
    struct err {};
    boost::contract::set_postcondition_failure(
            [] (boost::contract::from) { throw err(); });

    a_post = false;
    b_post = true;
    c_post = true;
    out.str("");
    try {
        aa.f();
        ok.str(""); ok
            << ok_begin()
            #if BOOST_CONTRACT_POSTCONDITIONS
                << "c::f::old" << std::endl
                << "b::f::old" << std::endl
                << "b::f::post" << std::endl
                // Test no failure here.
            #endif
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_post = true;
    b_post = false;
    c_post = true;
    out.str("");
    try {
        aa.f();
        #if BOOST_CONTRACT_POSTCONDITIONS
                BOOST_TEST(false);
            } catch(err const&) {
        #endif
        ok.str(""); ok
            << ok_begin()
            #if BOOST_CONTRACT_POSTCONDITIONS
                << "c::f::old" << std::endl
                << "b::f::old" << std::endl
                << "b::f::post" << std::endl // Test this failed.
            #endif
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_post = true;
    b_post = true;
    c_post = false;
    out.str("");
    try {
        aa.f();
        ok.str(""); ok
            << ok_begin()
            #if BOOST_CONTRACT_POSTCONDITIONS
                << "c::f::old" << std::endl
                // Test no failure here.
                << "b::f::old" << std::endl
                << "b::f::post" << std::endl
            #endif
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_post = false;
    b_post = false;
    c_post = false;
    out.str("");
    try {
        aa.f();
        #if BOOST_CONTRACT_POSTCONDITIONS
                BOOST_TEST(false);
            } catch(err const&) {
        #endif
        ok.str(""); ok
            << ok_begin()
            #if BOOST_CONTRACT_POSTCONDITIONS
                << "c::f::old" << std::endl
                << "b::f::old" << std::endl
                << "b::f::post" << std::endl // Test this failed (as all did).
            #endif
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    return boost::report_errors();
}

