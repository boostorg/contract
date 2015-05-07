
#include <boost/contract/free_function.hpp>
#include <boost/contract/oldof.hpp>
#include <boost/detail/lightweight_test.hpp>

// Test old-values evaluated and copied only once.

unsigned copy_count, eval_count;

struct num {
    int i;
    explicit num(int const _i) : i(_i) {}
    num(num const& n) : i(n.i) { ++copy_count; }
private:
    num& operator=(num const&);
};

num const& eval(num const& n) { ++eval_count; return n; }

void swap(num& a, num& b) {
    // Test explicit type declaration.
    boost::shared_ptr<num const> old_a = BOOST_CONTRACT_OLDOF(eval(a));
    // Test auto type declaration (C++11).
    auto old_b = BOOST_CONTRACT_OLDOF(eval(b));
    boost::contract::var contract = boost::contract::free_function()
        .precondition([&] {})
        .postcondition([&] {
            BOOST_TEST_EQ(a.i, old_b->i);
            BOOST_TEST_EQ(b.i, old_a->i);
        })
    ;
    int a_i = a.i;
    a.i = b.i;
    b.i = a_i;
}

int main() {
    copy_count = eval_count = 0;
    num a(1), b(2);
    swap(a, b);
#ifndef BOOST_CONTRACT_CONFIG_NO_POSTCONDITIONS
    BOOST_TEST_EQ(copy_count, 2);
    BOOST_TEST_EQ(eval_count, 2);
#else
    BOOST_TEST_EQ(copy_count, 0);
    BOOST_TEST_EQ(eval_count, 0);
#endif

    return boost::report_errors();
}

