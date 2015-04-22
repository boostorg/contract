
#include "aux_/oteststream.hpp"
#include <boost/contract/free_function.hpp>
#include <boost/contract/type.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

// Test free-function.

boost::contract::aux::test::oteststream out;

void f() {
    boost::contract::type c = boost::contract::free_function()
        .precondition([&] {
            out << "f::pre" << std::endl;
        })
        .postcondition([&] {
            out << "f::post" << std::endl;
        })
    ;
    out << "f::body" << std::endl;
}

int main() {
    std::ostringstream ok;

    out.str("");
    f();
    ok.str("");
    ok
        << "f::pre" << std::endl
        << "f::body" << std::endl
        << "f::post" << std::endl
    ;
    BOOST_TEST(out.check(ok.str()));

    return boost::report_errors();
}

