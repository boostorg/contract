
// Test only derived and grandparent classes (ends) with postconditions.

#undef BOOST_CONTRACT_AUX_TEST_NO_A_POST
#define BOOST_CONTRACT_AUX_TEST_NO_B_POST
#undef BOOST_CONTRACT_AUX_TEST_NO_C_POST
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>
#include <string>
        
std::string ok_a() {
    std::ostringstream ok; ok
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::dtor::old" << std::endl
        #endif
        << "a::dtor::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "a::static_inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::dtor::post" << std::endl // This can fail.
        #endif
    ;
    return ok.str();
}

std::string ok_b(bool failure = false) {
    std::ostringstream ok; ok
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "b::dtor::old" << std::endl
        #endif
        << "b::dtor::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "b::static_inv" << std::endl
            << (failure ? "b::inv\n" : "")
        #endif
    ;
    return ok.str();
}

std::string ok_c(bool failure = false) {
    std::ostringstream ok; ok
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "c::dtor::old" << std::endl
        #endif
        << "c::dtor::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "c::static_inv" << std::endl
            << (failure ? "c::inv\n" : "")
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << (!failure ? "c::dtor::post\n" : "") // This can fail.
        #endif
    ;
    return ok.str();
}

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
        << ok_a()
        << ok_b()
        << ok_c()
    ;
    BOOST_TEST(out.eq(ok.str()));
    
    struct err {};
    boost::contract::set_postcondition_failure([&ok] (boost::contract::from) {
        BOOST_TEST(out.eq(ok.str())); // Must check before dtor throws...
        throw err(); // ... for testing (as dtors should never throw anyways).
    });

    a_post = false;
    b_post = true;
    c_post = true;
    try {
        {
            a aa;
            ok.str(""); ok
                << ok_a() // Test a::dtor::post failed.
            ;
            out.str("");
        }
        #if BOOST_CONTRACT_POSTCONDITIONS
                BOOST_TEST(false);
            } catch(err const&) {
        #endif
        ok // ... then exec other dtors and check inv on throw (as dtor threw).
            << ok_b(BOOST_CONTRACT_POSTCONDITIONS)
            << ok_c(BOOST_CONTRACT_POSTCONDITIONS)
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_post = true;
    b_post = false;
    c_post = true;
    try {
        {
            a aa;
            out.str("");
        }
        ok.str(""); ok
            << ok_a()
            << ok_b() // Test no b::dtor::post so no failure here.
            << ok_c()
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
                << ok_a()
                << ok_b()
                << ok_c() // Test c::dtor::post failed.
            ;
            out.str("");
        }
        #if BOOST_CONTRACT_POSTCONDITIONS
                BOOST_TEST(false);
            } catch(err const&) {
        #endif
        // ... then exec other dtors and check inv on throw (as dtor threw).
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_post = false;
    b_post = false;
    c_post = false;
    try {
        {
            a aa;
            ok.str(""); ok
                << ok_a() // Test a::dtor::post failed.
            ;
            out.str("");
        }
        #if BOOST_CONTRACT_POSTCONDITIONS
                BOOST_TEST(false);
            } catch(err const&) {
        #endif
        ok // ... then exec other dtors and check inv on throw (as dtor threw).
            << ok_b(BOOST_CONTRACT_POSTCONDITIONS)
            << ok_c(BOOST_CONTRACT_POSTCONDITIONS)
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    return boost::report_errors();
}

