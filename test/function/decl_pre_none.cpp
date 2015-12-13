
// Test without preconditions.

#define BOOST_CONTRACT_AUX_TEST_NO_F_PRE
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok; ok // Test nothing fails.
        << "f::old" << std::endl
        << "f::body" << std::endl
        << "f::post" << std::endl
    ;

    f_pre = true;
    out.str("");
    f();
    BOOST_TEST(out.eq(ok.str()));
    
    f_pre = false;
    out.str("");
    f();
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

