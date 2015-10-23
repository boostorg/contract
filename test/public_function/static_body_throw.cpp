
// Test public static member function throwing.

#include "../aux_/oteststream.hpp"
#include <boost/contract/public_function.hpp>
#include <boost/contract/guard.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

struct a {
    void invariant() const { out << "a::inv" << std::endl; }
    static void static_invariant() { out << "a::static_inv" << std::endl; }

    struct e {};

    static void f() {
        boost::contract::guard c = boost::contract::public_function<a>()
            .precondition([&] { out << "a::f::pre" << std::endl; })
            .old([&] { out << "a::f::old" << std::endl; })
            .postcondition([&] { out << "a::f::post" << std::endl; })
        ;
        out << "a::f::body" << std::endl;
        throw a::e();
    }
};

int main() {
    std::ostringstream ok;

    bool threw = false;
    out.str("");
    try { a::f(); }
    catch(a::e const&) { threw = true; }
    BOOST_TEST(threw);
    ok.str(""); ok
        << "a::static_inv" << std::endl
        << "a::f::pre" << std::endl
        << "a::f::old" << std::endl
        << "a::f::body" << std::endl
        << "a::static_inv" << std::endl
        // Test no post (but still static inv) because body threw.
    ;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

