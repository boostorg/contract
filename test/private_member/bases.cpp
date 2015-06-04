
// Test private member function contracts.

#include "../aux_/oteststream.hpp"
#include <boost/contract/base_types.hpp>
#include <boost/contract/private_member.hpp>
#include <boost/contract/scoped.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

struct b {
    void invariant() const { out << "b::inv" << std::endl; }
    static void static_invariant() { out << "b::static_inv" << std::endl; }

private:
    virtual void f() {
        boost::contract::scoped c = boost::contract::private_member()
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

    void call_f() { f(); }

private:
    virtual void f() {
        boost::contract::scoped c = boost::contract::private_member()
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

    a aa;
    out.str("");
    aa.call_f();
    ok.str(""); ok
        // Test not part of public API so no inv, plus cannot be called directly
        // so substitution principle does not applu and no subcontracting.
        << "a::f::pre" << std::endl
        << "a::f::body" << std::endl
        << "a::f::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

