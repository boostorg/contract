
// Test protected member function throwing.

#include "../aux_/oteststream.hpp"
#include <boost/contract/protected_member.hpp>
#include <boost/contract/scoped.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

struct a {
    void invariant() const { out << "a::inv" << std::endl; }
    static void static_invariant() { out << "a::static_inv" << std::endl; }

    struct e {};

    void call_f() { f(); }

protected:
    virtual void f() {
        boost::contract::scoped c = boost::contract::protected_member()
            .precondition([&] { out << "a::f::pre" << std::endl; })
            .postcondition([&] { out << "a::f::post" << std::endl; })
        ;
        out << "a::f::body" << std::endl;
        throw a::e();
    }
};

int main() {
    std::ostringstream ok;

    a aa;
    bool threw = false;
    out.str("");
    try { aa.call_f(); }
    catch(a::e const&) { threw = true; }
    BOOST_TEST(threw);
    ok.str(""); ok
        << "a::f::pre" << std::endl
        << "a::f::body" << std::endl
        // Test no post because body threw (never inv because not public).
    ;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

