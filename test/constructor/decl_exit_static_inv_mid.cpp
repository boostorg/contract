
// Test only middle base class with exit static invariants.

#define BOOST_CONTRACT_AUX_TEST_NO_A_STATIC_INV
#undef BOOST_CONTRACT_AUX_TEST_NO_B_STATIC_INV
#define BOOST_CONTRACT_AUX_TEST_NO_C_STATIC_INV
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok;
    
    a_exit_static_inv = true;
    b_exit_static_inv = true;
    c_exit_static_inv = true;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =true;
    out.str("");
    {
        a aa;
        ok.str(""); ok // Test nothing failed.
            << "a::ctor::pre" << std::endl
            << "b::ctor::pre" << std::endl
            << "c::ctor::pre" << std::endl
            
            << "c::ctor::old" << std::endl
            << "c::ctor::body" << std::endl
            << "c::inv" << std::endl
            << "c::ctor::post" << std::endl
            
            << "b::static_inv" << std::endl
            << "b::ctor::old" << std::endl
            << "b::ctor::body" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "b::ctor::post" << std::endl

            << "a::ctor::old" << std::endl
            << "a::ctor::body" << std::endl
            << "a::inv" << std::endl
            << "a::ctor::post" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    struct err {};
    boost::contract::set_exit_invariant_failure(
            [] (boost::contract::from) { throw err(); });

    a_exit_static_inv = false;
    b_exit_static_inv = true;
    c_exit_static_inv = true;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =true;
    out.str("");
    try {
        a aa;
        ok.str(""); ok
            << "a::ctor::pre" << std::endl
            << "b::ctor::pre" << std::endl
            << "c::ctor::pre" << std::endl
            
            << "c::ctor::old" << std::endl
            << "c::ctor::body" << std::endl
            << "c::inv" << std::endl
            << "c::ctor::post" << std::endl
            
            << "b::static_inv" << std::endl
            << "b::ctor::old" << std::endl
            << "b::ctor::body" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "b::ctor::post" << std::endl

            << "a::ctor::old" << std::endl
            << "a::ctor::body" << std::endl
            // Test no failure here.
            << "a::inv" << std::endl
            << "a::ctor::post" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_exit_static_inv = true;
    b_exit_static_inv = false;
    c_exit_static_inv = true;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =true;
    out.str("");
    try {
        a aa;
        BOOST_TEST(false);
    } catch(err const&) {
        ok.str(""); ok
            << "a::ctor::pre" << std::endl
            << "b::ctor::pre" << std::endl
            << "c::ctor::pre" << std::endl
            
            << "c::ctor::old" << std::endl
            << "c::ctor::body" << std::endl
            << "c::inv" << std::endl
            << "c::ctor::post" << std::endl
            
            << "b::static_inv" << std::endl
            << "b::ctor::old" << std::endl
            << "b::ctor::body" << std::endl
            << "b::static_inv" << std::endl // Test this failed.
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_exit_static_inv = true;
    b_exit_static_inv = true;
    c_exit_static_inv = false;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =true;
    out.str("");
    try {
        a aa;
        ok.str(""); ok
            << "a::ctor::pre" << std::endl
            << "b::ctor::pre" << std::endl
            << "c::ctor::pre" << std::endl
            
            << "c::ctor::old" << std::endl
            << "c::ctor::body" << std::endl
            // Test no failure here.
            << "c::inv" << std::endl
            << "c::ctor::post" << std::endl
            
            << "b::static_inv" << std::endl
            << "b::ctor::old" << std::endl
            << "b::ctor::body" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "b::ctor::post" << std::endl

            << "a::ctor::old" << std::endl
            << "a::ctor::body" << std::endl
            << "a::inv" << std::endl
            << "a::ctor::post" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_exit_static_inv = false;
    b_exit_static_inv = false;
    c_exit_static_inv = false;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =true;
    out.str("");
    try {
        a aa;
        BOOST_TEST(false);
    } catch(err const&) {
        ok.str(""); ok
            << "a::ctor::pre" << std::endl
            << "b::ctor::pre" << std::endl
            << "c::ctor::pre" << std::endl
            
            << "c::ctor::old" << std::endl
            << "c::ctor::body" << std::endl
            << "c::inv" << std::endl
            << "c::ctor::post" << std::endl
            
            << "b::static_inv" << std::endl
            << "b::ctor::old" << std::endl
            << "b::ctor::body" << std::endl
            << "b::static_inv" << std::endl // Test this failed.
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    return boost::report_errors();
}

