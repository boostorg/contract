
// Test only derived and grandparent classes (ends) with exit invariants.

#undef BOOST_CONTRACT_AUX_TEST_NO_A_INV
#define BOOST_CONTRACT_AUX_TEST_NO_B_INV
#undef BOOST_CONTRACT_AUX_TEST_NO_C_INV
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok;
    
    a_exit_inv = true;
    b_exit_inv = true;
    c_exit_inv = true;
    out.str("");
    {
        a aa;
        ok.str(""); ok // Test nothing failed.
            << "a::ctor::pre" << std::endl
            << "b::ctor::pre" << std::endl
            << "c::ctor::pre" << std::endl
            
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
            << "b::ctor::post" << std::endl
            
            << "a::static_inv" << std::endl
            << "a::ctor::old" << std::endl
            << "a::ctor::body" << std::endl
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
            << "a::ctor::post" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    struct err {};
    boost::contract::set_exit_invariant_failure(
            [] (boost::contract::from) { throw err(); });

    a_exit_inv = false;
    b_exit_inv = true;
    c_exit_inv = true;
    out.str("");
    try {
        a aa;
        BOOST_TEST(false);
    } catch(err const&) {
        ok.str(""); ok
            << "a::ctor::pre" << std::endl
            << "b::ctor::pre" << std::endl
            << "c::ctor::pre" << std::endl
            
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
            << "b::ctor::post" << std::endl

            << "a::static_inv" << std::endl
            << "a::ctor::old" << std::endl
            << "a::ctor::body" << std::endl
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl // Test this failed.
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    a_exit_inv = true;
    b_exit_inv = false;
    c_exit_inv = true;
    out.str("");
    try {
        a aa;
        ok.str(""); ok
            << "a::ctor::pre" << std::endl
            << "b::ctor::pre" << std::endl
            << "c::ctor::pre" << std::endl
            
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
            // Test no failure here.
            << "b::ctor::post" << std::endl
            
            << "a::static_inv" << std::endl
            << "a::ctor::old" << std::endl
            << "a::ctor::body" << std::endl
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
            << "a::ctor::post" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_exit_inv = true;
    b_exit_inv = true;
    c_exit_inv = false;
    out.str("");
    try {
        a aa;
        BOOST_TEST(false);
    } catch(err const&) {
        ok.str(""); ok
            << "a::ctor::pre" << std::endl
            << "b::ctor::pre" << std::endl
            << "c::ctor::pre" << std::endl
            
            << "c::static_inv" << std::endl
            << "c::ctor::old" << std::endl
            << "c::ctor::body" << std::endl
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl // Test this failed.
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_exit_inv = false;
    b_exit_inv = false;
    c_exit_inv = false;
    out.str("");
    try {
        a aa;
        BOOST_TEST(false);
    } catch(err const&) {
        ok.str(""); ok
            << "a::ctor::pre" << std::endl
            << "b::ctor::pre" << std::endl
            << "c::ctor::pre" << std::endl
            
            << "c::static_inv" << std::endl
            << "c::ctor::old" << std::endl
            << "c::ctor::body" << std::endl
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl // Test this failed (as all did).
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    return boost::report_errors();
}

