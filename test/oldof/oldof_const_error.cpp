
#include <boost/contract/free_function.hpp>
#include <boost/contract/oldof.hpp>
#include <boost/contract/assert.hpp>
#include <boost/shared_ptr.hpp>

// Test old value declarations must be const.

void inc(int& x) {
    boost::shared_ptr<int> old_x = BOOST_CONTRACT_OLDOF(x); // Error.
    auto c = boost::contract::free_function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(*old_x == x - 1); // OK.
        })
    ;
    ++x;
}

int main() {
    int x = 1;
    inc(x);
    return 0;
}

