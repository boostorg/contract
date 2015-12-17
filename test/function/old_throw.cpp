
// Test throw from free function .old().

#include "../aux_/oteststream.hpp"
#include <boost/contract/function.hpp>
#include <boost/contract/guard.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

struct err {};

void f() {
    boost::contract::guard c = boost::contract::function()
        .precondition([&] { out << "f::pre" << std::endl; })
        .old([&] {
            out << "f::old" << std::endl;
            throw err(); // Test .old() throws.
        })
        .postcondition([&] { out << "f::post" << std::endl; })
    ;
    out << "f::body" << std::endl;
}

int main() {
    std::ostringstream ok;

    boost::contract::set_postcondition_failure(
            [] (boost::contract::from) { throw; });

    try {
        out.str("");
        f();
        BOOST_TEST(false);
    } catch(err const&) {
        ok.str(""); ok
            << "f::pre" << std::endl
            << "f::old" << std::endl // Test this threw.
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    return boost::report_errors();
}

