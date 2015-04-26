
#include <boost/contract/oldof.hpp>
#include <boost/contract/free_function.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/config.hpp>
#include <boost/detail/lightweight_test.hpp>

// Test old-values evaluated and copied only once.

unsigned copy_count, eval_count;

struct num {
    int i;
    explicit num(int const _i) : i(_i) {}
    num(num const& n) : i(n.i) { ++copy_count; }
    num& operator=(num const& n) { ++copy_count; i = n.i; return *this; }
};

num& eval(num& n) { ++eval_count; return n; }

void inc(num& n) {
    auto old_n = BOOST_CONTRACT_OLDOF(eval(n));
    auto c = boost::contract::free_function()
        .precondition([&] {}) // So pre part of this test.
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(n.i == old_n->i + 1);
        })
    ;
    n.i = n.i + 1;
}

int main() {
    copy_count = eval_count = 0;
    num n(1);
    inc(n);

    BOOST_TEST_EQ(n.i, 2);
#ifdef BOOST_CONTRACT_CONFIG_NO_POSTCONDITIONS
    BOOST_TEST_EQ(copy_count, 0);
    BOOST_TEST_EQ(eval_count, 0);
#else
    BOOST_TEST_EQ(copy_count, 1);
    BOOST_TEST_EQ(eval_count, 1);
#endif

    return boost::report_errors();
}

