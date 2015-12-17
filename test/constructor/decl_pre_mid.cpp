
// Test only middle base classes with preconditions.

#define BOOST_CONTRACT_AUX_TEST_NO_A_PRE
#undef BOOST_CONTRACT_AUX_TEST_NO_B_PRE
#define BOOST_CONTRACT_AUX_TEST_NO_C_PRE
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok;
    
    a_pre = true;
    b_pre = true;
    c_pre = true;
    out.str("");
    {
        a aa;
        ok.str(""); ok // Test nothing failed.
            << "b::ctor::pre" << std::endl

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
        BOOST_TEST(out.eq(ok.str()));
    }

    struct err {};
    boost::contract::set_precondition_failure(
            [] (boost::contract::from) { throw err(); });

    a_pre = false;
    b_pre = true;
    c_pre = true;
    out.str("");
    {
        a aa;
        ok.str(""); ok
            << "b::ctor::pre" << std::endl // Test no failure here.

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
        BOOST_TEST(out.eq(ok.str()));
    }
    
    a_pre = true;
    b_pre = false;
    c_pre = true;
    out.str("");
    try {
        a aa;
        BOOST_TEST(false);
    } catch(err const&) {
        ok.str(""); ok
            << "b::ctor::pre" << std::endl // Test this failed.
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    
    a_pre = true;
    b_pre = true;
    c_pre = false;
    out.str("");
    {
        a aa;
        ok.str(""); ok
            << "b::ctor::pre" << std::endl // Test no failure here.

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
        BOOST_TEST(out.eq(ok.str()));
    }
    
    a_pre = false;
    b_pre = false;
    c_pre = false;
    out.str("");
    try {
        a aa;
        BOOST_TEST(false);
    } catch(err const&) {
        ok.str(""); ok
            << "b::ctor::pre" << std::endl // Test this failed (as all did).
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    return boost::report_errors();
}

