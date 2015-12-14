
// Test all derived and base classes with postconditions.

#undef BOOST_CONTRACT_AUX_TEST_NO_A_POST
#undef BOOST_CONTRACT_AUX_TEST_NO_B_POST
#undef BOOST_CONTRACT_AUX_TEST_NO_C_POST
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok;
    
    a_post = true;
    b_post = true;
    c_post = true;
    {
        a aa;
        out.str("");
    }
    ok.str(""); ok // Test nothing failed.
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        << "a::dtor::old" << std::endl
        << "a::dtor::body" << std::endl
        << "a::static_inv" << std::endl
        << "a::dtor::post" << std::endl

        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "b::dtor::old" << std::endl
        << "b::dtor::body" << std::endl
        << "b::static_inv" << std::endl
        << "b::dtor::post" << std::endl
        
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "c::dtor::old" << std::endl
        << "c::dtor::body" << std::endl
        << "c::static_inv" << std::endl
        << "c::dtor::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));
    
    struct err {};
    boost::contract::set_postcondition_failed([&ok] (boost::contract::from) {
        BOOST_TEST(out.eq(ok.str())); // Must check before dtor throws...
        throw err(); // for testing (as dtors should never throw anyways).
    });

    a_post = false;
    b_post = true;
    c_post = true;
    try {
        {
            a aa;
            ok.str(""); ok
                << "a::static_inv" << std::endl
                << "a::inv" << std::endl
                << "a::dtor::old" << std::endl
                << "a::dtor::body" << std::endl
                << "a::static_inv" << std::endl
                << "a::dtor::post" << std::endl // Test this failed...
            ;
            out.str("");
        }
        BOOST_TEST(false);
    } catch(err const&) {
        ok // ... then exec other dtors and check inv on throw (as dtor threw).
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "b::dtor::old" << std::endl
            << "b::dtor::body" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl

            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
            << "c::dtor::old" << std::endl
            << "c::dtor::body" << std::endl
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_post = true;
    b_post = false;
    c_post = true;
    try {
        {
            a aa;
            ok.str(""); ok
                << "a::static_inv" << std::endl
                << "a::inv" << std::endl
                << "a::dtor::old" << std::endl
                << "a::dtor::body" << std::endl
                << "a::static_inv" << std::endl
                << "a::dtor::post" << std::endl

                << "b::static_inv" << std::endl
                << "b::inv" << std::endl
                << "b::dtor::old" << std::endl
                << "b::dtor::body" << std::endl
                << "b::static_inv" << std::endl
                << "b::dtor::post" << std::endl // Test this failed.
            ;
            out.str("");
        }
        BOOST_TEST(false);
    } catch(err const&) {
        ok // ... then exec other dtors and check inv on throw (as dtor threw).
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
            << "c::dtor::old" << std::endl
            << "c::dtor::body" << std::endl
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_post = true;
    b_post = true;
    c_post = false;
    try {
        {
            a aa;
            ok.str(""); ok
                << "a::static_inv" << std::endl
                << "a::inv" << std::endl
                << "a::dtor::old" << std::endl
                << "a::dtor::body" << std::endl
                << "a::static_inv" << std::endl
                << "a::dtor::post" << std::endl

                << "b::static_inv" << std::endl
                << "b::inv" << std::endl
                << "b::dtor::old" << std::endl
                << "b::dtor::body" << std::endl
                << "b::static_inv" << std::endl
                << "b::dtor::post" << std::endl
                
                << "c::static_inv" << std::endl
                << "c::inv" << std::endl
                << "c::dtor::old" << std::endl
                << "c::dtor::body" << std::endl
                << "c::static_inv" << std::endl
                << "c::dtor::post" << std::endl // Test this failed.
            ;
            out.str("");
        }
        BOOST_TEST(false);
    } catch(err const&) {
        ok; // ... then exec other dtors and check inv on throw (as dtor threw).
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_post = false;
    b_post = false;
    c_post = false;
    try {
        {
            a aa;
            ok.str(""); ok
                << "a::static_inv" << std::endl
                << "a::inv" << std::endl
                << "a::dtor::old" << std::endl
                << "a::dtor::body" << std::endl
                << "a::static_inv" << std::endl
                << "a::dtor::post" << std::endl // Test this failed...
            ;
            out.str("");
        }
        BOOST_TEST(false);
    } catch(err const&) {
        ok // ... then exec other dtors and check inv on throw (as dtor threw).
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "b::dtor::old" << std::endl
            << "b::dtor::body" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl

            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
            << "c::dtor::old" << std::endl
            << "c::dtor::body" << std::endl
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    return boost::report_errors();
}

