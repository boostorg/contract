
// Test with postconditions.

#undef BOOST_CONTRACT_TEST_NO_F_POST
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>
#include <string>
        
std::string ok_f() {
    std::ostringstream ok; ok
        #if BOOST_CONTRACT_PRECONDITIONS
            << "f::pre" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "f::old" << std::endl
        #endif
        << "f::body" << std::endl
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "f::post" << std::endl // This can fail.
        #endif
    ;
    return ok.str();
}

int main() {
    std::ostringstream ok;

    f_post = true;
    out.str("");
    f();
    ok.str(""); ok // Test nothing failed.
        << ok_f()
    ;
    BOOST_TEST(out.eq(ok.str()));

    struct err {};
    boost::contract::set_postcondition_failure(
            [] (boost::contract::from) { throw err(); });

    f_post = false;
    out.str("");
    try {
        f();
        #if BOOST_CONTRACT_POSTCONDITIONS
                BOOST_TEST(false);
            } catch(err const&) {
        #endif
        ok.str(""); ok
            << ok_f() // Test f::post failed.
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    return boost::report_errors();
}

