
// Test derived and base classes all with exit static invariants.

#undef BOOST_CONTRACT_AUX_TEST_NO_A_STATIC_INV
#undef BOOST_CONTRACT_AUX_TEST_NO_B_STATIC_INV
#undef BOOST_CONTRACT_AUX_TEST_NO_C_STATIC_INV
#include "./decl.hpp"

#include "../aux_/oteststream.hpp"
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok;
    
    struct err {};
    boost::contract::set_exit_invariant_failed(
            [] (boost::contract::from) { throw err(); });

    a aa;

    a_exit_static_inv = false;
    b_exit_static_inv = true;
    c_exit_static_inv = true;
    out.str("");
    try {
        a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
                true;
        aa.f();
        BOOST_TEST(false);
    } catch(err const&) {
        ok.str(""); ok
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl

            << "c::f::pre" << std::endl
            
            << "c::f::old" << std::endl
            << "b::f::old" << std::endl
            << "a::f::old" << std::endl
            
            << "a::f::body" << std::endl
            
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl // Test this failed.
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_exit_static_inv = true;
    b_exit_static_inv = false;
    c_exit_static_inv = true;
    out.str("");
    try {
        a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
                true;
        aa.f();
        BOOST_TEST(false);
    } catch(err const&) {
        ok.str(""); ok
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl

            << "c::f::pre" << std::endl
            
            << "c::f::old" << std::endl
            << "b::f::old" << std::endl
            << "a::f::old" << std::endl
            
            << "a::f::body" << std::endl
            
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
            << "b::static_inv" << std::endl // Test this failed.
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_exit_static_inv = true;
    b_exit_static_inv = true;
    c_exit_static_inv = false;
    out.str("");
    try {
        a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
                true;
        aa.f();
        BOOST_TEST(false);
    } catch(err const&) {
        ok.str(""); ok
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl

            << "c::f::pre" << std::endl
            
            << "c::f::old" << std::endl
            << "b::f::old" << std::endl
            << "a::f::old" << std::endl
            
            << "a::f::body" << std::endl
            
            << "c::static_inv" << std::endl // Test this failed.
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_exit_static_inv = false;
    b_exit_static_inv = false;
    c_exit_static_inv = false;
    out.str("");
    try {
        a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
                true;
        aa.f();
        BOOST_TEST(false);
    } catch(err const&) {
        ok.str(""); ok
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl

            << "c::f::pre" << std::endl
            
            << "c::f::old" << std::endl
            << "b::f::old" << std::endl
            << "a::f::old" << std::endl
            
            << "a::f::body" << std::endl
            
            << "c::static_inv" << std::endl // Test this failed (as all did).
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    return boost::report_errors();
}

