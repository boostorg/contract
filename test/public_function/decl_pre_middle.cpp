
// Test only middle base class has preconditions.

#define BOOST_CONTRACT_AUX_TEST_NO_A_PRE
#undef BOOST_CONTRACT_AUX_TEST_NO_B_PRE
#define BOOST_CONTRACT_AUX_TEST_NO_C_PRE
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok;

    a aa;
    
    a_pre = true;
    b_pre = true;
    c_pre = true;
    out.str("");
    aa.f();
    ok.str(""); ok // Test nothing failed.
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        
        << "b::f::pre" << std::endl
        
        << "c::f::old" << std::endl
        << "b::f::old" << std::endl
        << "a::f::old" << std::endl
        
        << "a::f::body" << std::endl
        
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        
        << "c::f::old" << std::endl
        << "c::f::post" << std::endl
        << "b::f::old" << std::endl
        << "b::f::post" << std::endl
        << "a::f::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));
    
    a_pre = false;
    b_pre = true;
    c_pre = false;
    out.str("");
    aa.f();
    ok.str(""); ok
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        
        << "b::f::pre" << std::endl // Test only middle pre checked and no fail.
        
        << "c::f::old" << std::endl
        << "b::f::old" << std::endl
        << "a::f::old" << std::endl
        
        << "a::f::body" << std::endl
        
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        
        << "c::f::old" << std::endl
        << "c::f::post" << std::endl
        << "b::f::old" << std::endl
        << "b::f::post" << std::endl
        << "a::f::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));
    
    struct err {};
    boost::contract::set_precondition_failed(
            [] (boost::contract::from) { throw err(); });

    ok.str(""); ok
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl

        << "b::f::pre" << std::endl // Test only middle pre checked and failed.
    ;
    
    a_pre = true;
    b_pre = false;
    c_pre = false;
    out.str("");
    try {
        aa.f();
        BOOST_TEST(false);
    } catch(err const&) {
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_pre = false;
    b_pre = false;
    c_pre = true;
    out.str("");
    try {
        aa.f();
        BOOST_TEST(false);
    } catch(err const&) {
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_pre = false;
    b_pre = false;
    c_pre = false;
    out.str("");
    try {
        aa.f();
        BOOST_TEST(false);
    } catch(err const&) {
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    return boost::report_errors();
}

