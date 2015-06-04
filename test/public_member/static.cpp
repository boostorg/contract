
// Test public static member function contracts.

#include "../aux_/oteststream.hpp"
#include <boost/contract/base_types.hpp>
#include <boost/contract/public_member.hpp>
#include <boost/contract/scoped.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

struct b {
    void invariant() const { out << "b::inv" << std::endl; }
    static void static_invariant() { out << "b::static_inv" << std::endl; }

    static void f() {
        boost::contract::scoped c = boost::contract::public_member<b>()
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
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const { out << "a::inv" << std::endl; }
    static void static_invariant() { out << "a::static_inv" << std::endl; }

    static void f() {
        boost::contract::scoped c = boost::contract::public_member<a>()
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

    out.str("");
    a::f();
    ok.str(""); ok
        // Static so no object thus only static inv, plus never virtual so subst
        // principle does not apply and no subcontracting.
        << "a::static_inv" << std::endl
        << "a::f::pre" << std::endl
        << "a::f::body" << std::endl
        << "a::static_inv" << std::endl
        << "a::f::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

