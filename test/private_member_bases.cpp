
#include "aux_/oteststream.hpp"
#include <boost/contract/private_member.hpp>
#include <boost/contract/type.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

// Test private member (not public API so substitution principle does not
// apply so no subcontracting, plus not public API so no invariants checked).

boost::contract::aux::test::oteststream out;

struct b {
    void invariant() const {
        out << "b::inv" << std::endl;
    }
    
    static void static_invariant() {
        out << "b::static_inv" << std::endl;
    }
    
    friend int main();
    
private:
    void f() {
        boost::contract::type c = boost::contract::private_member()
            .precondition([&] {
                out << "b::f::pre" << std::endl;
            })
            .postcondition([&] {
                out << "b::f::post" << std::endl;
            })
        ;
        out << "b::f::body" << std::endl;
    }
};

struct a
    #define BASES public b
    : BASES // Test no subcontracting even if public base.
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const { // Test no invariants checked.
        out << "a::inv" << std::endl;
    }
    
    static void static_invariant() { // Test no static invariants checked.
        out << "a::static_inv" << std::endl;
    }
    
    friend int main();

private:
    void f() {
        boost::contract::type c = boost::contract::private_member()
            .precondition([&] {
                out << "a::f::pre" << std::endl;
            })
            .postcondition([&] {
                out << "a::f::post" << std::endl;
            })
        ;
        out << "a::f::body" << std::endl;
    }
};

int main() {
    std::ostringstream ok;
    
    b bb;
    out.str("");
    bb.f(); // Test without base.
    ok.str("");
    ok
        << "b::f::pre" << std::endl
        << "b::f::body" << std::endl
        << "b::f::post" << std::endl
    ;
    BOOST_TEST(out.check(ok.str()));

    out << std::endl;

    a aa;
    out.str("");
    aa.f(); // Test with base.
    ok.str("");
    ok
        << "a::f::pre" << std::endl
        << "a::f::body" << std::endl
        << "a::f::post" << std::endl
    ;
    BOOST_TEST(out.check(ok.str()));

    return boost::report_errors();
}

