
#include <boost/contract/oldof.hpp>
#include <boost/contract/public_member.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/introspect.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/config.hpp>
#include <boost/detail/lightweight_test.hpp>

// Test old-values evaluated and copied only once, in virtual calls.

unsigned copy_count, eval_count;

struct num {
    int i;
    num() : i(0) {}
    num(num const& n) : i(n.i) { ++copy_count; }
    num& operator=(num const& n) { ++copy_count; i = n.i; return *this; }
};

num& eval(num& n) { ++eval_count; return n; }

struct once {
    num n;

    void invariant() const {} // So base inv part of this test.
    static void static_invariant() {} // So base static inv part of this test.

    virtual ~once() {}

    void inc_of(int const delta, boost::contract::virtual_body v = 0) {
        auto old_n = BOOST_CONTRACT_OLDOF(v, eval(n));
        auto c = boost::contract::public_member(v, this)
            .precondition([&] {}) // So base pre part of this test.
            .postcondition([&] { // So base post part of this test.
                BOOST_CONTRACT_ASSERT(n.i >= old_n->i + delta);
            })
        ;
        inc_of_body(delta);
    }
    virtual void inc_of_body(int const delta) { n.i = n.i + delta; }
};

struct twice
    #define BASES public once
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES
    
    void invariant() const {} // So derived inv part of this test.
    static void static_invariant() {} // So base static inv part of this test.

    virtual ~twice() {}

    void inc_of(int const delta) {
        auto c = boost::contract::public_member<introspect_inc_of>(this,
                &twice::inc_of, delta)
            .precondition([&] {}) // So derived pre part of this test.
            .postcondition([&] {}) // So derived post part of this test.
        ;
        inc_of_body(delta);
    }
    virtual void inc_of_body(int const delta) { n.i = (n.i + delta) * 2; }
    BOOST_CONTRACT_INTROSPECT(inc_of)
};

int main() {
    // Test direct user call.

    copy_count = eval_count = 0;
    once x;
    x.n.i = 1;
    x.inc_of(1); // 1 + 1 = 2

    BOOST_TEST_EQ(x.n.i, 2);
#ifdef BOOST_CONTRACT_CONFIG_NO_POSTCONDITIONS
    BOOST_TEST_EQ(copy_count, 0);
    BOOST_TEST_EQ(eval_count, 0);
#else
    BOOST_TEST_EQ(copy_count, 1);
    BOOST_TEST_EQ(eval_count, 1);
#endif

    // Test call via overridden virtual function.

    copy_count = eval_count = 0;
    twice y;
    y.n.i = 1;
    y.inc_of(1); // (1 + 1) * 2 = 4
    
    BOOST_TEST_EQ(y.n.i, 4);
#ifdef BOOST_CONTRACT_CONFIG_NO_POSTCONDITIONS
    BOOST_TEST_EQ(copy_count, 0);
    BOOST_TEST_EQ(eval_count, 0);
#else
    BOOST_TEST_EQ(copy_count, 1);
    BOOST_TEST_EQ(eval_count, 1);
#endif

    return boost::report_errors();
}

