
// Test public member subcontracting.

#include "../aux_/oteststream.hpp"
#include <boost/contract/public_member.hpp>
#include <boost/contract/decl_function.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/oldof.hpp>
#include <boost/contract/var.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/introspect.hpp>
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

    void f(std::string const& s, boost::contract::decl c) const {
        boost::shared_ptr<std::string const> old_u = BOOST_CONTRACT_OLDOF(c, z);
        boost::shared_ptr<std::string const> old_s = BOOST_CONTRACT_OLDOF(c, s);
        boost::contract::var contract = boost::contract::public_member(c, this)
            .precondition([&] {
                out << Id << "::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(s != "");
//                BOOST_CONTRACT_ASSERT(false);
            })
            .postcondition([&] {
                out << Id << "::f::post" << std::endl;
                BOOST_CONTRACT_ASSERT(z == *old_u + *old_s);
                BOOST_CONTRACT_ASSERT(s.find(*old_u) != std::string::npos);
            })
        ;
    }
    // Test pure virtual (=> decl).
    virtual void f(std::string& s) = 0;
};

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

    void f(std::string const& s, boost::contract::decl c) const {
        boost::shared_ptr<std::string const> old_y = BOOST_CONTRACT_OLDOF(c, y);
        boost::shared_ptr<std::string const> old_s = BOOST_CONTRACT_OLDOF(c, s);
        boost::contract::var contract = boost::contract::public_member<
                introspect_f>(c, this, s)
            .precondition([&] {
                out << "c::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(s != "");
//                BOOST_CONTRACT_ASSERT(false);
            })
            .postcondition([&] {
                out << "c::f::post" << std::endl;
                BOOST_CONTRACT_ASSERT(y == *old_y + *old_s);
                BOOST_CONTRACT_ASSERT(s.find(*old_y) != std::string::npos);
            })
        ;
    }
    // Test both overriding (=> introspect) and virtual (=> decl).
    virtual void f(std::string& s) /* override */ {
        boost::contract::var contract = boost::contract::decl_function(
                this, s, &c::f);
        out << "c::f::body" << std::endl;
    }
    BOOST_CONTRACT_INTROSPECT(f)
};

// Test not (fully) contracted base is not part of subcontracting.
struct b {
    virtual void f(std::string&) = 0; // No contract.
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
    void f(std::string& s) /* override */ {
        boost::shared_ptr<std::string const> old_x = BOOST_CONTRACT_OLDOF(x);
        boost::shared_ptr<std::string const> old_s = BOOST_CONTRACT_OLDOF(s);
        boost::contract::var contract = boost::contract::public_member<
                introspect_f>(this, s)
            .precondition([&] {
                out << "a::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(s != "");
            })
            .postcondition([&] {
                out << "a::f::post" << std::endl;
                BOOST_CONTRACT_ASSERT(x == *old_x + *old_s);
                BOOST_CONTRACT_ASSERT(s.find(*old_x) != std::string::npos);
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
    }
    BOOST_CONTRACT_INTROSPECT(f)
};

int main() {
    a aa;
    std::string s = "!";
    aa.f(s);
    std::cout << s << std::endl;
    std::cout << aa.x << std::endl;
    std::cout << aa.y << std::endl;
    std::cout << aa.t<'d'>::z << std::endl;
    //BOOST_TEST_EQ(aa.val(), 456);
    //BOOST_TEST_EQ(i, 123);

    return boost::report_errors();
}

