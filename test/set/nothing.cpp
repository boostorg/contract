
// Test no pre or post (for free func, but same for all contracts).

#include "../detail/oteststream.hpp"
#include <boost/contract/function.hpp>
#include <boost/contract/guard.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::test::detail::oteststream out;

void f() {
    boost::contract::guard c = boost::contract::function();
    out << "f::body" << std::endl;
}

int main() {
    std::ostringstream ok;

    out.str("");
    f();
    ok.str(""); ok << "f::body" << std::endl;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

