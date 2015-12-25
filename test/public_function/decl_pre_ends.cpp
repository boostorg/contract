
// Test only derived and grandparent classes (ends) with preconditions.

#undef BOOST_CONTRACT_AUX_TEST_NO_A_PRE
#define BOOST_CONTRACT_AUX_TEST_NO_B_PRE
#undef BOOST_CONTRACT_AUX_TEST_NO_C_PRE
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
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_PRECONDITIONS
            << "c::f::pre" << std::endl // Test only c pre checked.
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
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "c::f::old" << std::endl
            << "c::f::post" << std::endl
            << "b::f::old" << std::endl
            << "b::f::post" << std::endl
            << "a::f::post" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));
    
    a_pre = true;
    b_pre = false;
    c_pre = false;
    out.str("");
    aa.f();
    ok.str(""); ok
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
            // Test b's pre not checked.
            << "a::f::pre" << std::endl
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
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "c::f::old" << std::endl
            << "c::f::post" << std::endl
            << "b::f::old" << std::endl
            << "b::f::post" << std::endl
            << "a::f::post" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));
    
    a_pre = false;
    b_pre = false;
    c_pre = true;
    out.str("");
    aa.f();
    ok.str(""); ok
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_PRECONDITIONS
            << "c::f::pre" << std::endl // Test only c pre checked.
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
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "c::f::old" << std::endl
            << "c::f::post" << std::endl
            << "b::f::old" << std::endl
            << "b::f::post" << std::endl
            << "a::f::post" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));
    
    struct err {};
    boost::contract::set_precondition_failure(
            [] (boost::contract::from) { throw err(); });

    #if BOOST_CONTRACT_PRECONDITIONS
        ok.str(""); ok
            #if BOOST_CONTRACT_ENTRY_INVARIANTS
                << "c::static_inv" << std::endl
                << "c::inv" << std::endl
                << "b::static_inv" << std::endl
                << "b::inv" << std::endl
                << "a::static_inv" << std::endl
                << "a::inv" << std::endl
            #endif
            << "c::f::pre" << std::endl
            << "a::f::pre" << std::endl // Only ends' pre checked and failed.
        ;
    #endif
    
    a_pre = false;
    b_pre = true;
    c_pre = false;
    out.str("");
    try {
        aa.f();
        #if BOOST_CONTRACT_PRECONDITIONS
                BOOST_TEST(false);
            } catch(err const&) {
        #endif
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_pre = false;
    b_pre = false;
    c_pre = false;
    out.str("");
    try {
        aa.f();
        #if BOOST_CONTRACT_PRECONDITIONS
                BOOST_TEST(false);
            } catch(err const&) {
        #endif
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    return boost::report_errors();
}

