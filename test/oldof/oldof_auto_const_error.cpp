
#include <boost/contract/free_function.hpp>
#include <boost/contract/oldof.hpp>
#include <boost/contract/assert.hpp>

// Test auto old value declarations (C++11) must be const.

void inc(int& x) {
    auto old_x = BOOST_CONTRACT_OLDOF(x); // OK.
    auto c = boost::contract::free_function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(*old_x = x - 1); // Error.
        })
    ;
    ++x;
}

int main() {
    int x = 1;
    inc(x);
    return 0;
}

