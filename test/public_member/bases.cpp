
// Test public member subcontracting.

#include "../aux_/oteststream.hpp"
#include <boost/contract/public_member.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/oldof.hpp>
#include <boost/contract/scoped.hpp>
#include <boost/contract/override.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <string>

boost::contract::aux::test::oteststream out;

template<char Id>
struct t {
    void invariant() const {
        out << Id << "::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(z != "");
    }
    static void static_invariant() { out << Id << "::static_inv" << std::endl; }

    std::string z;
    t() : z("") { z.push_back(Id); }

    // Test pure virtual (=> decl).
    virtual std::string f(std::string& s, boost::contract::virtual_* v = 0) = 0;
};
    
template<char Id>
std::string t<Id>::f(std::string& s, boost::contract::virtual_* v) {
    std::string result;
    boost::shared_ptr<std::string const> old_u = BOOST_CONTRACT_OLDOF(v, z);
    boost::shared_ptr<std::string const> old_s = BOOST_CONTRACT_OLDOF(v, s);
    boost::contract::scoped c = boost::contract::public_member(v, result, this)
        .precondition([&] {
            out << Id << "::f::pre" << std::endl;
            BOOST_CONTRACT_ASSERT(s != "");
//                BOOST_CONTRACT_ASSERT(false);
        })
        .postcondition([&] (std::string const& result) {
            out << Id << "::f::post" << std::endl;
            BOOST_CONTRACT_ASSERT(z == *old_u + *old_s);
            BOOST_CONTRACT_ASSERT(s.find(*old_u) != std::string::npos);
            BOOST_CONTRACT_ASSERT(result == *old_s);
        })
    ;
    return result = "";
}

struct c
    #define BASES public t<'d'>, protected t<'p'>, private t<'q'>, public t<'e'>
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const {
        out << "c::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(y != "");
    }
    static void static_invariant() { out << "c::static_inv" << std::endl; }

    std::string y;
    c() : y("c") {}

    // Test both overriding (=> introspect) and virtual (=> decl).
    virtual std::string f(std::string& s, boost::contract::virtual_* v = 0)
            /* override */ {
        std::string result;
        boost::shared_ptr<std::string const> old_y = BOOST_CONTRACT_OLDOF(v, y);
        boost::shared_ptr<std::string const> old_s = BOOST_CONTRACT_OLDOF(v, s);
        boost::contract::scoped c = boost::contract::public_member<
                override_f>(v, result, &c::f, this, s)
            .precondition([&] {
                out << "c::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(s != "");
//                BOOST_CONTRACT_ASSERT(false);
            })
            .postcondition([&] (std::string const& result) {
                out << "c::f::post" << std::endl;
                BOOST_CONTRACT_ASSERT(y == *old_y + *old_s);
                BOOST_CONTRACT_ASSERT(s.find(*old_y) != std::string::npos);
                BOOST_CONTRACT_ASSERT(result == *old_s);
            })
        ;
        out << "c::f::body" << std::endl;
        return result = s;
    }
    BOOST_CONTRACT_OVERRIDE(f)
};

// Test not (fully) contracted base is not part of subcontracting.
struct b {
    virtual std::string f(std::string& s) { return s; } // No contract.
};

// Test public member with both non-contracted and contracted bases.
struct a
    #define BASES public b, public c
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const {
        out << "a::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(x != "");
    }
    static void static_invariant() { out << "a::static_inv" << std::endl; }

    std::string x;
    a() : x("a") {}

    // Test overriding (=> introspect).
    // TODO: Do I need this virtual_* or not? ... would a polymorphic cass to
    // c still call into this f impl if virtual_* is not here? I'd think so...
    std::string f(std::string& s, boost::contract::virtual_* v = 0)
            /* override */ {
        std::string result;
        boost::shared_ptr<std::string const> old_x = BOOST_CONTRACT_OLDOF(v, x);
        boost::shared_ptr<std::string const> old_s = BOOST_CONTRACT_OLDOF(v, s);
        boost::contract::scoped c = boost::contract::public_member<
                override_f>(v, result, &a::f, this, s)
            .precondition([&] {
                out << "a::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(s != "");
            })
            .postcondition([&] (std::string const& result) {
                out << "a::f::post ** " << result << std::endl;
                BOOST_CONTRACT_ASSERT(x == *old_x + *old_s);
                BOOST_CONTRACT_ASSERT(s.find(*old_x) != std::string::npos);
                BOOST_CONTRACT_ASSERT(result == *old_s);
            })
        ;
        out << "a::f::body" << std::endl;

        std::string save_s = s;
        std::string save = x;
        x += save_s;
        s = save;

        save = y;
        y += save_s;
        s += save;

        save = t<'d'>::z;
        t<'d'>::z += save_s;
        s += save;

        save = t<'e'>::z;
        t<'e'>::z += save_s;
        s += save;

        return result = save_s;
    }
    BOOST_CONTRACT_OVERRIDE(f)
};

int main() {
    a aa;
    std::string s = "!";
    aa.f(s);
    std::cout << s << std::endl;
    std::cout << aa.x << std::endl;
    std::cout << aa.y << std::endl;
    std::cout << aa.t<'d'>::z << std::endl;
    std::cout << aa.t<'e'>::z << std::endl;
    //BOOST_TEST_EQ(aa.val(), 456);
    //BOOST_TEST_EQ(i, 123);

    return boost::report_errors();
}

