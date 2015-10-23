
// Test old before pre error (for free func, but same for all contracts).

#include <boost/contract/function.hpp>
#include <boost/contract/guard.hpp>

void f() {
    boost::contract::guard c = boost::contract::function()
        .old([] {}) // Error (old before pre).
        .precondition([] {})
    ;
}

int main() {
    f();
    return 0;
}

