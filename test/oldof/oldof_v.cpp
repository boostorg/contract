
#include <boost/contract/oldof.hpp>
#include <boost/contract/public_member.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/introspect.hpp>
#include <boost/contract/config.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <string>

// Test old-values evaluated and copied only once, in virtual calls.

unsigned copy_count, eval_count;

struct str {
    std::string x;
    str(std::string const& _x) : x(_x) {}
    str(str const& s) : x(s.x) { ++copy_count; }
private:
    str& operator=(str const&);
};

str& eval(str& s) { ++eval_count; return s; }

struct d {
    str s;

    d() : s("d") {}

    void invariant() const {}
    static void static_invariant() {}

    void f(char const z, boost::contract::virtual_body v = 0) {
        // Test explicit type declaration.
        boost::shared_ptr<str const> old_s = BOOST_CONTRACT_OLDOF(v, eval(s));
        if(!v || v->action == boost::contract::aux::virtual_call::check_post) {
            BOOST_TEST(old_s);
            BOOST_TEST_EQ(old_s->x, "d");
        } else {
            BOOST_TEST(!old_s);
        }
        auto c = boost::contract::public_member(v, this)
            .precondition([&] {})
            .postcondition([&] { BOOST_TEST_EQ(old_s->x, "d"); })
        ;
        f_body(z);
    }
    virtual void f_body(char const z) { s.x += z; }
};

struct c
    #define BASES public d
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    str s;

    c() : s("c") {}

    void invariant() const {}
    static void static_invariant() {}

    void f(char const z, boost::contract::virtual_body v = 0) {
        // Test auto type declaration (C++11).
        auto old_s = BOOST_CONTRACT_OLDOF(v, eval(s));
        if(!v || v->action == boost::contract::aux::virtual_call::check_post) {
            BOOST_TEST(old_s);
            BOOST_TEST_EQ(old_s->x, "c");
        } else {
            BOOST_TEST(!old_s);
        }
        auto c = boost::contract::public_member<introspect_f>(v, this, &c::f, z)
            .precondition([&] {})
            .postcondition([&] { BOOST_TEST_EQ(old_s->x, "c"); })
        ;
        f_body(z);
    }
    virtual void f_body(char const z) = 0;
    BOOST_CONTRACT_INTROSPECT(f)
};

struct b {
    str s;

    b() : s("b") {}

    void invariant() const {}
    static void static_invariant() {}

    void f(char const z, boost::contract::virtual_body v = 0) {
        boost::shared_ptr<str const> old_s = BOOST_CONTRACT_OLDOF(v, eval(s));
        if(!v || v->action == boost::contract::aux::virtual_call::check_post) {
            BOOST_TEST(old_s);
            BOOST_TEST_EQ(old_s->x, "b");
        } else {
            BOOST_TEST(!old_s);
        }
        auto c = boost::contract::public_member(v, this)
            .precondition([&] {})
            .postcondition([&] { BOOST_TEST_EQ(old_s->x, "b"); })
        ;
        f_body(z);
    }
    virtual void f_body(char const z) = 0;
};

struct a
    #define BASES public b, public c
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    str s;

    a() : s("a") {}

    void invariant() const {}
    static void static_invariant() {}

    void f(char const z, boost::contract::virtual_body v = 0) {
        auto old_s = BOOST_CONTRACT_OLDOF(v, eval(s));
        if(!v || v->action == boost::contract::aux::virtual_call::check_post) {
            BOOST_TEST(old_s);
            BOOST_TEST_EQ(old_s->x, "a");
        } else {
            BOOST_TEST(!old_s);
        }
        auto c = boost::contract::public_member<introspect_f>(v, this, &a::f, z)
            .precondition([&] {})
            .postcondition([&] { BOOST_TEST_EQ(old_s->x, "a"); })
        ;
        f_body(z);
    }
    virtual void f_body(char const z) { s.x += z; }
    BOOST_CONTRACT_INTROSPECT(f)
};

int main() {
    // Test with `v` and bases.
    copy_count = eval_count = 0;
    a aa;
    aa.f('z');
#ifndef BOOST_CONTRACT_CONFIG_NO_POSTCONDITIONS
    BOOST_TEST_EQ(copy_count, 4);
    BOOST_TEST_EQ(eval_count, 4);
#else
    BOOST_TEST_EQ(copy_count, 0);
    BOOST_TEST_EQ(eval_count, 0);
#endif
    
    // Test with `v` but without bases.
    copy_count = eval_count = 0;
    d dd;
    dd.f('z');
#ifndef BOOST_CONTRACT_CONFIG_NO_POSTCONDITIONS
    BOOST_TEST_EQ(copy_count, 1);
    BOOST_TEST_EQ(eval_count, 1);
#else
    BOOST_TEST_EQ(copy_count, 0);
    BOOST_TEST_EQ(eval_count, 0);
#endif

    return boost::report_errors();
}

