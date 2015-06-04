
// Test free function body throwing.

#include "../aux_/oteststream.hpp"
#include <boost/contract/free_function.hpp>
#include <boost/contract/scoped.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

struct e {};

void f() {
    boost::contract::scoped c = boost::contract::free_function()
        .precondition([&] { out << "f::pre" << std::endl; })
        .postcondition([&] { out << "f::post" << std::endl; })
    ;
    out << "f::body" << std::endl;
    throw e(); // Test body throw.
}

int main() {
    std::ostringstream ok;

    bool threw = false;
    out.str("");
    try { f(); }
    catch(e const&) { threw = true; }
    BOOST_TEST(threw);
    ok.str(""); ok
        << "f::pre" << std::endl
        << "f::body" << std::endl
        // Test no post because body threw.
    ;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

