
// Test without postconditions.

#define BOOST_CONTRACT_TEST_NO_F_POST
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok; ok // Test nothing fails.
        #if BOOST_CONTRACT_PRECONDITIONS
            << "f::pre" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "f::old" << std::endl
        #endif
        << "f::body" << std::endl
    ;

    f_post = true;
    out.str("");
    f();
    BOOST_TEST(out.eq(ok.str()));
    
    f_post = false;
    out.str("");
    f();
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

