
#include <iostream>
#include "../aux_/friend.hpp"
#include <boost/contract/oldof.hpp>
#include <boost/contract/public_member.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/introspect.hpp>
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

str const& eval(str const& s) { ++eval_count; return s; }

struct d {
    str s;

    d() : s("d") {}

    void invariant() const {}
    static void static_invariant() {}

    boost::contract::var f_contract(char const& z,
            boost::contract::virtual_* v = 0) const {
        // Test explicit type declaration.
        boost::shared_ptr<str const> old_s = BOOST_CONTRACT_OLDOF(v, eval(s));
        if(boost::contract::aux::test::friend_::checking_post(v)) {
            BOOST_TEST(old_s);
            BOOST_TEST_EQ(old_s->x, "d");
        } else {
            BOOST_TEST(!old_s);
        }
        return boost::contract::public_member(v, this)
            .precondition([&] {})
            .postcondition([&] { BOOST_TEST_EQ(old_s->x, "d"); })
        ;
    }
    virtual void f(char const z) {
        boost::contract::var contract = f_contract(z);
        s.x += z;
    }
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

    boost::contract::var f_contract(char const& z,
            boost::contract::virtual_* v = 0) const {
        // Test auto type declaration (C++11).
        auto old_s = BOOST_CONTRACT_OLDOF(v, eval(s));
        if(boost::contract::aux::test::friend_::checking_post(v)) {
            BOOST_TEST(old_s);
            BOOST_TEST_EQ(old_s->x, "c");
        } else {
            BOOST_TEST(!old_s);
        }
        return boost::contract::public_member<introspect_f_contract>(v, this, z)
            .precondition([&] {})
            .postcondition([&] { BOOST_TEST_EQ(old_s->x, "c"); })
        ;
    }
    virtual void f(char const z) = 0;
    BOOST_CONTRACT_INTROSPECT(f_contract)
};

struct b {
    str s;

    b() : s("b") {}

    void invariant() const {}
    static void static_invariant() {}

    boost::contract::var f_contract(char const& z,
            boost::contract::virtual_* v = 0) const {
        boost::shared_ptr<str const> old_s = BOOST_CONTRACT_OLDOF(v, eval(s));
        if(boost::contract::aux::test::friend_::checking_post(v)) {
            BOOST_TEST(old_s);
            BOOST_TEST_EQ(old_s->x, "b");
        } else {
            BOOST_TEST(!old_s);
        }
        return boost::contract::public_member(v, this)
            .precondition([&] {})
            .postcondition([&] { BOOST_TEST_EQ(old_s->x, "b"); })
        ;
    }
    virtual void f(char const z) = 0;
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

    boost::contract::var f_contract(char const& z,
            boost::contract::virtual_* v = 0) const {
        auto old_s = BOOST_CONTRACT_OLDOF(v, eval(s));
        if(boost::contract::aux::test::friend_::checking_post(v)) {
            BOOST_TEST(old_s);
            BOOST_TEST_EQ(old_s->x, "a");
        } else {
            BOOST_TEST(!old_s);
        }
        return boost::contract::public_member<introspect_f_contract>(v, this, z)
            .precondition([&] {
        //        std::clog << "pre>>>" << old_s->x << "<<<" << std::endl;
            })
            .postcondition([&] {
                std::clog << "post>>> " << old_s->x << "<<<" << std::endl;
                BOOST_TEST_EQ(old_s->x, "a");
            })
        ;
    }
    virtual void f(char const z) {
        boost::shared_ptr<boost::contract::virtual_> v =
                boost::make_shared<boost::contract::virtual_>();
        boost::contract::var contract = f_contract(z, v.get());
        std::clog << v->old_values_.size() << std::endl;
        std::clog << "body start" << std::endl;
        s.x += z;
        std::clog << "body finish" << std::endl;
    }
    BOOST_CONTRACT_INTROSPECT(f_contract)
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
    
//    // Test with `v` but without bases.
//    copy_count = eval_count = 0;
//    d dd;
//    dd.f('z');
//#ifndef BOOST_CONTRACT_CONFIG_NO_POSTCONDITIONS
//    BOOST_TEST_EQ(copy_count, 1);
//    BOOST_TEST_EQ(eval_count, 1);
//#else
//    BOOST_TEST_EQ(copy_count, 0);
//    BOOST_TEST_EQ(eval_count, 0);
//#endif

    return boost::report_errors();
}

