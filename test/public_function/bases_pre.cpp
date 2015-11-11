
// Test overriding func has no pre (but overridden pre still checked).

#include "../aux_/oteststream.hpp"
#include <boost/contract/base_types.hpp>
#include <boost/contract/public_function.hpp>
#include <boost/contract/guard.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/override.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

struct b {
    static void static_invariant() { out << "b::static_inv" << std::endl; }
    void invariant() const { out << "b::inv" << std::endl; }

    virtual void f(char ch, boost::contract::virtual_* v = 0) {
        boost::contract::guard c = boost::contract::public_function(v, this)
            .precondition([&] {
                out << "b::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(ch == 'b');
            })
            .old([] { out << "a::f::old" << std::endl; })
            .postcondition([] { out << "a::f::post" << std::endl; })
        ;
        out << "a::f::body" << std::endl;
    }
};

struct a
    #define BASES public b
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    static void static_invariant() { out << "a::static_inv" << std::endl; }
    void invariant() const { out << "a::inv" << std::endl; }

    virtual void f(char ch, boost::contract::virtual_* v = 0) /* override */ {
        boost::contract::guard c = boost::contract::public_function<override_f>(
                v, &a::f, this, ch)
            // Test no .precondition(...) here.
            .old([] { out << "a::f::old" << std::endl; })
            .postcondition([] { out << "a::f::post" << std::endl; })
        ;
        out << "a::f::body" << std::endl;
    }
    BOOST_CONTRACT_OVERRIDE(f)
};

int main() {
    a aa;
    aa.f('a');
    return boost::report_errors();
}

