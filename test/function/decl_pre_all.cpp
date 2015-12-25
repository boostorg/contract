
// Test with preconditions.

#undef BOOST_CONTRACT_AUX_TEST_NO_F_PRE
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok;

    f_pre = true;
    out.str("");
    f();
    ok.str(""); ok
        #if BOOST_CONTRACT_PRECONDITIONS
            << "f::pre" << std::endl // Test no failure here.
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "f::old" << std::endl
        #endif
        << "f::body" << std::endl
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "f::post" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));

    struct err {};
    boost::contract::set_precondition_failure(
            [] (boost::contract::from) { throw err(); });

    f_pre = false;
    out.str("");
    try {
        f();
        #if BOOST_CONTRACT_PRECONDITIONS
                BOOST_TEST(false);
            } catch(err const&) {
        #endif
        ok.str(""); ok
        #if BOOST_CONTRACT_PRECONDITIONS
            << "f::pre" << std::endl // Test this failed.
        #endif
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    return boost::report_errors();
}

