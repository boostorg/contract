
#include "../aux_/oteststream.hpp"
#include <boost/contract/public_member.hpp>
#include <boost/contract/type.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

// Test static member (no object so substitution principle does not apply so no
// subcontracting, plus no object so only static invariants checked).

boost::contract::aux::test::oteststream out;

struct b {
    void invariant() const {
        out << "b::inv" << std::endl;
    }
    
    static void static_invariant() {
        out << "b::static_inv" << std::endl;
    }

    static void s() {
        boost::contract::type c = boost::contract::public_member<b>()
            .precondition([&] {
                out << "b::s::pre" << std::endl;
            })
            .postcondition([&] {
                out << "b::s::post" << std::endl;
            })
        ;
        out << "b::s::body" << std::endl;
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
    
    static void static_invariant() { // Test static invariants checked.
        out << "a::static_inv" << std::endl;
    }

    static void s() {
        boost::contract::type c = boost::contract::public_member<a>()
            .precondition([&] {
                out << "a::s::pre" << std::endl;
            })
            .postcondition([&] {
                out << "a::s::post" << std::endl;
            })
        ;
        out << "a::s::body" << std::endl;
    }
};

int main() {
    std::ostringstream ok;
    
    out.str("");
    b::s(); // Test static call directly from class (no object) and no base.
    ok.str("");
    ok
        << "b::static_inv" << std::endl
        << "b::s::pre" << std::endl
        << "b::s::body" << std::endl
        << "b::static_inv" << std::endl
        << "b::s::post" << std::endl
    ;
    BOOST_TEST(out.check(ok.str()));

    out << std::endl;
    
    a aa;
    out.str("");
    aa.s(); // Test static call from object and with base.
    ok.str("");
    ok
        << "a::static_inv" << std::endl
        << "a::s::pre" << std::endl
        << "a::s::body" << std::endl
        << "a::static_inv" << std::endl
        << "a::s::post" << std::endl
    ;
    BOOST_TEST(out.check(ok.str()));

    return boost::report_errors();
}

